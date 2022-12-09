
input = """
                    [L]     [H] [W]
                [J] [Z] [J] [Q] [Q]
[S]             [M] [C] [T] [F] [B]
[P]     [H]     [B] [D] [G] [B] [P]
[W]     [L] [D] [D] [J] [W] [T] [C]
[N] [T] [R] [T] [T] [T] [M] [M] [G]
[J] [S] [Q] [S] [Z] [W] [P] [G] [D]
[Z] [G] [V] [V] [Q] [M] [L] [N] [R]
"""
lines = [[] for _ in range(10)]

idx = 0
for line in input.split('\n'):
    if len(line) > 0:
        for ch in line:
            lines[idx].append(ch)
        idx += 1

for col in range(100):
    pr = ''
    for line in lines:
        if col < len(line):
            pr += line[col]
    if len(pr) > 0 and not any(ch == ']' or ch == '[' for ch in pr):
        print(pr[::-1])

"""
9
ZJNWPS
GST
VQRLH
VSTD
QZTDBMJ
MWTJDCZL
LPMWGTJ
NGMTBFQH
RDGCPBQW
"""
