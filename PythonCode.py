# Nicholas Porbansky
# CS210

import re
import string
import collections

#def printsomething():
#print("Hello from python!")

#def PrintMe(v):
#print("You sent me: " + v)
#return 100;

#def SquareValue(v):
#return v * v

#def MultiplicationTable(number):
#for i in range(1, 11):
# #print(number, "X", i, "=", number * i)

#def DoubleValue(number):
# return number * 2

def ItemCounter():
    with open('P3_Final_Input.txt') as fIn:   # open file and create dictionary 
        counts = collections.Counter(line.strip() for line in fIn) 
    for key in counts:        # for every item sold print it and the number times sold 
        print('%s %d' % (key, counts[key]))

def NumItemCounter(item):
    item = item.capitalize()
    with open('P3_Final_Input.txt') as fIn:   # open file to read and use count function
        data = fIn.read()
        occurences = data.count(item)
        return occurences

def ItemWriter():
    with open('frequency.dat', "w") as fOut:     # same as in "ItemCounter" to store the values as a dictionary
        with open('P3_Final_Input.txt') as fIn:
            counts = collections.Counter(line.strip() for line in fIn)
        for key in counts:  # item and counts to the dat file
            fOut.write('%s %d\n' % (key, counts[key]))
   
