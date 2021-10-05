# Set base and totals which letters should add to
base = 6
matches = {444:[], 666:[]}

# Create dict (keys are letters, vals are letter index*6 with a's index being 1
keys = ["a","b","c","d","e","f","g","h","i","j","k","l","m",
        "n", "o","p","q","r","s","t","u","v","w","x","y","z"]
alphabet = {}
num = 1
for key in keys:
  alphabet[key] = str(num*base)
  num += 1

# Get file (defaults to /home/pete/words.txt)
f = input("Input file of words separated into lines: ")
print()
if f == "":
  f = "/home/pete/words.txt"
f = open(f, 'r')
words = f.read().splitlines()
f.close()

# For each word in file, get total
for word in words:
  word = word.lower()
  total = 0
  for c in word:
    if c.isalpha():
      total += int(alphabet[c])
  print(f"Word : {word}\nValue: {total}")

  # If word's total matches a specified total, add it to that dict entry's list
  for match in matches:
    if match == total:
      matches[total].append(word)

# Print every word which matched a specified total
for match in matches:
  for item in matches[match]:
    print(f"{match}: {item}")

# Print percentage information of words which matches specified totals
perc_total = 0
for match in matches:
  num = len(matches[match])
  perc = num / len(words) * 100
  perc_total += perc
  print(f"{num} words adding to {match} out of {len(words)} total words")
  print("Percentage of %d words: %.4f" % (match, perc))

print("Percentage of all matching words: %.4f" % perc_total)
