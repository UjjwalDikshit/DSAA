# minimise sum


import sys
input = sys.stdin.readline
for _ in range(int(input())):
    n = int(input())
    a = list(map(int, input().split()))
    print(min(2*a[0], a[0] + a[1]))