from laba4 import hash_str, sliding_hash

if __name__ == '__main__':
    x = 11
    q = 2 ** 31 - 1
    test_cases = {
        (' ', 'asd'): [],
        ('no', 'yes'): [],
        ('a', 'abcda'): [0, 4],
        ('roman', 'roman'): [0],
        ('111', '1111'): [0, 1],
        ('dr', '0123dr'): [4]
    }
    for inp, res in test_cases.items():
        pattern, text = inp
        powers = [x ** i for i in range(len(pattern))][::-1]
        result = []
        pattern_hash = hash_str(pattern, powers, q)
        len_pattern = len(pattern)
        temp = text[0:len_pattern]
        prev = hash_str(text[0:len_pattern], powers, q)
        if prev == pattern_hash:
            if temp == pattern:
                result.append(0)
        for ind in range(len(text) - len_pattern):
            temp = temp[1:] + text[ind + len_pattern]
            new_hash = sliding_hash(ord(text[ind]), ord(text[ind + len_pattern]), prev, powers, q, x)
            prev = new_hash
            if pattern_hash == new_hash:
                if temp == pattern:
                    result.append(ind + 1)
        if result == res:
            print(f'test {inp} passed')
        else:
            print(f'test {inp} did not pass!')