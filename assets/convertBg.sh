#!/bin/sh

GRIT=/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

$GRIT gameLogo.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs
$GRIT spaceBackground.png -ftb -fh! -gTFF00FF -gt -gB8 -mR8 -mLs

for file in *.bin; do
    mv -- "$file" "${file%.bin}"
done

mv *.pal *.img *.map ../nitrofiles/bg
