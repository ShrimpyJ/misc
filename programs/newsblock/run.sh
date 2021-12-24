#!/bin/bash

### Using a list of search queries, add any (non-YouTube)          ###
### channel which appears in the results page to a blocklist file  ###

blocklist="blocklist.txt"
queries="queries.txt"
jsfile="channels.js"

# Download HTML pages for each query in the queries file
cat $queries | sed 's/^/https:\/\/www.youtube.com\/results?search_query=/' | xargs wget

# Find non-YouTube channels in each HTML file and place into the blocklist
find results* |
xargs awk 'BEGIN {FS=":"} {for(i=1; i<=NF; i++) {if($i=="{\"url\"") print $(i+1)}}' |
grep "/user/" | sort | uniq |
sed 's/\/user\///g' | sed 's/,"webPageType"//g' |
awk 'BEGIN {FS=" "} {if ($1!="\"YouTube") print $0}' >> $blocklist

# Remove redundant channels from blocklist
cat $blocklist | sort | uniq > tmp.txt
mv tmp.txt $blocklist

# Remove HTML file(s)
rm results*

# Create .js file with array of channels from the blocklist
cp $blocklist $jsfile
sed -i 's/$/,/g' $jsfile
echo "var channels = [" > tmp && cat $jsfile >> tmp && mv tmp $jsfile
echo "];" >> $jsfile
