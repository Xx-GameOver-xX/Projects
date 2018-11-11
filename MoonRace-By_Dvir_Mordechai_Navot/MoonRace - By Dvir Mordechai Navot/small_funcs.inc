.code

Spasecraft_Movment proc adrObj:DWORD;, keys:DWORD
	mov ebx,adrObj
	;mov edx, keys
	invoke SP_isPressed_drc, ebx, offset sp_keys ;edx
	mov eax, [ebx + SP_DRCX_OFST]
	add [ebx+POSX_OFST], eax

	mov eax, [ebx + SP_DRCY_OFST]
	add [ebx+POSY_OFST], eax	
ret
Spasecraft_Movment endp

moveSpacecraft_State proc adrObj:DWORD;, keys:DWORD
mov  edx, adrObj
mov ecx,[edx+36]
cmp ecx,1
jne Ret_Point
;mov ecx, keys
invoke Spasecraft_Movment, edx;, ecx
Ret_Point:
ret
moveSpacecraft_State endp

setPoints proc adrObj:DWORD 

	invoke miniSetPoints,40,20,adrObj;center_x,posx
	invoke miniSetPoints,44,24,adrObj;center_y,posy
	invoke miniSetPoints,48,20,adrObj;origin_x,posx
	invoke miniSetPoints,52,24,adrObj;origin_y,posy
ret
setPoints endp

drawR_OR_U proc 
ret
cmp usru, 0
jne do
invoke fallingDraw, offset rcoin1
invoke fallingDraw, offset rcoin2
invoke fallingDraw, offset rcoin3
invoke fallingDraw, offset rcoin4
ret
do:
invoke fallingDraw, offset ucoin1
invoke fallingDraw, offset ucoin2
invoke fallingDraw, offset ucoin3
invoke fallingDraw, offset ucoin4
ret
drawR_OR_U endp

draw_coins proc
mov ecx, offset bg
mov ebx, 2
cmp [ecx+20], ebx
jne retpoint
mov edx,usru
mov ecx, 0
cmp edx, ecx
je rupoint

invoke drd_imageDraw, offset ucoin1, ucoin1.pos.x,ucoin1.pos.y
invoke fallingDraw, offset ucoin1
invoke drd_imageSetTransparent, offset ucoin1, 0ffffffh
invoke drd_imageDraw, offset ucoin2, ucoin2.pos.x,ucoin2.pos.y
invoke fallingDraw, offset ucoin2
invoke drd_imageSetTransparent, offset ucoin2, 0ffffffh
invoke drd_imageDraw, offset ucoin3, ucoin3.pos.x,ucoin3.pos.y
invoke fallingDraw, offset ucoin3
invoke drd_imageSetTransparent, offset ucoin3, 0ffffffh
invoke drd_imageDraw, offset ucoin4, ucoin4.pos.x,ucoin4.pos.y
invoke fallingDraw, offset ucoin4
invoke drd_imageSetTransparent, offset ucoin4, 0ffffffh

ret

rupoint:
invoke drd_imageDraw, offset rcoin1, rcoin1.pos.x, rcoin1.pos.y
invoke fallingDraw, offset rcoin1
invoke drd_imageSetTransparent, offset rcoin1, 0ffffffh
invoke drd_imageDraw, offset rcoin2, rcoin2.pos.x,rcoin2.pos.y
invoke fallingDraw, offset rcoin2
invoke drd_imageSetTransparent, offset rcoin2, 0ffffffh
invoke drd_imageDraw, offset rcoin3, rcoin3.pos.x,rcoin3.pos.y
invoke fallingDraw, offset rcoin3
invoke drd_imageSetTransparent, offset rcoin3, 0ffffffh
invoke drd_imageDraw, offset rcoin4, rcoin4.pos.x,rcoin4.pos.y
invoke fallingDraw, offset rcoin4
invoke drd_imageSetTransparent, offset rcoin4, 0ffffffh
retpoint:
ret

draw_coins endp

reset proc
invoke GetAsyncKeyState, VK_P
cmp eax, 0
je retpoin

mov lvl1.state, 0
mov lvl1.pos.x, 100
mov lvl1.pos.y, 100
mov bg.state, 1
mov starttxt.state, 1
mov usru, 0
mov score, 0

jmp RESETPOINT

retpoin:
ret
reset endp