n = input ()
G = [[] for i in range (n)]
f = [[0] * (n + 1) for i in range (n)]
g = [1] * n
size = [1] * n
for i in range (n - 1) :
    a, b = map (int, raw_input ().split (' '))
    a, b = a - 1, b - 1
    G[a] += [b]
    G[b] += [a]

def dfs (v, F) :
    f[v][1] = 1
    for u in G[v] :
        if u != F :
            dfs (u, v)
            size[v] += size[u]
            for i in xrange (size[v], 0, -1) :
                f[v][i] *= g[u]
                for j in xrange (1, min ([2, size[u], i]) + 1) :
                    f[v][i] = max ([f[v][i], f[u][j] * f[v][i - j], f[u][i - j] * f[v][j]])
    g[v] = max ([f[v][i] * i for i in xrange (1, size[v] + 1)])
    # print v, f[v]

dfs (0, -1)
print g[0]

# print 'DEBUG'
# print g
