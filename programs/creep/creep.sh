#!/bin/bash

BASE="https://prnt.sc/"

# convert int to char and print
chr()
{
  printf \\$(printf '%03o' $1)
}

# get # of urls to read from user
echo -n "Enter # of urls to fetch: "
read n
if [[ ! $n =~ ^[0-9]+$ ]] ; then
  echo "Invalid #"
  exit
fi

# generate n number of random urls, place into 'out.txt'
rm out.txt
for((i=0; i<n; i++))
do
  r=$((RANDOM % 10000))
  c1=$((RANDOM % 26))
  c2=$((RANDOM % 26))
  c1=$((c1+97))
  c2=$((c2+97))
  printf '%s' "$BASE" >> out.txt
  chr $c1 >> out.txt
  chr $c2 >> out.txt
  printf '%04d\n' "$r" >> out.txt
done

# call wget on the urls in 'out.txt' and place the html files in 'urls'
cd urls
cat ../out.txt | xargs wget --wait=1 --random-wait

# get the image url from each html file, wget the .png and place in 'images'
cd ../images
for file in ../urls/*
do
    cat $file | grep DOC | sed 's/^.*meta property="og:image" content="//' | sed 's/".*//' | xargs wget --wait=1 --random-wait
done

# remove the html files from 'urls'
cd ..
rm urls/*

# remove dupliate images files from 'images'
rm images/*[0-9]

# remove empty image files from 'images'
cd images
ls -alh | awk '{if ($5 == "503"){print $9}}' | xargs rm
