import sys

### Node ###
class Node:
	def __init__(self, depth, num_children, parent, children, val):
		self.depth = depth
		self.num_children = num_children
		self.parent = parent
		self.children = []
		self.val = val
############

##### Trie #####
class Trie:
	def __init__(self, num_layers, num_items, head):
		self.num_layers = 0
		self.num_items = 0
		self.head = Node(0, 0, None, [], None)
	
	### Insert ###
	def insert(self, word):

		n = self.head
		for i in range(len(word)):
			substr = word[0:i+1]
			j = 0
			for c in n.children:
				if c.val == substr:
					break
				j += 1

			if j == n.num_children:
				new = Node(len(substr), 0, n, None, substr)
				n.num_children += 1
				n.children.append(new)
			n = n.children[j]
	##############

	#### Find ####
	def find(self, word):
		n = self.head
		for i in range(len(word)):
			substr = word[0:i+1]
			j = 0
			for c in n.children:
				if c.val == substr:
					break
				j += 1

			if j == n.num_children:
				raise ValueError('Could not find node ' + word + ' in trie')
			n = n.children[j]
		return n
	#################

################
##### read_file #####
def read_file(f):
	f = open(f, 'r')
	lines = f.read().splitlines()
	f.close()
	return lines
#####################

###### Main #####
if len(sys.argv) != 2:
	raise ValueError('Need 2 arguments: trie.py FILE_NAME')

f = sys.argv[1]
lines = read_file(f)

T = Trie(0, 0, None)

for line in lines:
	T.insert(line)

for line in lines:
	n = T.find(line)
#################
