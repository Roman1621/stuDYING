from main import _mergesort, mergesort, merge

def test_one_merge():
    merge = mergesort([(10,90), (31, 97), (4, 5)])

def test_two_merge():
    merge = mergesort([(0, 0), (0, 0)])

def test_three_merge():
    merge = mergesort([(98, 23),(-3,-6),(-12,-43),(54,87), (123, 23)])

def test_four_merge():
    merge = mergesort([])