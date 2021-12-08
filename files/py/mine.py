from random import *

minechance = 0.9

class Board:
  def __init__(self, width, height):
    self.width = width
    self.height = height
    self.tiles = []
    self.nummines = 0

  def print(self):
    for i in range(self.height):
      for j in range(self.width):
        print(self.tiles[i][j], end='')
      print()

def generate_tiles(width, height):
  board = Board(width, height)
  ntiles = width*height
  for i in range(height):
    row = []
    for j in range(width):
      if randint(0, 100) <= minechance*100:
        board.nummines += 1
        row.append('x')
      else:
        row.append('.')
    board.tiles.append(row)
  return board

def find_mines(tile, i, j):
  mines = 0
  # Up
  if i != 0:
    if b.tiles[i-1][j] == 'x':
      mines += 1

  # Down
  if i != b.height-1:
    if b.tiles[i+1][j] == 'x':
      mines += 1

  # Left
  if j != 0:
    if b.tiles[i][j-1] == 'x':
      mines += 1

  # Right
  if j != b.width-1:
    if b.tiles[i][j+1] == 'x':
      mines += 1

  # Up Left
  if i != 0 and j != 0:
    if b.tiles[i-1][j-1] == 'x':
      mines += 1

  # Up Right
  if i != 0 and j != b.width-1:
    if b.tiles[i-1][j+1] == 'x':
      mines += 1

  # Down Left
  if i != b.height-1 and j != 0:
    if b.tiles[i+1][j-1] == 'x':
      mines += 1

  # Down Right
  if i != b.height-1 and j != b.width-1:
    if b.tiles[i+1][j+1] == 'x':
      mines += 1

  if mines > 0:
    b.tiles[i][j] = mines


def get_nums(b):
  for i in range(b.height):
    for j in range(b.width):
      if b.tiles[i][j] == '.':
        find_mines(b.tiles[i][j], i, j)

b = generate_tiles(9, 9)
get_nums(b)
b.print()
