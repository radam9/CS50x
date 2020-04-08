from cs50 import get_int

# check to get user input
while True:
    n = get_int("Height: ")
    if n > 0 and n < 9:
        break

# Loop to print output
for i in range(n):
    a = i + 1
    print(" " * (n - a) + "#" * (a) + "  " + "#" * (a))