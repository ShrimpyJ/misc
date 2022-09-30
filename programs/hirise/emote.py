from random import *

EYES = ["x", "o", "u", "n", "v", "^", "+", "~", "-", "T"]
MOUTHS = [".", "_"]
HEADS = [ ["[", "]"], ["(", ")"], ["{", "}"] ]
HANDS = [ ["b", "d"] ]

def randomElem(l):
    return l[randint(0, len(l)-1)]

def emote():
    eye = randomElem(EYES)
    mouth = randomElem(MOUTHS)
    head = randomElem(HEADS)
    hands = randomElem(HANDS)
    print(f"{hands[0]}{head[0]}{eye}{mouth}{eye}{head[1]}{hands[1]}")

for i in range(0, 100):
    emote()

#       |_/
#     d[+_+]b
#      /[_]\ 
#     O | | O
#       m m
