.define _printc
_printc:
	push bp
	mov bp, sp
	movb ah, #0xE
	movb al, 4(bp)
	mov bx, #1
	int 0x10
	pop bp
	ret

.define _movecur
_movecur:
	push bp
	mov bp, sp
	movb ah, #0x2
	movb dh, 4(bp)
	movb dl, 6(bp)
	movb bh, #0x0
	int 0x10
	pop bp
	ret

.define _coloc
_coloc:
	push bp
	mov bp, sp
	movb ah, #0x9
	movb al, 4(bp)
	movb bl, 6(bp)
	movb bh, #0x0
	mov cx, #1
	int 0x10
	pop bp
	ret

