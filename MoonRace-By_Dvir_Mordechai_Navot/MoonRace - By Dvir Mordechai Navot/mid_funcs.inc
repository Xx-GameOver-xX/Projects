.code

init proc
 
	invoke drd_init,800,600,0

ret
init endp

loadToRam proc
invoke drd_imageLoadFile, offset usb, offset usBg
invoke drd_imageLoadFile, offset rub, offset ruBg
invoke drd_imageLoadFile,offset first,offset lvl1.img
invoke drd_imageLoadFile,offset second,offset lvl2.img
invoke drd_imageLoadFile,offset third,offset lvl3.img
invoke drd_imageLoadFile,offset fourth,offset lvl4.img
invoke drd_imageLoadFile, offset bgbyte, offset bg.img
invoke drd_imageLoadFile, offset stxtbyte, offset starttxt.img
invoke drd_imageLoadFile,offset uscbyte, offset ucoin1.img
invoke drd_imageLoadFile,offset uscbyte, offset ucoin2.img
invoke drd_imageLoadFile,offset uscbyte, offset ucoin3.img
invoke drd_imageLoadFile,offset uscbyte, offset ucoin4.img
invoke drd_imageLoadFile,offset rucbyte, offset rcoin1.img
invoke drd_imageLoadFile,offset rucbyte, offset rcoin2.img
invoke drd_imageLoadFile,offset rucbyte, offset rcoin3.img
invoke drd_imageLoadFile,offset rucbyte, offset rcoin4.img
invoke drd_imageLoadFile, offset astrobyte, offset astro1
invoke drd_imageLoadFile, offset astrobyte, offset astro2
invoke drd_imageLoadFile, offset astrobyte, offset astro3
invoke drd_imageLoadFile, offset astrobyte, offset astro4
invoke drd_imageLoadFile, offset astrobyte, offset astro5
invoke drd_imageSetTransparent,offset lvl1,0ffffffh
invoke drd_imageSetTransparent, offset astro1, 0ffffffh
invoke drd_imageSetTransparent, offset astro2, 0ffffffh
invoke drd_imageSetTransparent, offset astro3, 0ffffffh
invoke drd_imageSetTransparent, offset astro4, 0ffffffh
invoke drd_imageSetTransparent, offset astro5, 0ffffffh
ret
loadToRam endp

drawBG proc
	invoke bgState,offset bg
ret
drawBG endp

drawTxt proc
invoke textState,offset starttxt
ret
drawTxt endp

drawS proc
invoke spaceShipState,offset lvl1
invoke spaceShipState,offset lvl2
invoke spaceShipState,offset lvl3
invoke spaceShipState,offset lvl4
ret
drawS endp

isSpace_State proc adrObj:DWORD, adrObj2:DWORD, adrBg:DWORD
mov edx, adrBg
mov ecx, 2
cmp [edx+20], ecx
je retpoint
invoke GetAsyncKeyState, VK_R
cmp eax, 0
je anddo
mov usru, 0
jmp fundo
anddo:
invoke GetAsyncKeyState, VK_U
cmp eax, 0
je retpoint
mov usru, 1
fundo:
xor edx, edx
mov edx, adrObj
mov ecx, 0
mov [edx+28], ecx
mov edx, adrObj2
mov ecx, 1 
mov [edx+36], ecx ; state spaceship1 = 1
mov edx, adrBg
mov ecx, 2
mov [edx+20], ecx
retpoint:
ret
isSpace_State endp

State_DO proc
invoke moveSpacecraft_State, offset lvl1;, offset keys
invoke moveSpacecraft_State, offset lvl2
invoke moveSpacecraft_State, offset lvl3
invoke moveSpacecraft_State, offset lvl4

ret
State_DO endp

StopFor proc Time:DWORD
mov edx, 0 
mov ecx, Time
time:
inc edx
cmp ecx, edx
jne time
ret
StopFor endp

updateWorld proc 
invoke StopFor, 5000000

    inc h
	dec y 
	cmp h,600
	je do
	jmp Ret_Point
do:
	mov y,600
	mov h, 0
Ret_Point:
ret
updateWorld endp

