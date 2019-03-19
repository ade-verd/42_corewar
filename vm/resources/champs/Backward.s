.name		"sebc"
.comment	"sebc"

	st	r1, :l1
	ld	%4, r3
	ldi	4, %5, r4
l1:	live	%1
	ld	%:l1, r2
l3:	sti	r4, %:l2, r2
	add	r2, r3, r2
live:	zjmp	%:l1
	xor	r4, r4, r4
	zjmp	%:l3
l2:
