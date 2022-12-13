from functools import cmp_to_key
from Day13 import compare # note: compare is implemented in reversed order (biggest to smallest)

compElems = [[[2]], [[6]]]

while True:
    line = input()
    if line == 'q!': break
    if line == '': continue

    compElems.append(eval(line))

sortedElems = sorted(compElems, key=cmp_to_key(compare), reverse=True)

pack1Idx = -1
pack2Idx = -1

for idx, elem in enumerate(sortedElems):
    if len(elem) == 1 and (type(elem[0]) is list) and len(elem[0]) == 1:
        if elem[0][0] == 2:
            pack1Idx = idx + 1
        elif elem[0][0] == 6:
            pack2Idx = idx + 1

print("Packet [[2]] is at:", pack1Idx)
print("Packet [[6]] is at:", pack2Idx)
print("Decoder:", pack1Idx*pack2Idx)
