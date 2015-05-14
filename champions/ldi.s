.name "ldi heros"
.comment "this is ldi"

ldi %:1, r2, r2
ldi %1, r2, r2
ldi %:_ldi, r2, r2
ldi %:1, %:1, r2
ldi %1, %2, r2
ldi %:1, %:1, r2
ldi %1, %2, r2
ldi %:1, %:1, r2
ldi %2, %:_ldi, r2
ldi 2, %:_ldi, r2

ldi :1, r2, r2
ldi 1, r2, r2
ldi :_ldi, r2, r2

ldi r1, r2, r1

_ldi:

1:
