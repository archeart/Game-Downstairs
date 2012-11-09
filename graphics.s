.define _init_graphics
_init_graphics:
	movb ah, #0
	movb al, #0x13
	int 0x10
	ret

.define _draw_pixel  !draw_pixel(x,y)
_draw_pixel:
	push bp
	mov bp, sp

	mov dx, 4(bp)
	mov cx, 6(bp)
	movb al, 8(bp)
	movb ah, #0xC

	int 0x10
	pop bp
	ret
