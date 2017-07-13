.name "gnahahaaa"
.comment "I beliiiieve I can liiiiiiive... "

		ld -42,r15
start:	st r1, 18
		ld %-805300479,r2
		st r2,-16
flood:	live %42
		st r15,r16
		ld %252188160,r3
		st r3,-11
		st r1,6
		live %42
		fork %:start
liiive:	st r1,6
		live %42
		ld %0,r15
		zjmp %:liiive
