f = open('words_alpha.txt')
lines = f.read().splitlines()
goal = 5
length = 5


def padLine(n):
    for i in range(0, n):
        print(' ', end='')

def findValid(index, n, word, pairs):
    if len(answer) == goal:
        print(answer)
        return answer

#    padLine(depth*2)
#    print(word, n, depth)

    for i in range(index, len(pairs)):
#        if answer[0][0] == 'angry':
#            print(answer)
#            print(pairs[i])
#            print()

#        padLine(depth*2)
#        print(f'    {word[0]}   {pairs[i][0]}')
        result = n & pairs[i][1]
        if result == 0:
            answer.append(word)
            for j in range(i, len(pairs)):
                a = findValid(j, n | pairs[j][1], pairs[j], pairs)
                if a != 0:
                    print(len(a))
                    return answer
            answer.pop()
#            return findValid(i+1, n | pairs[i][1], pairs[i], pairs)

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
    findValid(i+1, pairs[i][1], pairs[i], pairs)
    if len(answer) == goal:
        printAnswers(answer)
