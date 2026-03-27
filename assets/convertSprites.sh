#!/bin/sh

GRIT=/opt/wonderful/thirdparty/blocksds/core/tools/grit/grit

$GRIT botonContinue.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
$GRIT botonPause.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
$GRIT botonQuit.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
$GRIT botonStart.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
#$GRIT gameLogo.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
$GRIT meteorite.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
$GRIT FlyingCat.png -ftb -fh! -gTFF00FF -gt -gB8 -m!
$GRIT Star.png -ftb -fh! -gTFF00FF -gt -gB8 -m!


for file in *.bin; do
    mv -- "$file" "${file%.bin}"
done


mv *.pal *.img ../nitrofiles/sprite
