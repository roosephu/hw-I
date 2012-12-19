from random import *
from subprocess import call

with open ("23E.in", "w") as fout :
    n = 60
    print (n, file = fout)
    for i in range (1, n) :
        print (i + 1, randint (max (1, i - 0), i), file = fout)

call ("./23E")
# call (["python2", "23E.py"])
