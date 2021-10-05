# Tabber

1. Write guitar tabs as a formatted series of characters
2. Save the file with the extension .tabr
3. Run Tabber on the .tabr file to have in converted into an ASCII .txt file

## Overview

- Start with a header which contains:
 * Song name (optional)
 * Artist name (optional)
 * Album name (optional)
 * Release year (optional)
 * String tunings from lowest to highest (required)
- Each line is a measure

## Detailed overview

Header info should be at the beginning of the .tabr file. Possible info is song, artist, album, year, and tuning, though **tuning is required.**

Simply type the info label (case-insensitive) followed by a **:** with **no space between the label or :**. Then type the info itself following the **:** (does not matter if spaces are between the **:** and info).

**The only required piece of info is the tuning.** The other info can be listed in **any order** but will always appear in the same order in the output. See the example below (ignore the backticks if viewing raw .md file).

`song:tabr example`  
`artist:Alexander Brock`  
`album:tabr tutorial`  
`year:2021`  
`tuning:eadgbe`  

If you want to do sharp notes, simply put a **#** after the note. **For flat notes, put an underscore instead of a _b_ since _b_ will be interpreted as a note.**
