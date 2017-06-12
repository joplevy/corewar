.name "zork"
.comment "just a basic living prog"

plop:	sti r1,%:live,%1
live:	live %1
		ld %2147483648,r3
load:	ld %0,r2
		sti r3,%:load,%1 
		st r2,:plop
#		ld %0,r2
		zjmp %:live
