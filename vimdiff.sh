#!/bin/zsh

CHAMP="helltrain.cor"
DUMP=-d
CNBR=10000

vimdiff <(tail -n 64 <( ./corewar -n champions/$CHAMP $DUMP $CNBR ) ) <(tail -n 64 <( $HOME/Desktop/corewar/corewar champions/$CHAMP $DUMP $CNBR ) | cut -c10-999 )
