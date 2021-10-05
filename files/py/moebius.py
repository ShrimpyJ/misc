import turtle
import random
paletteMaker = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f']
color = []
while len(color) < 24:
	if (col := ''.join(['#', *random.choices(palleteMaker, k = 6)])) not in color:
		color.append(col)
print(color)
