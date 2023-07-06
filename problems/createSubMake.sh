# create temporary makefile in subdirectory for testing

newProblem=$1

if [ -z $newProblem ]; then
    echo 'usage: bash createSubMake.sh <problem-name>'
    exit
fi

if ! [ -d $newProblem ]; then
    echo "directory '$newProblem' not found"
    exit 1
fi

# remove trailing slash if necessary
newProblem=$(basename $newProblem)

SUBMAKE=$newProblem/Makefile
touch $SUBMAKE
echo "BASENAME=$newProblem" > $SUBMAKE
echo "run: runner.exe" >> $SUBMAKE
printf "\tmake -C .. \$(BASENAME).run\n" >> $SUBMAKE
echo "runner.exe:" >> $SUBMAKE
printf "\tmake -C .. \$(BASENAME)/runner.exe\n" >> $SUBMAKE
