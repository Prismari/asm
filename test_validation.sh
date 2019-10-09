#!/usr/bin/env bash

FILES_ERR=champ_test/checker_test_files/error/*.s
FILES_VAL=champ_test/checker_test_files/valid/*.s
FILES_VALID=champ_test/checker_test_files/valid2/*.s
CYAN='\033[0;36m'
GREEN='\033[0;32m'
YEL='\033[1;32m'
NC='\033[0m'

for f in $FILES_ERR
do
  echo "${CYAN}exec test - $f${NC}"
  echo "${GREEN}Our asm ${NC}"
./asm $f
echo "${GREEN}Original${NC}"
./champ_test/asm $f

done
rm champ_test/checker_test_files/error/*.cor


echo "\n${YEL} VALID_ARGS ${NC} \n"

#
#for i in $FILES_VAL
#do
#  echo "${CYAN}exec test - $i${NC}"
#  echo "${GREEN}Our asm ${NC}"
#./asm $i
#echo "${GREEN}Original${NC}"
#./champ_test/asm $i
#
#done
#rm /Users/aestella/42/corewar/asm/champ_test/checker_test_files/valid/*.cor

#
#for c in $FILES_VALID
#do
#  echo "${CYAN}exec test - $c${NC}"
#  echo "${GREEN}Our asm ${NC}"
#./asm $c
#echo "${GREEN}Original${NC}"
#./champ_test/asm $c
#
#done
#rm /Users/aestella/42/corewar/asm/champ_test/checker_test_files/valid2/*.cor