colision PROC,x1:DWORD,y1:DWORD,w1:DWORD,h1:DWORD,x2:DWORD,y2:DWORD,w2:DWORD,h2:DWORD
	
	mov eax,x1
	add eax,w1
	cmp eax,x2
	jl not_coliding

	mov eax,x2
	add eax,w2
	cmp eax,x1
	jl not_coliding

	mov eax,y1
	add eax,h1
	cmp eax,y2
	jl not_coliding

	mov eax,y2
	add eax,h2
	cmp eax,y1
	jl not_coliding

	mov eax,1
	ret

	not_coliding:
	xor eax,eax
	ret
colision ENDP

col proc, adrObj1:DWORD, adrObj2:DWORD, ru:DWORD, us:DWORD,astro:DWORD, SCORE:DWORD, USRU:DWORD

;;;;;;;;;;;;;;;;;;;;;;;;;;; TODO - FIX ;;;;;;;;;;;;;;;;;;;;;;;;;;;
	mov eax,adrObj1
	mov ebx,adrObj2
	mov ecx,[eax+CNTR_CNST];ecx = CENTER_X
	add ecx,[eax+POS_OFST]; ecx = center_X
	mov edi,[ebx+CNTR_CNST];edi = CENTER_X
	add edi,[ebx+POS_OFST]; edi = center_X
	sub ecx,edi
	imul ecx,ecx
	mov edx,4
	mov edi,[eax+CNTR_CNST+edx];edi = CENTER_y
	add edi,[eax+POS_OFST+edx]; edi = center_y

	mov esi,[ebx+CNTR_CNST+edx];eax = CENTER_y
	add esi,[ebx+POS_OFST+edx]; eax = center_y
	sub esi,edi
	imul esi,esi
	
	add esi,ecx ;eax=2900
	mov ecx,[eax+RAD]
	mov edx,[ebx+RAD]
	add ecx,edx
	imul ecx,ecx
	cmp esi,ecx
	jle DO_COL
	
	
	ret
	DO_COL:
	mov eax, adrObj2
	mov ecx, 650
	mov [eax+24], ecx
	mov ecx,SCORE
	mov edx, astro 
	cmp edx, 1
	jne do
	endg:
	invoke PlaySound, NULL,0, 0
	mov edx, USRU
	cmp edx,0
	jne DRW_RU
	invoke PlaySound, offset USWINMUSIC,NULL, SND_ASYNC
	AFTMUSUS:
	invoke drd_imageDraw,us,0,0
	invoke drd_flip
	invoke reset
	jmp AFTMUSUS
	DRW_RU:
	invoke PlaySound, offset RUWINMUSIC,NULL, SND_ASYNC
	AFTMUSRU:
	invoke drd_imageDraw,ru,0,0
	invoke drd_flip
	invoke reset
	jmp AFTMUSRU
	do:
	mov ecx,SCORE
	mov eax,1
	add [ecx],eax
	ret
col endp



cols proc 
	mov edx, usru 
	cmp edx,0
	je ussrcol

	mov ecx, score
	cmp ecx,0
	je lv1

	lv1:
	mov ecx, score
	cmp ecx, 10
	jge lv2
	invoke col, offset lvl1,offset ucoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin4, offset ruBg, offset usBg,0,offset score, usru
	ret

	lv2:
	mov ecx, score
	cmp ecx, 20
	jge lv3
	invoke col, offset lvl1,offset ucoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin4, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset astro1, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro2, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro3, offset ruBg, offset usBg,1,offset score, usru

	ret

	lv3:
	mov ecx, score
	cmp ecx, 25
	jge lv4
	invoke col, offset lvl1,offset ucoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin4, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset astro1, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro2, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro3, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro4, offset ruBg, offset usBg,1,offset score, usru
	ret

	lv4:
	mov ecx, score
	cmp ecx, 30
	jge RETP
	invoke col, offset lvl1,offset ucoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset ucoin4, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset astro1, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro2, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro3, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro4, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro5, offset ruBg, offset usBg,1,offset score, usru

	ussrcol:

	ussrlv1:
	mov ecx, score
	cmp ecx, 10
	jge ussrlv2
	invoke col, offset lvl1,offset rcoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin4, offset ruBg, offset usBg,0,offset score, usru
	ret

	ussrlv2:
	mov ecx, score
	cmp ecx, 20
	jge ussrlv3
	invoke col, offset lvl1,offset rcoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin4, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset astro1, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro2, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro3, offset ruBg, offset usBg,1,offset score, usru
	ret

	ussrlv3:
	mov ecx, score
	cmp ecx, 25
	jge ussrlv4
	invoke col, offset lvl1,offset rcoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin4, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset astro1, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro2, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro3, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro4, offset ruBg, offset usBg,1,offset score, usru
	ret

	ussrlv4:
	mov ecx, score
	cmp ecx, 30
	jge RETP
	invoke col, offset lvl1,offset rcoin1, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin2, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin3, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset rcoin4, offset ruBg, offset usBg,0,offset score, usru
	invoke col, offset lvl1,offset astro1, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro2, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro3, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro4, offset ruBg, offset usBg,1,offset score, usru
	invoke col, offset lvl1,offset astro5, offset ruBg, offset usBg,1,offset score, usru

	RETP:
