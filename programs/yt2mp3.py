#script to convert list of songs to mp3 files
from bs4 import BeautifulSoup as bs
from pytube import YouTube
import requests
import moviepy.editor as mp
from subprocess import call
import os.path

songlist = [] 
#open input file and read lines
with open('music.txt', encoding='ISO-8859-1') as f:
    lines = f.readlines()

#the youtube search url. songs will be appended to this
base = "https://www.youtube.com/results?search_query="

for line in lines:
    #check if mp3 file already exists
    name = line.replace("\n","")
    name = name + ".mp3"
    if os.path.isfile(name):
        print("File: " + name + " already exists. Moving on...\n")
        continue

    #print current song
    print("\n\nNow downloading: " + line)

    #parse current song and make ready for youtube url
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
    final = 'https://www.youtube.com' + vid['href']

    #search video descriptions to find official uploads
    songname = line.split('- ')[1]
    songname = songname.strip()
    songname = songname.lower()
    songname = songname[0:3]
    songartist = line.split(' -')[0]
    songartist = songartist.strip()
    songartist = songartist.lower()
    songartist = songartist[0:3]
    i = 0
    for i in range(20):
        #get current video info
        temp = soup.find_all('div', class_="yt-lockup-content")[i]
        info = temp.get_text("\n")
        title = info.split("\n")[0]
        artist = info.split("\n")[2]
        desc = info.split("\n")[4]

        title = title.strip()
        title = title.lower()
        title = title[0:3]

        artist = artist.strip()
        artist = artist.lower()
        artist = artist[0:3]

        #literal string "Provided to", to be matched in description
        desc = desc[0:11]

        #if official upload, grab that video link instead
        if desc == "Provided to" and title == songname and artist == songartist:
            print("Official upload found at link",i+1)
            print(info)
            vid = soup.find_all('a',attrs={'class':'yt-uix-tile-link'})[i]
            final = 'https://www.youtube.com' + vid['href']
            break
        else:
            i += 1

    #download as mp4
    yt = YouTube(final)
    video = yt.streams.first()
    video.download('./')

    #correct "problem characters" for reading .mp4 files
    sng = yt.title
    print(".mp4 is: " + sng)
    sng = sng.replace(",","")
    sng = sng.replace("'","")
    sng = sng.replace(".","")
    sng = sng.replace("\"","")
    sng = sng.replace(":","")
    sng = sng.replace("*","")

    #convert mp4 to mp3
    clip = mp.VideoFileClip(sng + ".mp4")
    clip.audio.write_audiofile(name)

print("All files successfully downloaded!\n")
#remove mp4 files
call('rm *.mp4', shell=True)
#move mp3 files to songs folder
call('mv *.mp3 ../songs', shell=True)
