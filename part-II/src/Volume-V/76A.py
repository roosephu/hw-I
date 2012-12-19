from random import *
from subprocess import call

while True :
    with open ("76A.in", "w") as fout :
        n, m = 50, 60
        print (n, m, file = fout)
        print (randint (1, 10), randint (1, 10), file = fout)
        for i in range (m) :
            print (randint (1, n), randint (1, n), randint (1, 10), randint (1, 10), file = fout)
    if call ("./76A") or call ("./76A_std") or call (["diff", "76A.out", "76A.ans"]) :
        break
    
