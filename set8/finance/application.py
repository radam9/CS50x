import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    inventory = db.execute("SELECT symbol,quantity FROM inventory WHERE userid = :uid", uid=session["user_id"])
    cash = float(db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])[0]["cash"])
    total = cash
    for i in inventory:
        stock = lookup(i["symbol"])
        i["price"] = stock["price"]
        i["name"] = stock["name"]
        i["total"] = usd(stock["price"] * i["quantity"])
        total += stock["price"] * i["quantity"]
    return render_template("index.html", context={"inventory":inventory,"total":usd(total),"cash":usd(cash)})


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol)
        cash = float(db.execute("SELECT cash FROM users WHERE id = :userid", userid=session["user_id"])[0]["cash"])
        if symbol == None or stock == None:
            return apology("The stock symbol you searched for doesn't exist.")
        if not shares.isdigit():
            return apology("You have not entered a valid quantity of shares to buy.")
        shares = int(shares)
        if shares < 1:
            return apology("You have entered an incorrect value for stock 'quantity'")
        if (stock["price"] * shares) > cash:
            return apology("You don't have enough cash to buy those stocks")
        cost = round(shares*stock["price"]*(-1), 2)
        db.execute("INSERT INTO shares (stock,symbol,value,quantity,cost,userid) VALUES(:st,:sy,:va,:qu,:co,:uid)",
            {"st":stock["name"],"sy":stock["symbol"],"va":stock["price"],"qu":shares,"co":cost,"uid":session["user_id"]})
        db.execute("UPDATE users SET cash = :cash WHERE id = :userid",{"cash":float(cash + cost),"userid":session["user_id"]})
        inv = db.execute("SELECT quantity FROM inventory WHERE userid = :uid AND symbol = :sy",
                        {"uid":session["user_id"],"sy":stock["symbol"]})
        if not inv:
            db.execute("INSERT INTO inventory (symbol,quantity,userid) VALUES(:sy,:qu,:uid)",
                        {"sy":stock["symbol"],"qu":shares,"uid":session["user_id"]})
        else:
            quan = (shares + inv[0]["quantity"])
            db.execute("UPDATE inventory SET quantity = :qu WHERE userid =:uid AND symbol = :sy",
                        {"qu":quan,"uid":session["user_id"],"sy":stock["symbol"]})
        flash("Purchase completed successfully!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    hist = db.execute("SELECT * FROM shares WHERE userid = :uid ORDER BY date DESC", uid=session["user_id"])
    for h in hist:
        h["total"] = round(h["value"]*h["quantity"],2)
    return render_template("history.html", context=hist)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        result = lookup(request.form.get("symbol"))
        return render_template("quoted.html", result=result)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():

    """Register user"""
    if request.method == "POST":
        user = request.form.get("username")
        pword = request.form.get("password")
        rpword = request.form.get("confirmation")

        if len(db.execute("SELECT * FROM users WHERE username = :username", username=user)) > 0:
            return apology("Username already exists, please choose a different username!")
        if len(pword) < 8 or not any(char.isdigit() for char in pword):
            return apology("Your password is less than 8 characters or doesn't contain at least 1 digit")
        if pword != rpword:
            return apology("Your passwords do not match")
        pword = generate_password_hash(pword)

        db.execute("INSERT INTO users (username, hash) VALUES(:username, :password)", {"username":user, "password":pword})
        return redirect("/")
    else:
        return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    if request.method == "POST":
        sellstock = request.form.get("symbol")
        sellq = int(request.form.get("shares"))
        if sellstock == None:
            return apology("Please select a stock symbol to sell.")
        if sellq < 0:
            return apology("Please enter a valid quantity of stocks to sell")
        invq = db.execute("SELECT quantity FROM inventory WHERE userid = :uid AND symbol = :sy",
                            {"uid":session["user_id"],"sy":sellstock})[0]["quantity"]
        if sellq > invq:
            return apology("You don't have enough shares.")
        stock = lookup(sellstock)
        cost = round(sellq*stock["price"], 2)
        db.execute("INSERT INTO shares (stock,symbol,value,quantity,cost,userid) VALUES(:st,:sy,:va,:qu,:co,:uid)",
            {"st":stock["name"],"sy":sellstock,"va":stock["price"],"qu":sellq,"co":cost,"uid":session["user_id"]})
        db.execute("UPDATE inventory SET quantity = :qu WHERE userid =:uid AND symbol = :sy",
                        {"qu":(invq-sellq),"uid":session["user_id"],"sy":sellstock})
        db.execute("UPDATE users SET cash = cash + :cash WHERE id =:uid", {"cash":cost,"uid":session["user_id"]})
        flash("Shares successfully sold!")
        return redirect("/")
    inventory = db.execute("SELECT symbol FROM inventory WHERE userid = :uid", uid=session["user_id"])
    return render_template("sell.html", context = inventory)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
