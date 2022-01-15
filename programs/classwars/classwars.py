import matplotlib.pyplot as plt
import numpy as np
from enum import Enum
import codecs

SCOUT = 0
SOLDIER = 1
PYRO = 2
DEMO = 3
DEMOMAN = 3
HEAVY = 4
ENGINEER = 5
MEDIC = 6
SNIPER = 7
SPY = 8

REDCOL = '#ba3435'
BLUCOL = '#3db0d9'

mercnames = ["Scout", "Soldier", "Pyro", "Demoman", "Heavy", "Engineer", "Medic", "Sniper", "Spy"]

class Round:
    def __init__(self, red, blu):
        self.winner = "NONE"
        self.red = red
        self.blu = blu
        self.surrender = 0
        self.stage = 0

class Merc:
    def __init__(self, name):
        self.name = name
        self.id = get_class(name)
        self.total = 0
        self.wins = 0
        self.losses = 0
        self.classtotals = [0,0,0,0,0,0,0,0,0]
        self.classwins = [0,0,0,0,0,0,0,0,0]
        self.classlosses = [0,0,0,0,0,0,0,0,0]

    def print(self):
        print(f"%10s - Wins: %4d" % (self.name, self.wins), end='')
        print(f"    Losses: %4d" % (self.losses), end='')
        print(f"    W/L Ratio: %.2f" % (self.wins / self.total))


class Stats:
    def __init__(self):
        self.total_rounds = 0
        self.red_wins = 0
        self.blu_wins = 0
        self.max_wins = 0

def victory(r, rounds, winner):
    if winner != "BLU" and winner != "RED":
        return
    r.winner = winner
    if r.winner == "BLU":
        print(f"BLU wins as {r.blu} vs. {r.red}")
    elif r.winner == "RED":
        print(f"RED wins as {r.red} vs. {r.blu}")
    rounds.append(r)
    print()

def get_class(c):
    if c == "Scout":
        return SCOUT
    if c == "Soldier":
        return SOLDIER
    if c == "Pyro":
        return PYRO
    if c == "Demoman":
        return DEMOMAN
    if c == "Heavy":
        return HEAVY
    if c == "Engineer":
        return ENGINEER
    if c == "Medic":
        return MEDIC
    if c == "Sniper":
        return SNIPER
    if c == "Spy":
        return SPY

file = open('console.log', 'r', encoding='iso_8859_1')
tmplines = file.read().splitlines()
file.close()

lines = []

# Get all relevant lines from raw output
for line in tmplines:
    words = line.split()
    if len(words) < 5:
        continue
    if words[4] == "surrendered!":
        lines.append(line)
    if len(words) < 8:
        continue
    if words[2] == "This":
        lines.append(line)
    if words[-7] == "Second" and words[-8] == "captured":
        lines.append(line)

rounds = []
total_rounds = 0

for i,line in enumerate(lines):
    words = line.split()
    if words[2] == "This":
        print(line)
        r = Round(words[5], words[7])
        total_rounds += 1
        if i == len(lines)-1:
            continue
        nextline = lines[i+1]
        nextwords = nextline.split()
        if nextwords[2] == "This":
            victory(r, rounds, "RED")
        continue

    if words[4] == "surrendered!":
        if total_rounds == 0:
            continue
        print(line)
        if words[3] == "red":
            victory(r, rounds, "BLU")
        else:
            victory(r, rounds, "RED")
        continue

    if words[-7] == "Second":
        victory(r, rounds, "BLU")
        continue

###### TEAM AND MERC STATS ######
s = Stats()
red_wins = 0
blu_wins = 0

mercs = []
redteam = []
bluteam = []
for mercname in mercnames:
    mercs.append(Merc(mercname))
    redteam.append(Merc(mercname))
    bluteam.append(Merc(mercname))

for r in rounds:
    s.total_rounds += 1
    red = get_class(r.red)
    blu = get_class(r.blu)
    for merc in mercs:
        if merc.name == r.red:
            redmerc = merc.id
        if merc.name == r.blu:
            blumerc = merc.id

    mercs[redmerc].total += 1
    mercs[blumerc].total += 1
    redteam[redmerc].total += 1
    bluteam[blumerc].total += 1
    if r.winner == "RED":
        s.red_wins += 1
        mercs[redmerc].wins += 1
        mercs[blumerc].losses += 1
        redteam[redmerc].wins += 1
        bluteam[blumerc].losses += 1
        redteam[redmerc].classtotals[blumerc] += 1
        redteam[redmerc].classwins[blumerc] += 1
        bluteam[blumerc].classlosses[redmerc] += 1
    elif r.winner == "BLU":
        s.blu_wins += 1
        mercs[blumerc].wins += 1
        mercs[redmerc].losses += 1
        bluteam[blumerc].wins += 1
        redteam[redmerc].losses += 1
        bluteam[blumerc].classtotals[redmerc] += 1
        bluteam[blumerc].classwins[redmerc] += 1
        redteam[redmerc].classlosses[blumerc] += 1

