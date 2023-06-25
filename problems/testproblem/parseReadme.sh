grep -P '^Input:|^Example \d+:|^Output:' README.md | while read line; do
    if [[ "$line" =~ Example\ \.* ]]; then
        echo example number = $line
    fi
    if [[ "$line" =~ "Input:" ]]; then
        echo input = $line
    fi
    if [[ "$line" =~ "Output:" ]]; then
        echo output = $line
    fi
done
