class Min_Heap:
    def __init__(self, n, m, *time):
        self.answer = ""
        self.n = n
        self.proc = [[i, 0] for i in range(n)]
        self.m = m
        self.time = [j for j in range(m)]
        for k in range(m):
            self.time[k] = time[k]

    def get_left(self, index):
        if (2*index+1) < self.n:
            return 2*index+1
        else: return -1

    def get_right(self, index):
        if (2*index+2) < self.n:
            return 2*index+2
        else: return -1

    def get_parent(self, index):
        if (index-1)//2 < 0:
            return 0
        return (index-1)//2
    
    def swap(self, i, j):
        temp = self.proc[i]
        self.proc[i] = self.proc[j]
        self.proc[j] = temp
    
    def down(self, index):
        max = index
        
        if self.get_left(index) > 0:
            if self.proc[self.get_left(index)][1] < self.proc[max][1]:
                max = self.get_left(index)
            if self.proc[self.get_left(index)][1] == self.proc[max][1]:
                if self.proc[self.get_left(index)][0] < self.proc[max][0]:
                    max = self.get_left(index)
        
        if self.get_right(index) > 0:
            if self.proc[self.get_right(index)][1] < self.proc[max][1]:
                max = self.get_right(index)
            if self.proc[self.get_right(index)][1] == self.proc[max][1]:
                if self.proc[self.get_right(index)][0] < self.proc[max][0]:
                    max = self.get_right(index)
        
        if index != max:
            self.swap(index, max)
            self.down(max)
        
    def proc_time(self):
        for i in range(self.m):
            self.answer += str(self.proc[0][0]) + " " + str(self.proc[0][1]) + "\n"
            self.proc[0][1] += self.time[i]
            self.down(0)
        return self.answer

if __name__ == "__main__":
    n, m = map(int, input().split())
    time = list(map(int, input().split())) 
    heap = Min_Heap(n, m, *time)
    result = heap.proc_time()
    print(result, end="")