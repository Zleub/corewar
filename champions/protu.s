.name "stayin' alive"
.comment "Ha, Ha, Ha, stayiiiiin' aliiiiiiiiiive"

ld	%25648596, r3
st	r3, r2
and	%-19, r3, r3
and	r2, r3, r3
or	%3, r3, r3
or	r2, r3, r3
live:
	live %1
