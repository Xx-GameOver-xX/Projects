include \masm32\include\masm32rt.inc

include \masm32\include\winmm.inc
includelib \masm32\lib\winmm.lib

include drd.inc
includelib drd.lib
include heinemannlib.inc
includelib heinemannlib.lib
include data.inc
include little_funcs.inc
include small_funcs.inc
include mid_funcs.inc
include main_funcs.inc


.code
RESETPOINT:

;;;;;;;;;;;;;;;;;;;;;;;;;;; TODO - FIX COLISION!!! ;;;;;;;;;;;;;;;;;;;;;;;;;;;:

main proc
invoke doFirst
invoke PlaySound, offset bgmusic,NULL, SND_ASYNC
loopy:
push score
invoke draw
invoke update
pop tmpscore
;cmp score,10
;jl loopy
cmp tmpscore,10
jl loopy
sec:
cmp tmpscore, 20
jg thrd
invoke drd_imageDelete,offset lvl1
invoke drd_imageLoadFile, offset second, offset lvl1
invoke drd_imageSetTransparent, offset lvl1, 0ffffffh
mov lvl1.CENTER.x, 60
mov lvl1.CENTER.y, 155
mov lvl1.ORIGIN.x, 120
mov lvl1.ORIGIN.y, 310
mov lvl1.RAD, 90
jmp loopy
thrd:
cmp tmpscore,25
jg forth
invoke drd_imageDelete,offset lvl1
invoke drd_imageLoadFile, offset third, offset lvl1
invoke drd_imageSetTransparent, offset lvl1, 0ffffffh
mov lvl1.CENTER.x, 45
mov lvl1.CENTER.y, 57
mov lvl1.ORIGIN.x, 90
mov lvl1.ORIGIN.y, 165
mov lvl1.RAD, 40
jmp loopy 
forth:
cmp tmpscore,30
jg loopy
invoke drd_imageDelete,offset lvl1
invoke drd_imageLoadFile, offset fourth, offset lvl1
invoke drd_imageSetTransparent, offset lvl1, 0ffffffh
mov lvl1.CENTER.x, 115
mov lvl1.CENTER.y, 170
mov lvl1.ORIGIN.x, 230
mov lvl1.ORIGIN.y,340
mov lvl1.RAD, 150
jmp loopy
ret
main endp
end main

;;;;;;;;;;;;;;;;;;;;;;;;;;; TODO - FIX COLISION!!! ;;;;;;;;;;;;;;;;;;;;;;;;;;;U