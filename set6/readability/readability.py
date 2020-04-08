import re
from math import ceil

text = input("Text: ")

letters = len(re.findall(r'\w', text))
sentences = len(re.findall(r'\.|!|\?', text))
words = len(re.findall(r"[\w'-]+", text))

grade = round((0.0588 * ((letters / words) * 100)) - (0.296 * ((sentences / words) * 100)) - 15.8)

if grade >= 1 and grade < 17:
    print(f"Grade {grade}")
elif grade < 1:
    print("Before Grade 1")
else:
    print("Grade 16+")