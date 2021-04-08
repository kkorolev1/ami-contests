def count_ones(x):
    ans = 0
    while x > 0:
        if x % 2 == 1:
            ans += 1
        x >>= 1
    return ans


n = int(input())
xs = [int(x) for x in input().split()]
xs.sort()
print(" ".join(map(str, xs)))
xs.sort(key=lambda x: (-count_ones(x), x))
print(" ".join(map(str, xs)))