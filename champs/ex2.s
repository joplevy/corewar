.name "zork"
.comment "just a basic living prog"
		
l2:		sti		r1, %:live01, %1
		sti		r1, %:live02, %1
live01:	live	%1
live02:	live	%1
