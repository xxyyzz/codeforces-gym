import re

n = int(raw_input())
s = raw_input()

smile = [r':\)', r'\(:']
frown = [r':\(', r'\):']

num_s = 0
num_f = 0

for x in xrange(2):
    num_s += len(re.findall(smile[x], s))
    num_f += len(re.findall(frown[x], s))

if num_s == num_f:
    print 'BORED'
elif num_s < num_f:
    print 'SAD'
else:
    print 'HAPPY'
