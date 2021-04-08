n = int(input())
xs = [int(x) for x in input().split()]


def merge(arr, l, m, r):
    tmp = [0] * (r - l + 1)
    i = l
    j = m + 1
    k = 0

    while i <= m and j <= r:
        if arr[i] < arr[j]:
            tmp[k] = arr[i]
            i += 1
        else:
            tmp[k] = arr[j]
            j += 1
        k += 1

    while i <= m:
        tmp[k] = arr[i]
        i += 1
        k += 1

    while j <= r:
        tmp[k] = arr[j]
        j += 1
        k += 1

    for i in range(len(tmp)):
        arr[l + i] = tmp[i]


def merge_sort(arr, l, r):
    if l < r:
        m = l + (r - l) // 2
        merge_sort(arr, l, m)
        merge_sort(arr, m + 1, r)
        merge(arr, l, m, r)
    print(" ".join(map(str, xs[l: r + 1])))


merge_sort(xs, 0, len(xs) - 1)