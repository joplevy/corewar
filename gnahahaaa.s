.name "gnahahaaa"
.comment "I beliiiieve I can liiiiiiive... "

secu:	ld -42,r15
		st r1, 14
		ld %-805297407,r2
		st r2,-16
live0:	live %42
		ld %0,r15
		zjmp %:live0
