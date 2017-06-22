.name "test"
.comment "dss"

start:	live %2
st r1, 16
st r1, 6
live %4
live %94
st r1, r2
st r1, 100
st r2, 150
ld -20, r4
ld %-1, r2
and r4, r2, r3
st r3, 200
fork %10
ld %1, r5
ld %0, r5
zjmp %:start
