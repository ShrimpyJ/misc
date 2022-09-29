# [ War Room       ]
# [ C-Suite        ]
# [ Administration ]
# [ Security       ]
# [ Legal          ]
# [ HR             ]
# [ Laboratory     ]
# [ Medical        ]
# [ Servers        ]
# [ Risk Management]
# [ R&D            ]
# [ R&D            ]
# [ R&D            ]
# [ R&D            ]
# [ Logistics      ]
# [ Logistics      ]
# [ Logistics      ]
# [ Logistics      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Financial      ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]
# [ Data entry     ]

from random import *

FIRST_NAMES = []
LAST_NAMES = []
ALPHABET = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
            "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]

# Physical accesses (keycard):
#   War room
#   C-Suite
#     CEO
#     COO
#     CFO
#     CIO
#     CTO
#   President's Office
#   Vice President's Office
#   Administration
#   Legal floor
#   Medical bay
#   Laboratory
#   Server floor
#   Security

# Digital access (hardware key):
#   Root server
#   Server
#   Root database
#   Database
#   Legal
#   Medical
#   Laboratory
#   Security
#   Human Resources


class Employee():
    def __init__(self, privilege):
        self.name = randomName()

class Floor():
    def __init__(self, number, department):
        self.number = number
        self.department = department
        self.manager = Employee()

class HiRise():
    floors = []

def randomName():
    first = FIRST_NAMES[randint(0, len(FIRST_NAMES)-1)]
    middle = ALPHABET[randint(0, len(ALPHABET)-1)]
    last = LAST_NAMES[randint(0, len(LAST_NAMES)-1)]
    return first + ' ' + middle + '. ' + last

f = open("first-names.txt", "r")
lines = f.read().splitlines()
for line in lines:
    FIRST_NAMES.append(line)
f.close()

f = open("last-names.txt", "r")
lines = f.read().splitlines()
for line in lines:
    LAST_NAMES.append(line)
f.close()

for i in range(0, 10):
    name = randomName()
    print(name)
