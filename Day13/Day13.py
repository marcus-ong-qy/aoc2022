def compare(elem1, elem2):
    if (type(elem1) is int) and (type(elem2) is int):
        if elem1 <  elem2: return 1
        if elem1 == elem2: return 0
        return -1

    if (type(elem1) is list) and (type(elem2) is list):
        shorter = min(len(elem1), len(elem2))
        for i in range(shorter):
            result = compare(elem1[i], elem2[i])
            if result != 0: return result

        if len(elem1) <  len(elem2): return 1
        if len(elem1) == len(elem2): return 0
        return -1

    if (type(elem1) is list) and (type(elem2) is int):
        return compare(elem1, [elem2])

    if (type(elem1) is int) and (type(elem2) is list):
        return compare([elem1], elem2)
        
def main():
    lineIdx = 0
    pairIdx = 1

    compElems = []
    correctCounter = 0;

    while True:
        line = input()
        if line == 'q!': break

        lineType = lineIdx % 3

        if lineType != 2:
            compElems.append(eval(line))
        else:
            compElems = []
            pairIdx += 1

        if lineType == 1:
            result = compare(*compElems)
            if (result == 1):
                correctCounter += pairIdx

        lineIdx += 1

    print("No. of Pairs ordered correctly:", correctCounter)

if __name__ == '__main__':
    main()
