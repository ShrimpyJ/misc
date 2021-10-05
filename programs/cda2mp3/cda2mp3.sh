#!/bin/bash
for i in *.flac ; do
	ffmpeg -i "$i" -acodec libmp3lame -ac 1 -ar 44100 "${i%.flac}".mp3
done
