# create quick scaffolding for a new leetcode problem runner

newProblem=$1

if [ -z $newProblem ]; then
    echo 'usage: bash createNew <problem-name>'
    exit
fi

mkdir $newProblem
touch $newProblem/Solution.h
echo '#include "../../common/common.h"' >> $newProblem/Solution.h
touch $newProblem/readme.md
cp sample_makefile $newProblem/Makefile
