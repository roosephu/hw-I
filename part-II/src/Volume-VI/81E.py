from random import *
from subprocess import call

def read (name) :
    with open (name, "r") as f :
        return int (f.readline ().split (' ')[0])
    return 

for cnt in range (1000) :
    with open ("81E.in", "w") as fout :
        n = 6
        print (n, file = fout)
        for i in range (n) :
            x = i + 1
            while x == i + 1 :
                x = randint (1, n)
            print (x, randint (1, 2), file = fout)


    if call ("./81E") or call ("./81E_std") or read ("81E.out") != read ("81E.ans") :
        break
    print (cnt)
