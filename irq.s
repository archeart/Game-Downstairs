.define _timer_int
.extern _timer_handle

_timer_int:
	push ax
	push bx
	push cx
	push dx
	push bp
	push si
	push di
	call _timer_handle
	pop di
	pop si
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	iret

.define _keyboard_int
.extern _keyboard_handle
_keyboard_int:
	push ax
	push bx
	push cx
	push dx
	push bp
	push si
	push di
	call _keyboard_handle
	pop di
	pop si
	pop bp
	pop dx
	pop cx
	pop bx
	pop ax
	iret
