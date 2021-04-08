stack = []
ans = 0


def safe_op(a):
    if abs(a) < 1e-6:
        return 0
    if abs(a) > 1e6:
        return 1e6 * ((a > 0) - (a < 0))
    return a


for token in input().split():
    if token[0].isdigit():
        stack.append(float(token))
    else:
        x, y = stack[-2], stack[-1]
        stack.pop()
        stack.pop()

        if token == "+":
            stack.append(safe_op(x + y))
        elif token == "-":
            stack.append(safe_op(x - y))
        elif token == "*":
            stack.append(safe_op(x * y))
        elif token == "/":
            if y == 0:
                stack.append(1e6 * ((x > 0) - (x < 0)))
            else:
                stack.append(safe_op(x / y))

print("{:.4f}".format(stack[0]))