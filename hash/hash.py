import mmh3


def my_hash(s):
    i = 0
    res = 0
    for c in s:
        if i == 0:
            res = res ^ ord(c)
        elif i == 1:
            res = res ^ (ord(c) << 8)
        elif i == 2:
            res = res ^ (ord(c) << 16)
        elif i == 3:
            res = res ^ (ord(c) << 24)
        elif i == 4:
            i = 0
        i += 1
    return res


words = ['VEHICLE1', 'VEHICLE2', 'AMOB', 'BMOB']

for word in words:
    murmur = mmh3.hash(word)
    my = my_hash(word)
    print('Murmurhash {0} {1}'.format(murmur, murmur % 1024))
    print('MyHash {0} {1}'.format(my, my % 1024))
