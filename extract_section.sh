#! /bin/bash

while getopts f:t: flag
do
    case "${flag}" in
        f) filename=${OPTARG};;
        t) title=${OPTARG};;
    esac
done

if [ -z "$filename" ]; then
    echo "Please specify a filename using '-f'"
    exit 1
fi

if [ ! -f $filename ]; then

    echo "File does not exist: ${filename}"
    exit 1

fi

if [ -z "$title" ]; then
    echo "Please specify a title using '-t'"
    exit 1
fi

echo "analyzing file $filename"
header="## ${title}"
echo "checking for <${header}>"

foundTitle=false
while read line; do
    if [ "$foundTitle" == false ]; then
        if [[ "$line" =~ ^${header} ]]; then
            echo "first line: $line"
            foundTitle=true
        else
            echo "pre-section line"
        fi
    else
        if [[ $line = '## '* ]]; then
            echo "start of next section"
            break
        else
            echo "within section: $line"
        fi
    fi
done <$filename
