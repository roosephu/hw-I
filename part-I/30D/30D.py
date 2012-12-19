from random import *
from subprocess import call
from shutil import move

info = [
    [5, True, 10], 
    [5, False, 10],
    [10, True, 100],
    [10, False, 100],
    [10, False, 1000],
    [10, False, 1000],
    [20, False, 10000],
    [20, False, 10000],
    [20, False, 100000],
    [20, False, 100000],
    [100, True, 1000000], 
    [100, False, 1000000],
    [1000, False, 1000000],
    [1000, False, 1000000],
    [100000, True, 1000000],
    [100000, False, 1000000],
    [100000, False, 1000000], 
    [100000, False, 1000000], 
    [100000, False, 1000000], 
    [100000, False, 1000000], 
]

for cnt, [N, K, wmax] in enumerate (info) :
    while True :
        with open ("30D.in", "w") as fout :
            n = randint (N * 9 // 10, N)
            if K :
                k = n + 1
            else :
                k = randint (1, n)
            print (n, k, file = fout)
            S = sample (range (-wmax, wmax + 1), n)
            for i in S :
                print (i, end = " ", file = fout)
            while True :
                x = randint (-wmax, wmax + 1)
                y = randint (-wmax, wmax)
                if x in S and y :
                    continue
                print (x, file = fout)
                print (y, file = fout)
                break

        if call ("./30D") or call ("./30D_wa1") or call ("./30D_wa2") or call ("./30D_wa3") or call ("./30D_wa4") \
                or call (["diff", "30D.out", "30D_1.ans"]) + \
                   call (["diff", "30D.out", "30D_2.ans"]) + \
                   call (["diff", "30D.out", "30D_3.ans"]) + \
                   call (["diff", "30D.out", "30D_4.ans"]) >= 2 \
                or cnt < 4 or K :
            break
        print (cnt, "fail")

    print (cnt)
    move ("30D.in" , "30D" + str (cnt) + ".in" );
    move ("30D.out", "30D" + str (cnt) + ".out");
