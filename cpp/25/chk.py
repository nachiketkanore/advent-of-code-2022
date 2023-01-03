s = input()
val = 0
def get_val(ch):
    if ch == '0' or ch == '1' or ch == '2':
        return ord(ch) - ord('0')
    if ch == '=':
        return -2
    if ch == '-':
        return -1

    assert(False)
for i in range(len(s)):
    val += get_val(s[i]) * (5 ** (len(s) - i - 1))

print(val)
