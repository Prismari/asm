#!/bin/bash
RED="\033[1;31m"
GREEN="\033[1;32m"
RESET="\033[0m"
echo $RED"Our asm 1"$RESET
./asm champ_test/checker_test_files/error/comment_len_2049.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/comment_len_2049.s
echo ""

echo $RED"Our asm 2"$RESET
./asm champ_test/checker_test_files/error/direct_param_no_value.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/direct_param_no_value.s
echo ""

echo $RED"Our asm 3"$RESET
./asm champ_test/checker_test_files/error/four_arg_malloc_free_pointer_error.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/four_arg_malloc_free_pointer_error.s
echo ""

echo $RED"Our asm 4"$RESET
./asm champ_test/checker_test_files/error/header_double_comments.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_double_comments.s
echo ""

echo $RED"Our asm 5"$RESET
./asm champ_test/checker_test_files/error/header_double_names.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_double_names.s
echo ""

echo $RED"Our asm 6"$RESET
./asm champ_test/checker_test_files/error/header_max_comment.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_max_comment.s
echo ""

echo $RED"Our asm 7"$RESET
./asm champ_test/checker_test_files/error/header_max_name.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_max_name.s
echo ""

echo $RED"Our asm 8"$RESET
./asm champ_test/checker_test_files/error/header_nl.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_nl.s
echo ""

echo $RED"Our asm 9"$RESET
./asm champ_test/checker_test_files/error/header_nl_unclosed.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_nl_unclosed.s
echo ""

echo $RED"Our asm 10"$RESET
./asm champ_test/checker_test_files/error/header_null_name.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/header_null_name.s
echo ""

echo $RED"Our asm 11"$RESET
./asm champ_test/checker_test_files/error/label_contain_badchar.s
echo $GREEN"Original"$RESET
./champ_test/asm
echo ""

echo $RED"Our asm 12"$RESET
./asm champ_test/checker_test_files/error/label_error_1.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_error_1.s
echo ""

echo $RED"Our asm 13"$RESET
./asm champ_test/checker_test_files/error/label_error_2.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_error_2.s
echo ""

echo $RED"Our asm 14"$RESET
./asm champ_test/checker_test_files/error/label_error_3.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_error_3.s
echo ""

echo $RED"Our asm 15"$RESET
./asm champ_test/checker_test_files/error/label_invalidname.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_invalidname.s
echo ""

echo $RED"Our asm 16"$RESET
./asm champ_test/checker_test_files/error/label_noending.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_noending.s
echo ""

echo $RED"Our asm 17"$RESET
./asm champ_test/checker_test_files/error/label_space.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_space.s
echo ""

echo $RED"Our asm 18"$RESET
./asm champ_test/checker_test_files/error/label_without_double_dot_at_the_end.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/label_without_double_dot_at_the_end.s
echo ""

echo $RED"Our asm 19"$RESET
./asm champ_test/checker_test_files/error/name_len_129.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/name_len_129.s
echo ""

echo $RED"Our asm 20"$RESET
./asm champ_test/checker_test_files/error/op_double_operation_on_single_line.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/op_double_operation_on_single_line.s
echo ""

echo $RED"Our asm 21"$RESET
./asm champ_test/checker_test_files/error/op_extra.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/op_extra.s
echo ""

echo $RED"Our asm 22"$RESET
./asm champ_test/checker_test_files/error/op_extreme.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/op_extreme.s
echo ""

echo $RED"Our asm 23"$RESET
./asm champ_test/checker_test_files/error/op_no_code.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/op_no_code.s
echo ""

echo $RED"Our asm 24"$RESET
./asm champ_test/checker_test_files/error/param_badtypes.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_badtypes.s
echo ""

echo $RED"Our asm 25"$RESET
./asm champ_test/checker_test_files/error/param_commas.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_commas.s
echo ""

echo $RED"Our asm 26"$RESET
./asm champ_test/checker_test_files/error/param_direct_no_sp.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_direct_no_sp.s
echo ""

echo $RED"Our asm 27"$RESET
./asm champ_test/checker_test_files/error/param_direct_no_value.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_direct_no_value.s
echo ""

echo $RED"Our asm 28"$RESET
./asm champ_test/checker_test_files/error/param_double_commas.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_double_commas.s
echo ""

echo $RED"Our asm 29"$RESET
./asm champ_test/checker_test_files/error/param_extra2.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_extra2.s
echo ""

echo $RED"Our asm 30"$RESET
./asm champ_test/checker_test_files/error/param_mt_3.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_mt_3.s
echo ""

echo $RED"Our asm 31"$RESET
./asm champ_test/checker_test_files/error/param_mt_r99.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_mt_r99.s
echo ""

echo $RED"Our asm 32"$RESET
./asm champ_test/checker_test_files/error/param_nonexistent_label.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_nonexistent_label.s
echo ""

echo $RED"Our asm 33"$RESET
./asm champ_test/checker_test_files/error/param_plus_minus.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_plus_minus.s
echo ""

echo $RED"Our asm 34"$RESET
./asm champ_test/checker_test_files/error/param_specialchars.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/param_specialchars.s
echo ""

echo $RED"Our asm 35"$RESET
./asm champ_test/checker_test_files/error/zother_1.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/zother_1.s
echo ""

echo $RED"Our asm 36"$RESET
./asm champ_test/checker_test_files/error/zother_2.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/zother_2.s
echo ""

echo $RED"Our asm 37"$RESET
./asm champ_test/checker_test_files/error/zother_3.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/zother_3.s
echo ""

echo $RED"Our asm 38"$RESET
./asm champ_test/checker_test_files/error/zother_4.s
echo $GREEN"Original"$RESET
./champ_test/asm champ_test/checker_test_files/error/zother_4.s
echo ""
