.code

doFirst proc
invoke init
invoke loadToRam
ret
doFirst endp

astroscore proc
cmp score, 10
jge LVL_3
mov edx, score
cmp edx, 20
jl retpoint
invoke fallingDraw, offset astro1
invoke drd_imageDraw,  offset astro1, astro1.pos.x, astro1.pos.y
invoke fallingDraw, offset astro2
invoke drd_imageDraw,  offset astro2, astro2.pos.x, astro2.pos.y
invoke fallingDraw, offset astro1
invoke drd_imageDraw,  offset astro1, astro1.pos.x, astro1.pos.y
ret

LVL_3:
cmp score, 25
jge LVL_4
invoke fallingDraw, offset astro1
invoke drd_imageDraw,  offset astro1, astro1.pos.x, astro1.pos.y
invoke fallingDraw, offset astro2
invoke drd_imageDraw,  offset astro2, astro2.pos.x, astro2.pos.y
invoke fallingDraw, offset astro3
invoke drd_imageDraw,  offset astro3, astro3.pos.x, astro3.pos.y
invoke fallingDraw, offset astro4
invoke drd_imageDraw,  offset astro4, astro4.pos.x, astro4.pos.y
ret

LVL_4:
mov edx, score
cmp edx, 30
jge endgame
invoke fallingDraw, offset astro1
invoke drd_imageDraw,  offset astro1, astro1.pos.x, astro1.pos.y
invoke fallingDraw, offset astro2
invoke drd_imageDraw,  offset astro2, astro2.pos.x, astro2.pos.y
invoke fallingDraw, offset astro3
invoke drd_imageDraw,  offset astro3, astro3.pos.x, astro3.pos.y
invoke fallingDraw, offset astro4
invoke drd_imageDraw,  offset astro4, astro4.pos.x, astro4.pos.y
invoke fallingDraw, offset astro5
invoke drd_imageDraw,  offset astro5, astro5.pos.x, astro5.pos.y
ret
endgame:
	invoke PlaySound, NULL,0, 0
	mov edx, usru
	cmp edx,0
	jne DRW_RU
	invoke PlaySound, offset USWINMUSIC,NULL, SND_ASYNC
	AFTMUSUS:
	invoke drd_imageDraw,offset usBg,0,0
	invoke drd_flip
	invoke reset
	jmp AFTMUSUS
	DRW_RU:
	invoke PlaySound, offset RUWINMUSIC,NULL, SND_ASYNC
	AFTMUSRU:
	invoke drd_imageDraw,offset ruBg,0,0
	invoke drd_flip
	invoke reset
	jmp AFTMUSRU
jmp endgame
retpoint:
ret
astroscore endp


draw proc
invoke drawBG
invoke drawS
invoke drawTxt
invoke drawR_OR_U
invoke draw_coins
invoke astroscore
invoke drd_flip
ret
draw endp

update proc
invoke draw
invoke drd_processMessages
invoke drd_pixelsClear,0000000h
invoke State_DO
invoke isSpace_State, offset starttxt, offset lvl1, offset bg
invoke updateWorld
invoke pointsSeter
invoke updateState, offset lvl1, offset lvl2, offset lvl3, offset lvl4, offset score, offset usru, offset usBg, offset usBg
invoke cols
invoke int_to_string,score
push eax
invoke drd_setWindowTitle, eax
call Free ; invoke Free,offset score string
;invoke drd_flip
ret
update endp


;;;;;;;;;;;;;;;;;;;;;;;;;;; TODO - FIX COLISION!!! ;;;;;;;;;;;;;;;;;;;;;;;;;;;
