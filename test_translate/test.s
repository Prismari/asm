.comment "MY NAME!!"
.name "MY NAME!!"
_mama_:
ld %:debut, r3
live %-2
sti  r15,%0,r14
zjmp %-200
debut:		
		live %42			#5
		sti  r4,%:debut , %1		#7
		add  r4,r12,r4			#5	
		sub  r10,r11,r10		#5
		zjmp %:debut			#3
		fork %:debut




















