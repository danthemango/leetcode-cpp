#!/usr/bin/bash
# create quick scaffolding for a new leetcode problem runner

newProblem=$1

if [ -z $newProblem ]; then
    echo 'usage: bash createNew.sh <problem-name>'
    exit
fi
newProblem=$(echo $newProblem | sed 's/https:\/\/leetcode.com\/problems\///' | sed 's/\/submissions\/.*//' | sed 's/\/$//')

echo "mkdir $newProblem"
mkdir $newProblem
echo creating new files:
echo $(pwd)/$newProblem/Solution.h | sed 's/\/c/C:/' | sed 's/\//\\/g'
touch $newProblem/Solution.h
echo '#include "../../common/common.h"' >> $newProblem/Solution.h
echo $(pwd)/$newProblem/readme.md | sed 's/\/c/C:/' | sed 's/\//\\/g'
touch $newProblem/readme.md
bash createSubMake.sh $newProblem
