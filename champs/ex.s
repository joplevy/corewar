.name "zork"
.comment "just a basic living prog"
		
l2:		sti		r1, %:live1, %1
		sti		r1, %:live2, %1
		sti		r1, %:live3, %1
live1:	live	%1
live2:	live	%1
live3:	live	%1
