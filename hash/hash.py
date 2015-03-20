import mmh3


def my_hash(s):
    i = 0
    res = 0
    for c in s:
        if i < 32:
            res = res ^ ((ord(c) % 15) << i)
        else:
            i = 0
        i += 4
    return res


words = ['VEHICLE1', 'VEHICLE2', 'AMOB', 'BMOB']

for word in words:
    my = my_hash(word)
    print('HashFunction1("{0}") = {1}'.format(word, my))

print('\n')

for word in words:
    murmur = mmh3.hash(word)
    print('HashFunction2("{0}") = {1}'.format(word, murmur))

print('\n')

for word in words:
    my = my_hash(word)
    print('HashFunction1("{0}") % 1024 = {1}'.format(word, my % 1024))

print('\n')

for word in words:
    murmur = mmh3.hash(word)
    print('HashFunction2("{0}") % 1024 = {1}'.format(word, murmur % 1024))
