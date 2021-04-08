n = int(input())
xs = [int(x) for x in input().split()]
k = int(input())

for i in range(1, k + 1):
    j = i
    x = xs[i]

    while j > 0 and xs[j - 1] >= x:
        xs[j] = xs[j - 1]
        j -= 1

    if i != j:
        xs[j] = x

print(" ".join(map(str, xs)))