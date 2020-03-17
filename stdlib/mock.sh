#!/bin/sh
if [ "$#" -lt 1 ]; then
    echo "usage: $0 <header>..."
    exit 1
fi
for header in $@; do
    mkdir -p $(dirname $header)
    echo "system_include <$header>" > $header
done
