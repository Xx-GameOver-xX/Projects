.686
.code

spaceShipState proc adrObj:DWORD
mov  edx, adrObj
mov ecx,[edx+36]
cmp ecx,1
jne Ret_Point
invoke drd_imageDraw, edx, [edx+20], [edx+24]
Ret_Point:
ret
spaceShipState endp

textState proc adrObj:DWORD
xor edx, edx
mov  edx, adrObj
mov edi, edx
mov eax,20
add edi, eax ; pos x
mov eax, edx
mov ecx,24
add eax, ecx
mov ecx,[edx+28]
cmp ecx,1
jne Ret_Point
invoke drd_imageDraw, edx, [edi], [eax]
xor edx, edx
mov  edx, adrObj
invoke drd_imageSetTransparent,edx,0ffffffh
Ret_Point:
ret
textState endp

bgState proc adrObj:DWORD

State1:
mov edx, adrObj
mov ecx, edx
mov edx, 20
add ecx, edx
mov edx, [ecx]
cmp edx,1
jne State2
mov edx, adrObj
invoke drd_imageDraw, edx,0,0
ret

State2:
mov edx, adrObj
mov ecx, 20
add edx, ecx
mov ecx, 2
cmp [edx], ecx
jne Ret_Point
xor edx,edx
mov edx, adrObj
	invoke drd_imageDrawCrop, edx,0,h,0,0,w,y
xor edx,edx
mov edx, adrObj
	invoke drd_imageDrawCrop, edx,0,0,0,y,w,h
Ret_Point:
ret
bgState endp

SP_isPressed_drc proc adrObj:dword, keys:DWORD
mov edx, keys
mov ecx, adrObj

	invoke GetAsyncKeyState,[edx]
	cmp eax, 0
	jne left
	mov ecx, adrObj
	mov eax, 0
	mov [ecx+SP_DRCX_OFST], eax

mov edx, keys
mov ecx, adrObj

	invoke GetAsyncKeyState,[edx+4]
	cmp eax, 0
	jne right
	mov ecx, adrObj
	mov eax, 0
	mov [ecx+SP_DRCX_OFST], eax

mov edx, keys
mov ecx, adrObj

	invoke GetAsyncKeyState,[edx+8]
	cmp eax, 0
	jne up
	mov ecx, adrObj
	mov eax, 0
	mov [ecx+SP_DRCY_OFST], eax

mov edx, keys
mov ecx, adrObj

	invoke GetAsyncKeyState,[edx+12]
	cmp eax, 0
	jne down
	mov ecx, adrObj
	mov eax, 0
	mov [ecx+SP_DRCY_OFST], eax

ret

left: 
mov ecx, adrObj
mov edx,0
cmp [ecx+20],edx
jle Ret_point
mov eax, -3
mov [ecx+SP_DRCX_OFST], eax
ret
right:
mov ecx, adrObj
mov edx,800
cmp [ecx+20],edx
jge Ret_point
mov eax, 3
mov [ecx+SP_DRCX_OFST], eax
ret
up:
mov ecx, adrObj
mov edx,0
cmp [ecx+24],edx
jle Ret_point
mov eax, -3
mov [ecx+SP_DRCY_OFST], eax
ret
down:
mov ecx, adrObj
mov edx,600
cmp [ecx+24],edx
jge Ret_point
mov eax, 3
mov [ecx+SP_DRCY_OFST], eax
Ret_point:
ret
SP_isPressed_drc endp

miniSetPoints proc startP:DWORD, XY: DWORD, adrObj:DWORD
	mov ebx, adrObj
	mov edi, ebx
	add edi, startP			;edi is on CENTER or ORIGIN
	mov ecx, ebx	
	add ecx, POS_OFST		;ecx = ebx +20
	add ecx, XY			;ecx = ebx+20 or +ebx+24
	mov ecx, [ecx]		
	add ecx, [edi]			;ecx = pos + origin/center
	add edi, CNTRX_OFST	;edi = center/origin
	mov [edi],ecx			;change center/origin TODO fix this line, there is a problem with it
	
ret
miniSetPoints endp
            
random proc max:DWORD
rdrand eax
rdrand eax
rdrand eax
xor edx, edx
div max
mov eax,edx
ret
random endp

fallingDraw proc adrObj:DWORD
mov edx,adrObj
mov ecx, 600
mov edi,[edx+24]
cmp [edx+24], ecx
jge do
mov ecx,1		
add [edx+24],ecx
ret
do:
invoke random,800
mov edx,adrObj
mov [edx+20], eax
mov ecx, 0
mov [edx+24], ecx
ret
fallingDraw endp 