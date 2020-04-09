from sys import argv
import csv
from cs50 import SQL

# check for input arguments
if len(argv) != 2:
    print("Usage: import.py <file.csv>")
    exit(1)

# connect to database
db = SQL("sqlite:///students.db")

# open csv file and write into db
with open(argv[1], "r") as file:
    for p in csv.DictReader(file):
        name = p["name"].split(" ")
        if len(name) == 2:
            name.insert(1, None)
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)",
                   name[0], name[1], name[2], p["house"], p["birth"])
