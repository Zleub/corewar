.name "stayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"

sti	r1, %:live, %1		;change live by the right value
sti	r1, %:live2, %1			;change live by the right value
ld	%280267669825, r3
ld	%:live, r6
sti	r3, %:live, %400

#While (r2 < 10)
forks:
add	r2, r3, r2		;increment r2
xor	%15, %15, r4		;if (r4) {carry = 0}
live2:
	live 	%4
zjmp	%:endwhile		;if (carry)
fork	%:forks
ld	%0, r4			;carry = 1
zjmp	%:forks
#EndWhile
endwhile:
ld	%0, r4			;carry = 1

live:
live %4
zjmp %:live
