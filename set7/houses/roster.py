from sys import argv
from cs50 import SQL

# check for user input
if len(argv) != 2:
    print("Usage: roster.py <School Name>")
    exit(1)

# initiate database
db = SQL("sqlite:///students.db")

# get data from database and print
result = db.execute("SELECT first,middle,last,birth FROM students WHERE house = ? ORDER BY last,first", argv[1])
for r in result:
    if r["middle"] == None:
        print(f'{r["first"]} {r["last"]}, born {r["birth"]}')
        continue
    print(f'{r["first"]} {r["middle"]} {r["last"]}, born {r["birth"]}')
