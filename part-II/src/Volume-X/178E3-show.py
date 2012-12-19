from PIL import Image

n = 1500
f = Image.new ('1', (n, n))
vec = []

for i, S in enumerate (open ("178E3.out", "r").readlines ()[:n]) :
    for j in range (n) :
        vec += [int (S[j * 2 : j * 2 + 1])]

f.putdata (vec)
f.save ('show.BMP', format = 'BMP')
