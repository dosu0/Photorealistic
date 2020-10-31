#!/bin/sh
echo "WARNING: This process requires git"
echo "WARNING: this will overwrite the libraries and may take a long time"
echo "Are you sure you want to continue? (y/n)"
read ans

if [ ans = "y" ]
then
    git pull
    git merge
fi


