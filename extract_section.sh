#! /bin/bash

while getopts f:v: flag
do
    case "${flag}" in
        f) filename=${OPTARG};;
        v) version=${OPTARG};;
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

if [ -z "$version" ]; then
    echo "Please specify a version using '-v'"
    exit 1
fi

echo "analyzing file $filename"
header="## v${version}"
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
