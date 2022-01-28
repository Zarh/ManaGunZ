#!/bin/bash
for i in *.pkg; do
    k=$i
    # Remove version.
    if [[ "$i" == *"_"*".pkg"* ]]; then
	    k="${k/"_"**".pkg"/}_nightly.pkg"
    fi
    # Rename file.
    if [[ "$k" != "$i" ]]; then
        mv "${i}" "${k}"
    fi
done
