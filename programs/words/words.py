f = open('test.txt')
lines = f.read().splitlines()
target = 5
length = 5


def pop(answer):
    print(f"    Popping", end='')
    print(f" {answer.pop()}", end='')
    print(f":  {answer}")

def findValid(index, n, word, pairs):
    if len(answer) == target:
        print(answer)
        return answer

    for i in range(index, len(pairs)):
        result = n & pairs[i][1]
        if result == 0:
            answer.append(pairs[i][0])
            for j in range(i, len(pairs)):
                a = findValid(j+1, n | pairs[i][1], pairs[j], pairs)
                break
            answer.pop()

    return 0

def printAnswers(answers):
    for i in range(0, len(answers)):
        print(answers[i][0], end=' ')
    print()

words = []
for line in lines:
    # Get words without symbols of valid length
    if len(line) == length and line.isalpha():
        word = line.lower()
        sort = ''.join(sorted(word))

        # Only get words without repeating letters
        flag = 1
        for i in range(1, len(sort)):
            if sort[i] == sort[i-1]:
                flag = 0 

        if flag == 1:
            words.append(line.lower())

pairs = []
for word in words:
    # Remove words with repeating letters
    sort = ''.join(sorted(word))
    val = 0
    for letter in word.lower():
        n = ord(letter) - 97
        val += 2 ** n
    pairs.append([word, val])

for i in range(0, len(pairs)):
    answer = []
    print(f"PUSHING {pairs[i][0]}")
    answer.append(pairs[i][0])
    findValid(i+1, pairs[i][1], pairs[i], pairs)
