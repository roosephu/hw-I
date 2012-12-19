from random import *
from subprocess import call
from shutil import move

info = [                        # n, alphabet, use a lot of same character, single
    [8, 2, False, False], 
    [10, 2, False, False], 
    [100, 20, False, False], 
    [100, 2, False, True], 
    [100, 2, True, False], 
    [100, 2, True, False], 
    [10000, 20, False, False], 
    [10000, 20, True, False], 
    [20000, 20, False, True], 
    [20000, 2, True, False], 
    [20000, 2, True, False], 
    [20000, 2, True, False], 
    [50000, 20, False, True], 
    [50000, 2, True, False], 
    [50000, 2, True, False], 
    [50000, 2, True, False], 
    [100000, 20, False, False], 
    [100000, 2, True, True], 
    [100000, 2, True, False], 
    [100000, 2, True, False], 
]

def get (a, strict, n) :
    if not strict :
        return choice (a)
    for i in range (len (a) - 1) :
        if random () > 10 / n :
            return a[i]
    return a[len (a) - 1]

for cnt, [N, alpha, strict, single] in enumerate (info) :
    while True :
        with open ("30E.in", "w") as fout :
            n = randint (N * 99 // 100, N)
            S = ""
            
            ins = []
            for i in range (alpha) :
                ins += [chr (ord ('a') + i)]
            for i in range (n) :
                S += get (ins, strict, n)
            if single :
                S += 'z'
            print (S, file = fout)
        # print (call ("./30E"))
        if int (call ("./30E")) == int (single) :
            break
        print ('fail')

    print (cnt)
    move ("30E.in" , "30E" + str (cnt) + ".in" )
    move ("30E.out", "30E" + str (cnt) + ".out")
