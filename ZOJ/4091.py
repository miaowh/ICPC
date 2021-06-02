T = input()
for i in range(T):
    e = input()
    cnt = 0
    i = 2
    while i <= e:
        cnt = cnt + e // i
        i = i * 2
    print cnt