matchups = []
for i in range(len(mercnames)):
    for j in range(len(mercnames)):
        matchups.append([redteam[i], bluteam[j]])

print()
print("TOTAL STATS")
print("-----------")
for merc in mercs:
    merc.print()

print()
print("RED STATS")
print("---------")
for red in redteam:
    red.print()

print()
print("BLU STATS")
print("---------")
for blu in bluteam:
    blu.print()

print()
print(f"Games captured: {s.total_rounds}\nRED wins: {s.red_wins}\nBLU wins: {s.blu_wins}")

### PLOT ###
fig, axs = plt.subplots(2, 3, figsize=(16,9))

axs[0,1].pie([s.red_wins, s.blu_wins], labels=["RED", "BLU"], colors=[REDCOL, BLUCOL])
axs[0,1].set_title('Total Round Win % (Sample Size=' + str(s.total_rounds) + ')')

axs[0,0].axis('off')
axs[0,2].axis('off')

mercwins = []
mercwinslabels = []
for merc in mercs:
    mercwins.append(merc.wins)
    if merc.wins == 0:
        mercwinslabels.append('')
    else:
        mercwinslabels.append(merc.name)
axs[1,1].pie(mercwins, labels=mercwinslabels)
axs[1,1].set_title('Total Merc Win %')

bluwins = []
bluwinslabels = []
blulosses = []
for blu in bluteam:
    bluwins.append(blu.wins)
    blulosses.append(blu.losses)
    if blu.wins > s.max_wins:
        s.max_wins = blu.wins
    if blu.losses > s.max_wins:
        s.max_wins = blu.losses
    if blu.wins == 0:
        bluwinslabels.append('')
    else:
        bluwinslabels.append(blu.name)
axs[1,0].pie(bluwins, labels=bluwinslabels, radius=0.85)
axs[1,0].set_title('BLU Merc Win %', color=BLUCOL)

redwins = []
redwinslabels = []
redlosses = []
for red in redteam:
    redwins.append(red.wins)
    redlosses.append(red.losses)
    if red.wins > s.max_wins:
        s.max_wins = red.wins
    if red.losses >s.max_wins:
        s.max_wins = red.losses
    if red.wins == 0:
        redwinslabels.append('')
    else:
        redwinslabels.append(red.name)
axs[1,2].pie(redwins, labels=redwinslabels, radius=0.85)
axs[1,2].set_title('RED Merc Win %', color=REDCOL)

fig.tight_layout()
plt.savefig('data0_totalwins')

width = .24
halfwidth = width * .5
fig, axs = plt.subplots(figsize=(16, 8), ncols=2)
axs[0].bar(np.arange(9)+halfwidth, bluwins, width=width, align='center', color='green', label='BLU Wins')
axs[0].set_title("BLU Round Losses/Wins", color=BLUCOL)
axs[0].set_ylim(0, s.max_wins+1)
axs[0].set(xticks=np.arange(9), xticklabels=mercnames)
axs[0].bar(np.arange(9)-halfwidth, blulosses, width=width, color='red', label='BLU losses')
axs[0].legend()

axs[1].bar(np.arange(9)+halfwidth, redwins, width=width, align='center', color='green', label='RED Wins')
axs[1].set_title("RED Round Lossses/Wins", color=REDCOL)
axs[1].set(xticks=np.arange(9), xticklabels=mercnames)
axs[1].set_ylim(0, s.max_wins+1)
axs[1].bar(np.arange(9)-halfwidth, redlosses, width=width, color='red', label='RED losses')
axs[1].legend()

fig.tight_layout()
plt.savefig('data1_winslosses')

fig, axs = plt.subplots(9,9, figsize=(18,9))

##### MATCHUP STATS ######
ypos = 0
xpos = 0
for red in redteam:
    for i in range(len(red.classwins)):
        bluname = bluteam[xpos].name
        if red.classwins[i] == 0 and red.classlosses[i] == 0:
            axs[ypos,xpos].axis('off')
            if xpos == 0:
                axs[ypos][xpos].set_title("RED " + red.name + " vs. BLU " + bluname, fontsize=8)
            else:
                axs[ypos][xpos].set_title("vs. BLU " + bluname, fontsize=8)
            xpos += 1
            continue
        data = [red.classwins[i], red.classlosses[i]]
        if xpos == 0:
            axs[ypos][xpos].set_title("RED " + red.name + " vs. BLU " + bluname, fontsize=8)
        else:
            axs[ypos][xpos].set_title("vs. BLU " + bluname, fontsize=8)
        axs[ypos][xpos].pie(data, colors=[REDCOL, BLUCOL])
        xpos += 1
    ypos += 1
    xpos = 0

fig.tight_layout()
plt.savefig('data2_matchups')