ret
cols endp

pointsSeter proc
push ruBg.img.surface
push ruBg.img.iwidth
push ruBg.img.iheight
push ruBg.img.hasSrcKey
push ruBg.img.hbitmap
push astro1.pos.y
push astro2.pos.y
push astro3.pos.y
push astro4.pos.y
push astro5.pos.y
push ucoin1.pos.y
push ucoin2.pos.y
push ucoin3.pos.y
push ucoin4.pos.y
push rcoin1.pos.y
push rcoin2.pos.y
push rcoin3.pos.y
push rcoin4.pos.y
invoke setPoints,offset ucoin1
invoke setPoints,offset ucoin2
invoke setPoints,offset ucoin3
invoke setPoints,offset ucoin4
invoke setPoints,offset rcoin1
invoke setPoints,offset rcoin2
invoke setPoints,offset rcoin3
invoke setPoints,offset rcoin4
invoke setPoints,offset astro1
invoke setPoints,offset astro2
invoke setPoints,offset astro3
invoke setPoints,offset astro4
invoke setPoints,offset astro5
pop rcoin4.pos.y
pop rcoin3.pos.y
pop rcoin2.pos.y
pop rcoin1.pos.y
pop ucoin4.pos.y
pop ucoin3.pos.y
pop ucoin2.pos.y
pop ucoin1.pos.y
pop astro5.pos.y
pop astro4.pos.y
pop astro3.pos.y
pop astro2.pos.y
pop astro1.pos.y
pop ruBg.img.hbitmap
pop ruBg.img.hasSrcKey
pop ruBg.img.iheight
pop ruBg.img.iwidth
pop ruBg.img.surface
ret
pointsSeter endp

updateState proc sp1:DWORD,sp2:DWORD,sp3:DWORD,sp4:DWORD,SCORE:DWORD, USRU:DWORD, US:DWORD, RU:DWORD
ret
mov edx, SCORE
cmp edx, 10
jge lev2
mov edx , sp1
mov edi, 0
mov [edx+36], edi
mov ecx , sp2
mov edx, 1
mov [ecx+36],edi 
ret
lev2:
mov edx, SCORE
cmp edx, 10
jge lev3
mov edx , sp2
mov edi, 0
mov [edx+36],edi
mov ecx , sp3
mov edi, 1
mov [ecx+36],edi
ret
lev3:
mov edx, SCORE
cmp edx, 20
jge lev4 
mov edx , sp3
mov edi,0
mov [edx+36],edi
mov ecx , sp4
mov edi, 1
mov [ecx+36],edi
ret
lev4:
mov edx, SCORE
cmp edx, 25
jge endgame
ret
endgame:
cmp edx, 30
jl retpp
cmp USRU,0
je 	DRW_RU
	invoke PlaySound, offset USWINMUSIC,NULL, SND_ASYNC
	AFTMUSUS:
	invoke drd_imageDraw,US,0,0
	invoke drd_flip
	invoke reset
	jmp AFTMUSUS
	DRW_RU:
	invoke PlaySound, offset RUWINMUSIC,NULL, SND_ASYNC
	AFTMUSRU:
	invoke drd_imageDraw,RU,0,0
	invoke drd_flip
	invoke reset
	jmp AFTMUSRU
jmp endgame
retpp:
ret
updateState endp