def hash_str(sent, power, mod):
    result = 0
    index = 0
    for letter in sent:
        result += ord(letter) * power[index]
        index += 1
    return result % mod


def sliding_hash(first, last, prev, power, mod, x):
    return ((prev - first * power[0]) * x + last) % mod


if __name__ == '__main__':
    a = 11
    b = 2 ** 31 - 1
    pattern = input()
    text = input()

    powers = [a ** i for i in range(len(pattern))][::-1]

    pattern_hash = hash_str(pattern, powers, b)
    len_pattern = len(pattern)
    temp = text[0:len_pattern]
    prev = hash_str(text[0:len_pattern], powers, b)
    if prev == pattern_hash:
        if temp == pattern:
            print(0, end=' ')
    for ind in range(len(text) - len_pattern):
        temp = temp[1:] + text[ind + len_pattern]
        new_hash = sliding_hash(ord(text[ind]), ord(text[ind + len_pattern]), prev, powers, b, a)
        prev = new_hash
        if pattern_hash == new_hash:
            if temp == pattern:
                print(ind + 1, end=' ')