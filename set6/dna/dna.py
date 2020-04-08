from sys import argv, exit
import csv
import re

# https://stackoverflow.com/questions/33676975/finding-longest-consecutive-sequence-of-a-character
def findsequence(exp, text):
    search = r'(?:' + exp + '){1,}'
    temp = re.findall(search, text)
    if len(temp) == 0:
        return 0
    result = max(temp)
    count = len(re.findall(exp, result))
    return count

with open(argv[1], 'r') as db, open(argv[2], 'r') as seq:
    database = list()
    for i in csv.DictReader(db):
        database.append(i)
    sequence = seq.readline().rstrip("\n")

x = list(database[0].keys())
x.pop(0)

for person in database:
    dnacount = list()
    seqcount = list()
    for i in x:
        dnacount.append(findsequence(i, sequence))
        seqcount.append(int(person[i]))
    if dnacount == seqcount:
        print(person["name"])
        exit(0)

print("No match")

# https://stackoverflow.com/questions/2664150/counting-longest-occurrence-of-repeated-sequence-in-python
# def findsequence(exp, text):
#     search = r'((?:' + exp + '{1})+)'
#     result = max(re.findall(search, text))
#     count = len(re.findall(exp, result))
#     return count


# https://stackoverflow.com/questions/33676975/finding-longest-consecutive-sequence-of-a-character
# def findsequence(exp, text):
#     search = r'(?:' + exp + '){1,}'
#     result = max(re.findall(search, text))
#     count = len(re.findall(exp, result))
#     return count

