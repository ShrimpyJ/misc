#script to convert list of songs to mp3 files
from bs4 import BeautifulSoup as bs
from pytube import YouTube
import requests
import moviepy.editor as mp
from subprocess import call
import os.path
from time import sleep
import time
import sys
import threading
import itertools


#def loading():
#    print("\n")
#    for x in range(1000):
#        if done:
#            break
#        sys.stdout.write("\rDownloading mp4%s" % ("."*x))
#        sys.stdout.flush()
#        time.sleep(0.1)
#    sys.stdout.write('\nDone!     ')

songlist = [] 
#open input file and read lines
with open('music.txt', encoding='ISO-8859-1') as f:
    lines = f.readlines()

#the youtube search . songs will be appended to this
base = "https://www.youtube.com/results?search_query="

for line in lines:
    #check if mp3 file already exists
    done = False
    name = line.replace("\n","")
    name = name + ".mp3"
    if os.path.isfile(name):
        print("File: " + name + " already exists. Moving on...\n")
        continue

    #print current song
    print("\n\n\n\nCurrently working on: " + line)

    #parse current song and make ready for youtube 
    song = line.replace("-","+")
    song = song.replace(" ", "+")
    song = song + "+topic"

    #search youtube for current song
    r = requests.get(base + song)
    
    #extract html of search results page
    page = r.text
    soup = bs(page,'html.parser')
    
    #grab first video link regardless of description
    vid = soup.find('a',attrs={'class':'yt-uix-tile-link'})
    #if failure
    while not vid:
        print("OOPSY POOPSY\n")
        r = requests.get(base + song)
        page = r.text
        soup = bs(page,'html.parser')
        vid = soup.find('a',attrs={'class':'yt-uix-tile-link'})
    final = 'https://www.youtube.com' + vid['href']

    #get short sample strings of song name and artist
    if line.find('-') != -1:
        songname = line.split('- ')[1]
        songartist = line.split(' -')[0]
    else:
        songname = line
        songartist = line
    songname = songname.strip()
    songname = songname.lower()
    if songname.startswith("the "):
        songname = songname.replace("the ","")
    songname = songname[0:3]
    songartist = songartist.strip()
    songartist = songartist.lower()
    if songartist.startswith("the "):
        songartist = songartist.replace("the ","")
    songartist = songartist[0:3]

    #search video descriptions to find official uploads
    i = 0
    for i in range(10):
        #get current video info
        temp = soup.find_all('div', class_="yt-lockup-content")[i]
        info = temp.get_text("\n")
        title = info.split("\n")[0]
        artist = info.split("\n")[2]
        desc = info.split("\n")[4]

        title = title.strip()
        title = title.lower()
        if title.startswith('the '):
            title = title.replace("the ","")
        title = title[0:3]

        artist = artist.strip()
        artist = artist.lower()
        if artist.startswith('the '):
            artist = artist.replace("the ","")
        artist = artist[0:3]

        #literal string "Provided to", to be matched in description
        desc = desc[0:11]

        #if official upload, grab that video link instead
        if desc == "Provided to" and title == songname and artist == songartist:
            print("\tOfficial upload found at link",i+1)
            print("\t--------------------------------")
            print(info)
            print("\t--------------------------------")
            vid = soup.find_all('a',attrs={'class':'yt-uix-tile-link'})[i]
            final = 'https://www.youtube.com' + vid['href']
            break
        else:
            i += 1

    #download as mp4
    #print("\nDownloading .mp4...")
    #t = threading.Thread(target=loading)
    #t.start()
    yt = YouTube(final)
    video = yt.streams.first()
    video.download('./')
    done = True

    #correct "problem characters" for reading .mp4 files
    sng = yt.title
    print("\n\n.mp4 is: " + sng)
    sng = sng.replace(",","")
    sng = sng.replace("'","")
    sng = sng.replace(".","")
    sng = sng.replace("\"","")
    sng = sng.replace("/","")
    sng = sng.replace(":","")
    sng = sng.replace("*","")

    #convert mp4 to mp3
    print("Converting to .mp3...")
    clip = mp.VideoFileClip(sng + ".mp4")
    clip.audio.write_audiofile(name)

print("All files successfully downloaded!\n")
#remove mp4 files
call('rm *.mp4', shell=True)
#move mp3 files to songs folder
call('mv *.mp3 ../songs', shell=True)
