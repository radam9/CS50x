from cs50 import get_string

# get input from user
card = get_string("Number: ")
c = len(card)

# conditions
if (c == 13 or c == 16) and card[0] == "4":
    print("VISA")
elif c == 15 and card[0:2] in ["34", "37"]:
    print("AMEX")
elif c == 16 and card[0:2] in ["51", "52", "53", "54", "55"]:
    print("MASTERCARD")
else:
    print("INVALID")
