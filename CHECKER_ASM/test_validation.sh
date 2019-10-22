#!/usr/bin/env bash

ZERO=$(wc -l < nothing)
PATH_CHECKER=../champ_test/checker_test_files/
PATH_OUR_ASM=../
PATH_ORIG_ASM=../champ_test

FILES_ERR=${PATH_CHECKER}error/*.s
FILES_VAL=${PATH_CHECKER}valid/*.s

OUTPUT_ERR=${PATH_CHECKER}error/*.cor
OUTPUT_VALID=${PATH_CHECKER}valid/*.cor

OUTPUT_OUR=/our_output
OUTPUT_ORIG=/origin_output
CYAN='\033[0;36m'
GREEN='\033[0;32m'
RED='\033[0;31m'
YEL='\033[1;32m'
NC='\033[0m'

echo "\n${YEL}ERROR_ARGS ${NC} \n"

for f in $FILES_ERR
do

  ${PATH_OUR_ASM}/asm $f > error_output
  grep 'Writing output program to' error_output > grep_result
  ERROR_SIZE=$(wc -l < grep_result)
  rm grep_result
  if [ "$ERROR_SIZE" == "$ZERO" ]; then
    echo "${GREEN}OK${NC}"
  else
    echo "${RED}KO${NC}   By test - $f"
  fi
done
rm -rf ${PATH_CHECKER}/*.cor


echo "\n${YEL}VALID_ARGS ${NC} \n"


for i in $FILES_VAL
do
${PATH_OUR_ASM}/asm $i > test_valid_our
cp $OUTPUT_VALID ./our_output_file

${PATH_ORIG_ASM}/asm $i > test_valid_origin
cp $OUTPUT_VALID ./orig_output_file


if diff our_output_file orig_output_file &> /dev/null; then
    echo "bytecode -> ${GREEN}OK${NC}"
  else
    echo "${CYAN}exec test - $i${NC}${GREEN}"
    echo "${RED}KO${NC}"
fi


if diff test_valid_origin test_valid_our &> /dev/null; then
  echo "error handling -> ${GREEN}OK${NC}"
  else
    echo "${CYAN}exec test - $i${NC}"
    echo "${RED}KO${NC}"
    echo "${GREEN}Our asm ${NC}"
    cat test_valid_our
    echo "${GREEN}Original${NC}"
    cat test_valid_origin
    echo "\n"
  fi


rm ./orig_output_file
rm ${PATH_CHECKER}valid/*.cor

done

