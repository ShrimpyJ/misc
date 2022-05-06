class Row:
    def __init__(self):
        self.nums = []

def printRows(rows):
    for i, row in enumerate(rows):
        print(f"Row {i+1}: ", end='')
        for num in row.nums:
            print(f"{num} ", end='')
        print()

def makeRow(nums):
    row = []
    for num in nums:
        print(str(num) + " ", end='')
    print()
    row.append(1)
    for i in range(len(nums)-1):
        row.append(nums[i] + nums[i+1])
    row.append(1)
    makeRow(row)

rows = []
r1 = Row()
r1.nums.append(1)
rows.append(r1)
r2 = Row()
r2.nums.append(1)
r2.nums.append(1)
rows.append(r2)

makeRow([1, 1])
