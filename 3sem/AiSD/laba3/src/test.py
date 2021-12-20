from laba3 import Min_Heap

def test_1():
    result = Min_Heap(2, 5, *[1, 2, 3, 4, 5]).proc_time()
    assert result == "0 0\n1 0\n0 1\n1 2\n0 4\n", "Test 1"

def test_2():
    result = Min_Heap(6, 5, *[1, 2, 3, 4, 5]).proc_time()
    assert result == "0 0\n0 0\n0 0\n0 0\n0 0\n", "Test 2"

def test_3():
    result = Min_Heap(3, 3, *[1, 2, 3, 4, 5]).proc_time()
    assert result == "0 0\n1 0\n2 0\n3 0\n4 0\n", "Test 3"

def test_4():
    result = Min_Heap(4, 20, *[1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]).proc_time()
    assert result == "0 0\n1 0\n2 0\n3 0\n0 1\n1 1\n2 1\n3 1\n0 2\n1 2\n2 2\n3 2\n0 3\n1 3\n2 3\n3 3\n0 4\n1 4\n2 4\n3 4\n", "Test 4"