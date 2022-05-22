import csv
import sys
import random
import cs50
from cs50 import get_int

size = get_int("Height: ")

while(size > 8 or size < 1):
    print("Pyramid must be between 1 and 8 blocks high")
    size = get_int("Height: ")

spaces = size - 1
for i in range(1, size + 1, 1):
    for j in range(spaces):
        print(" ", end="")
    print("#" * i, end="")
    print("  ", end="")
    print("#" * i)
    spaces -= 1

