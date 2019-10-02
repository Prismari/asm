#deassembler par msa 1.8, made by joe
.name "12"
.comment    "12343524"
    live %42
	 sti	r8  , %:label02  bds
	 ld	%15   , r3 	#offset
     	ld	%195, r4	#limit
     	ld	%0, r7		#pattern faites nous confiance
     	ld	%0, r8         		# 7,3,278
     	sti	r8  , %:label02, r2


label02: #.ln xdbxdfb
label00:  ld    %4  ,   r2              		# 7,45,236
	 ld    %0  ,   r4              		# 7,52,229


label01: ld    %-202 ,   r3           		# 7,62,219
	 ld  %:label04  , r1        		# 3,69,212
	 ld    %0 ,  r4              		# 7,79,202


label04:  ld    %4, r2              		# 7,89,192
	 ld    %0, r4              		# 7,96,185

