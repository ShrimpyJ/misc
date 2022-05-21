from random import *
from os import system

MINNUM = 1
MAXNUM = 500
MINOPS = 6
MAXOPS = 8
MINEXP = 2
MAXEXP = 3

def add():
    return " + "
def sub():
    return " - "
def div():
    return " / "
def mul():
    return " * "
def exp():
    return " ^ "

def getFormula():
    formula = ""
    ops = [add, sub, div, mul, exp]
    lops = len(ops)-1
    nops = randint(MINOPS, MAXOPS)
    lastop = ""
    formula += "( "
    for i in range(0, nops):
        # Get operator
        if lastop == div:
            while op == div:
                op = ops[randint(0, lops)]
        elif lastop == exp:
            while op == exp:
                op = ops[randint(0, lops)]
        else:
            op = ops[randint(0, lops)]

        # Get number
        if lastop == exp:
            n = randint(MINEXP, MAXEXP)
        else:
            n = randint(MINNUM, MAXNUM)

        lastop = op
        lastn = n

        formula += str(n)
        formula += op()
    
    if lastop == exp:
        n = randint(MINEXP, MAXEXP)
    else:
        n = randint(MINNUM, MAXNUM)
    formula += str(n) + " )"
    return formula

def formulaToPython(formula):
    parsed = ""
    items = formula.split(" ")
    skip = False

    for i, item in enumerate(items):
        if skip:
            skip = False
            continue

        if item == "^":
            parsed += "pow(" + items[i-1] + ", " + items[i+1] + ") "
            skip = True
        elif i != len(items)-1 and items[i+1] != "^":
            parsed += item + " "

    parsed += ")"
    return parsed

def formulaToTex(formula):
    parsed = []
    items = formula.split(" ")

    skip = False
    for i, item in enumerate(items):
        if skip > 0:
            skip -= 1
            continue

        if item == "/":
#            if i > 2 and parsed[i-2] == "^":
            # Look ahead for exponents
            if items[i+2] == "^":
                parsed.insert(i-1, "\\frac")
                parsed[i] = "{" + parsed[i] + "}"
                parsed.append("{" + items[i+1] + items[i+2] + items[i+3] + "}")
                skip = 3
            # Look behind for exponents
            elif i > 3 and parsed[i-2] == "^":
                parsed.insert(i-3, "\\frac")
                parsed[i-2] = "{" + parsed[i-2] + parsed[i-1] + parsed[i] + "}"
                parsed[i-1] = ""
                parsed[i] = ""
                parsed.append("{" + items[i+1] + "}")
                skip = 1
            else:
                parsed.insert(i-1, "\\frac")
                parsed[i] = "{" + parsed[i] + "}"
                parsed.append("{" + items[i+1] + "}")
                skip = 1
        else:
            parsed.append(item)

    ret = ""
    for i, p in enumerate(parsed):
        if i == 0 or i == len(parsed)-1:
            continue
        ret += p + " "
    return ret

def createTexDocument(formula, ans):
    f = open("formula.tex", "w")
    f.write("\\documentclass{article}\n")
    f.write("\\usepackage{amsmath}\n\n")
    f.write("\\begin{document}\n")
    f.write("\\begin{align*}\n")
    f.write("  " + formula + " = " + str(ans) + "\n")
    f.write("\\end{align*}\n\n")
    f.write("\\end{document}\n")
    f.close()

numerator = getFormula()
print(numerator)
pythonNumerator = formulaToPython(numerator)
print(pythonNumerator)
texNumerator = formulaToTex(numerator)
print(texNumerator)

denominator = getFormula()
print(denominator)
pythonDenominator = formulaToPython(denominator)
print(pythonDenominator)
texDenominator = formulaToTex(denominator)
print(texDenominator)

ans = eval(pythonNumerator + "/" + pythonDenominator)
print(ans)
formula = "\\frac{" + texNumerator + "}" + "{" + texDenominator + "}"
createTexDocument(formula, ans)

cmd = 'pdflatex formula.tex && mupdf formula.pdf && rm *.log *.aux'
system(cmd)
