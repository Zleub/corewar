.name "lldi heros"
.comment "this is lldi"

lldi %:1, r2, r2
lldi %1, r2, r2
lldi %:_lldi, r2, r2
lldi %:1, %:1, r2
lldi %1, %2, r2
lldi %:1, %:1, r2
lldi %1, %2, r2
lldi %:1, %:1, r2
lldi %2, %:_lldi, r2
lldi 2, %:_lldi, r2

lldi :1, r2, r2
lldi 1, r2, r2
lldi :_lldi, r2, r2

lldi r1, r2, r1

_lldi:

1:
