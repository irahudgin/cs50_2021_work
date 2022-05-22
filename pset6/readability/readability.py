import csv
import sys
import random
import cs50
import re
from cs50 import get_int
from cs50 import get_string

#index = 0.0588 * L - 0.296 * S - 15.8

#Here, L is the average number of letters per 100 words in the text, and S is the average number of sentences per 100 words in the text.

#Your program should count the number of letters, words, and sentences in the text. You may assume that a letter is any lowercase character 
#from a to z or any uppercase character from A to Z, any sequence of characters separated by spaces should count as a word, and that any occurrence
#of a period, exclamation point, or question mark indicates the end of a sentence.

#Your program should print as output "Grade X" where X is the grade level computed by the Coleman-Liau formula, rounded to the nearest integer.

#First remove everything that isnt a part of the alphabet from the string
#Count the words that are divided by spaces
#Remove spaces and count letters

#get string and remove anything from text that is not just words and spaces
text = get_string("text: ")
s = re.sub(r'[^a-zA-Z ]', '', text)

#put words into array 'words' and count elements in array stored in 'numwords'
words = s.split()
numwords = len(words)

#Counts letters by finding length of words with spaces removed
letters = len(s.replace(" ", ""))
#Gets sentences by finding how many .?! in text
sent = len(re.sub(r'[^.?!]', '', text))

#Assigns variables for formula
L = (letters / numwords) * 100
S = (sent / numwords) * 100

#Index 1 is used in case of a rounding error for anything below 1
index1 = 0.0588 * L - 0.296 * S - 15.8
index = round(0.0588 * L - 0.296 * S - 15.8)

#Conditions for printing output
if index > 16:
    print("Grade 16+")
    sys.exit()
elif index1 < 1:
    print("Before Grade 1")
    sys.exit()
else:
    print("Grade " + str(index))

