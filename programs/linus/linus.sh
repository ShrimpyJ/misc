#!/bin/bash

# Step 1: Find and save each URL of emails by Linus Torvalds to a text file.
# Step 2: Download each email URL as an HTML file saved to a subdirectory in html
# Step 3: 

base="https://lkml.org/lkml"
urls="urls.txt"
start_year=1996
end_year=2022
cur_year=$start_year
start_month=1
start_day=1

# Step 1: Find every e-mail authored by Linus Torvalds.
#         Save each URL to the specified text file.

# If possible, resume from last URL grabbed
if [[ $1 -le 1 ]]; then
  last=$(tail -n 1 $urls)
  if [[ $? -ne 1 ]]; then
    start_year=$(echo $last | awk 'BEGIN {FS="/"} {print $5}')
    start_month=$(echo $last | awk 'BEGIN {FS="/"} {print $6}')
    start_day=$(echo $last | awk 'BEGIN {FS="/"} {print $7}')
    echo Resuming from $base/$start_year/$start_month/$start_day
  fi
  
  # Year
  for (( i = $start_year; i <= $end_year; i++ )); do
    # Month
    for (( j = $start_month; j <= 12; j++ )); do
      # Day
      for (( k = $start_day; k <= 31; k++ )); do
        url=$base/$i/$j/$k/

        echo "working on $url"
  
        wget -O index.html $url
        grep "calendar" index.html | sed 's/td/\\\n/g' | grep "Linus Torvalds" |
          awk '{printf("https://lkml.org%s\n", $3)}' |
          sed 's/href="//g' | sed 's/".*$//g' >> $urls
      done
    done
  done
fi

# Ensure only unique URLs are in the file
awk '!seen[$0]++' $urls > tmp.txt
cp tmp.txt $urls
rm tmp.txt


# Step 2: Download each URL in the URL file.
#         These are the plain HTML files for
#         each email.
if [[ $1 -le 2 ]]; then
  lines=$(cat $urls)
  mkdir html
  cd html
  start=$(pwd);
  for line in $lines; do
    # Build directory path
    dir1=$(echo $line | awk 'BEGIN {FS="/"} {print $5}')
    dir2=$(echo $line | awk 'BEGIN {FS="/"} {print $6}')
    dir3=$(echo $line | awk 'BEGIN {FS="/"} {print $7}')
    file=$(echo $line | awk 'BEGIN {FS="/"} {print $8}')
    path=$(echo $dir1/$dir2/$dir3)
    file_path=$(echo $path/$file)
  
    # Skip file if exists
    find $file_path > /dev/null
    if [[ $? -eq 0 ]]; then
      echo File $file_path exists, continuing...
      continue
    fi
  
    # Navigate to or create appropriate directory
    mkdir $dir1; cd $dir1;
    mkdir $dir2; cd $dir2;
    mkdir $dir3; cd $dir3;

    # Download HTML
    wget $line

    # Trim everything out of the HTML file except the message
    grep "articleBody" $file > tmp.txt
    cp tmp.txt $file
    rm tmp.txt
    cd $start
  done
fi
