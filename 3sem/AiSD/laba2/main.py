import math
import copy

def _mergesort(arr):
    if len(arr) > 0:
        temp = [None]*len(arr)
        mergesort(arr, temp, 0, len(arr)-1)

def mergesort(arr, temp, start, end):
    if start >= end:
        return
    middle = math.ceil((start+end)/2)
    mergesort(arr, temp, start, middle-1)
    mergesort(arr, temp, middle, end)

    temp = copy.deepcopy(arr)
    merge(arr, temp, start, end)
    for i in range(start, end+1):
        print(arr[i][1], end=' ')
    print('')

def merge(out_, in_, start, end):
    middle = math.ceil((start + end)/2)
    i = start
    j = middle
    k = start
    while i < middle and j <= end:
        if in_[i][0] > in_[j][0]:
            out_[k] = in_[j]
            j += 1
        elif in_[i][0] < in_[j][0]:
            out_[k] = in_[i]
            i += 1
        elif in_[i][1] > in_[j][1]:
            out_[k] = in_[j]
            j += 1
        else :
            out_[k] = in_[i]
            i += 1
        k += 1
    while i < middle:
        out_[k] = in_[i]
        i += 1
        k += 1
    while j < end:
        out_[k] = in_[j]
        j += 1
        k += 1

if __name__ == '__main__':
    n = int(input())
    list_ = [None]*n
    for i in range (0,n):
        m = int(input())
        t = 0
        for j in range (0,m):
            line = list(map(int, input().split()))
            t += line[j]
        list_[i] = (t, i)
    _mergesort(list_)
    for i in range (0, n):
        print(list_[i][1], end = ' ')
    print('')