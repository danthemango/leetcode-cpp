# compiles each cpp file, then runs it
# TODO consider doing something with the failure conditions, right now I'm just printing it out
for file in *.cpp; do
    echo $file
    g++ $file -o currentTest.exe && ./currentTest.exe && rm currentTest.exe
    echo
done
