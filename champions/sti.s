.name "sti heros"
.comment "this is sti"

sti r1, %:1, r2
sti r1, %1, r2
sti r1, %:_sti, r2
sti r1, %:1, %:1
sti r1, %1, %2
sti r1, %:1, %:1
sti r1, %1, %2
sti r1, %:1, %:1
sti r1, %2, %:_sti
sti r1, 2, %:_sti

sti r1, :1, r2
sti r1, 1, r2
sti r1, :_sti, r2

sti r1, r1, r2

_sti:

1:
