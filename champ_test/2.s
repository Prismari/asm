#deassembler par msa 1.8, made by joe
.name "12"
.comment    "12343524"
	 aff %:label00          		# 3,0,281
	 live    %-272,r3           		# 7,3,278



label02:#.ln
label00:
        lldi    %4,r2              		# 7,45,236
	 ld    %0,r4              		# 7,52,229


label01: ld    %-202,r3           		# 7,62,219
	 fork  %:label04          		# 3,69,212
	 ld    %0,r4              		# 7,79,202


label04:  lfork    %4,r2              		# 7,89,192
	 ld    %0,r4              		# 7,96,185

