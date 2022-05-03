from random import *

PRESIDENTS = []
YEAR = 1788
DEATHS = ["FOOD POISONING", "ASSASSINATION", "HEART FAILURE", "GENDER DYSPHORIA",
        "ALCOHOLISM", "PEASANT REVOLT", "BLOOD CLOTS", "CEREBRAL HEMORRHAGE",
        "PRION DISEASE", "HANGING", "HOUSE FIRE", "GASTROENTERITIS"]

class President:
    def __init__(self):
        self.name = self.setName()
        self.children = []
        self.alive = True

    def setName(self):
        f = open('male_first.txt')
        names = f.read().splitlines()
        f.close()
        first = names[randint(0, len(names)-1)]

        f = open('last.txt')
        names = f.read().splitlines()
        f.close()
        last = names[randint(0, len(names)-1)]

        name = first + ' ' + last
        return name
    
    def live(self, years):
        global YEAR
        for i in range(0, years):
            print(f"YEAR {YEAR}: ", end="")
            print(self.name, end="")
            diesInOffice = randint(0, 45*8)
            if diesInOffice < 8:
                print(" DIES IN OFFICE FROM " + DEATHS[randint(0, len(DEATHS)-1)])
                self.alive = False
                return i
            print()
            YEAR += 1

yearsToServe = 4
for i in range(0, 99):
    p = President()
    yearsServed = p.live(yearsToServe)
    PRESIDENTS.append(p)

    # Possible re-election
    if randint(0, 100) < 45 and p.alive:
        yearsToServe = 4
        yearsServed = p.live(yearsToServe)

    if not p.alive:
        yearsToServe = 4 - yearsServed
    else:
        yearsToServe = 4
