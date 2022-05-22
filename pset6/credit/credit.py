import csv
import sys
import random
import cs50
from cs50 import get_int
from cs50 import get_string

cc = get_int("number: ")

length = len(str(cc))

if length != 13 and length != 15 and length != 16:
    print("INVALID")
    sys.exit()

n = 0
n1 = 0
n2 = 0
n3 = 0
n4 = 0
n5 = 0
n6 = 0

sum1 = 0
sum2 = 0

x = cc


while x > 0:
    n = x % 10
    sum1 = sum1 + n
    
    x = int(x / 10)
    n2 = int(x % 10)
    
    if n2 > 4:
        n3 = int(n2 * 2)
        n4 = int(n3 % 100 / 10)
        n5 = int(n3 % 10)
        n6 = int(n4 + n5)
    else:
        n3 = int(n2 * 2)
        n6 = n3
        
        
    sum2 = sum2 + n6
    x = int(x / 10)

sum3 = sum2 + sum1
check1 = sum3 % 10
if  check1 != 0:
    print("INVALID")
    sys.exit()

d1 = int(cc / (10 ** (length - 1)))
d2 = int(cc / (10 ** (length - 2))) % 10

if d1 == 4:
    print("VISA")
    sys.exit()

if d2 == 3 or d2 == 7 and d1 == 3:
    print("AMEX")
    sys.exit()

if d2 > 0 and d2 < 6 and d1 == 5:
    print("MASTERCARD")
    sys.exit()
    
print("INVALID")
