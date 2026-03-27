#!/bin/sh

GRIT=/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit
$GRIT font16.png -ftb -fh! -gTFF00FF -gt -gB8 -m!

for file in *.bin; do
    mv -- "$file" "${file%.bin}"
done

for file in *.img; do
    mv -- "$file" "${file%.img}".fnt
done

mv *.pal *.fnt ../nitrofiles/fnt