inp = open('china.in', 'rb')
out = open('china.out', 'wb')

k = int(inp.readline())

if k % 2 == 0:
    if k/2 % 2 == 0:
        res = (k/2) - 1
    else:
        res = (k/2) - 2
else:
    res = (k-1)/2

out.write(str(res) + '\n')
