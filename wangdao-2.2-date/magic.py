def magic(y: int, m: int, d: int):
    if m <= 2:
        y -= 1
        m += 12
    return 365 * y + y // 4 - y // 100 + y // 400 + 306 * (m + 1) // 10 + d - 429


import math
def date_func(x):
    return (30.6 * x - 63)
def date_func_floor(x):
    return math.floor(date_func(x))


a = []
delta = []
last = 0
for i in range(3,15):
    tmp = date_func_floor(i)
    a.append(tmp)
    delta.append(tmp-last)
    last = tmp

print(delta)
print(a)