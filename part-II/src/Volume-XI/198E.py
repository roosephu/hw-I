from random import *
from subprocess import call

def RX () :
    return randint (-100, 100)

def RP () :
    return randint (1, 100)

for cnt in range (100000) :
    with open ("198E.in", "w") as fout :
        n = 1000
        print (RX (), RX (), RP (), RP (), n, file = fout)
        for i in range (n) :
            print (RX (), RX (), RP (), RP (), RP (), file = fout)

    if call ("./198E") or call ("./198E-petr") or call (["diff", "198E.out", "198E.ans"]) :
        break
    print (cnt)
