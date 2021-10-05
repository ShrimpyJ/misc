#!/bin/bash

# remove duplicate image files from 'images'
rm images/*[0-9]

# remove empty image files from 'images'
cd images
ls -alh | awk '{if ($5 == "503"){print $9}}' | xargs rm
