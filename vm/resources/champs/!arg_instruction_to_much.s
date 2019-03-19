.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1
		and r1, %0, r1

live:	live %1 ,%999 #add one arg here
		zjmp %:live
		and r1, %0, r1, r3
