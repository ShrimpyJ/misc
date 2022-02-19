import sys

if len(sys.argv) != 2:
    print("usage: thunderdrunk.py NUM_PLAYERS")
    exit()

n = int(sys.argv[1])

for i in range(32):
    player = (i % n) + 1
    print(i+1, player, end='')
    if i+1 == 16 or i+1 == 19:
        print(" <--- long one", end='')
    print()
