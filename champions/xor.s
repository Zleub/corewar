.name "xor heros"
.comment "this is xor"

xor %:1, r2, r2
xor %1, r2, r2
xor %:_xor, r2, r2
xor %:1, %:1, r2
xor %1, %2, r2
xor %:_xor, 2, r2
xor %:1, %:1, r2
xor %1, %2, r2
xor %:_xor, 2, r2
xor %:1, %:1, r2
xor %2, %:_xor, r2
xor 2, %:_xor, r2

xor :1, r2, r2
xor 1, r2, r2
xor :_xor, r2, r2

xor r1, r2, r1

_xor:

1:
