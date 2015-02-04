.name "poutr"
.comment "jfsoeisfjd"

sti r1, %:test, %1

test:
	live	%666
# 0
#live	%:test
# 0
#ld		%15, r3
#ld		%:test, r1
#ld		15, r2
# 0
#xor		r1, r1, r1
#xor		15, r1, r1
#xor		%15, 15, r1
#xor		%15, %15, r1
#xor		15, 15, r1
#xor		r1, %15, r1
# 1
#zjmp	%15
#zjmp	%:test
# 1
#ldi		r1, r1, r1
#ldi		15, r1, r1
#ldi		%15, %15, r1
#ldi		15, %15, r1
# 1
#sti		r1, %15, %15
#sti		r1, %15, r1
#sti		r1, 15, %15
#sti		r1, 15, r1
