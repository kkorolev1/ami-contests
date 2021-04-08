n = int(input())
stack = []
total_sum = 0

for i in range(n):
    cmd = input().split()

    if cmd[0] == "1":
        x = int(cmd[1])
        max_elem = x
        max_idx = len(stack)
        if len(stack) > 0 and stack[-1][0] > x:
            max_elem = stack[-1][1]
            max_idx = stack[-1][2]
        stack.append((x, max_elem, max_idx))
        total_sum += x
    elif cmd[0] == "2":
        total_sum -= stack.pop()[0]
    elif cmd[0] == "3":
        print(total_sum)
    elif cmd[0] == "4":
        print(stack[-1][1] if len(stack) > 0 else 0)
    elif cmd[0] == "5":
        print((len(stack) - stack[-1][2]) if len(stack) > 0 else 0)
    print("after op : ", stack)