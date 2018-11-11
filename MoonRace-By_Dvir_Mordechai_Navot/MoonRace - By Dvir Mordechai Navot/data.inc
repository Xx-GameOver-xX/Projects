.const

SP_DRCX_OFST = 28 ;sp
SP_DRCY_OFST = 32 ;sp
POSX_OFST = 20 ;txt
POSY_OFST = 24 ;txt
POS_OFST = 20
RAD_OFST = 56
CNTRX_OFST = 60
CNTR_CNST = 40
RAD = 56
.data

;spaceD STRUCT
;Img STRUCT
;   surface DWORD ? 0
;    iwidth DWORD ? 4
;    iheight DWORD ? 8 
;    hasSrcKey DWORD ? 12
;    hbitmap DWORD ? 16
;Img ENDS
;pos POINT<> 20
;drcX DWORD ? 28
;drcY DWORD ? 32
;state DWORD 36
;CENTER POINT<> 40
;ORIGIN POINT<> 48
;RAD DWORD ?  56
;center POINT<> 60
;origin POINT<> 68
;usru DWORD 76
;spaceD ENDS


bgmusic byte "sound.wav",0 ;; creating byte var that contains the name of the wav file
RUWINMUSIC byte "ussrau.wav",0
USWINMUSIC byte "usaau.wav",0

spaceD STRUCT
	img Img<>
	pos POINT<>
	drcX DWORD ?
	drcY DWORD ?
	state DWORD 0
	CENTER POINT<>
	ORIGIN POINT<> 
	RAD DWORD ? 
    center POINT<> 
	origin POINT<> 
spaceD ENDS

bgS STRUCT
	img Img<> 
	state DWORD 0
bgS ENDS

y dword 600
h dword 0
w dword 800

txt STRUCT
	img Img<> ;0
	pos POINT<> ;20
	state DWORD ? ;28
txt ENDS

KEYS STRUCT
	left DWORD ? ;0
	right DWORD ? ;4
	up DWORD ? ;8
	down DWORD ? ;12
KEYS ENDS

;; creating byte vars that contains the name of the pic
first byte "lvl1.bmp",0
second byte "lvl2.bmp",0
third byte "lvl3.bmp",0
fourth byte "lvl4.bmp",0
;; creating structs

lvl1 spaceD<<>,<100,100>,0,0,0,<45,95>,<90,190>,60>
lvl2 spaceD<<>,<100,100>,0,0,0,<60,155>,<120,310>,100>
lvl3 spaceD<<>,<100,100>,0,0,0,<45,57>,<90,165>,45>
lvl4 spaceD<<>,<100,100>,0,0,0,<115,170>,<230,340>,160>

sp_keys KEYS<VK_LEFT, VK_RIGHT, VK_UP, VK_DOWN>

bgbyte byte "sky.bmp",0 ; creating byte var that contains the name of the pic

bg bgS<<>,1> ;; creating struct

stxtbyte byte "starttxt.bmp",0

starttxt txt<<>,<50,100>,1>

score DWORD 0

uscbyte byte "uscoin.bmp",0
rucbyte byte "rucoin.bmp",0
astrobyte byte "astro.bmp",0
rub byte "roowin.bmp",0
usb byte "uswin.bmp",0

ucoin1 spaceD<<>,<700,700>,0,0,1,<>,<31,33>,15,<>>
ucoin2 spaceD<<>,<700,700>,0,0,1,<>,<31,33>,15,<>>
ucoin3 spaceD<<>,<700,700>,0,0,1,<>,<31,33>,15,<>>
ucoin4 spaceD<<>,<700,700>,0,0,1,<>,<31,33>,15,<>>

rcoin1 spaceD<<>,<700,700>,0,0,1,<15,15>,<30,30>,17,<>>
rcoin2 spaceD<<>,<700,700>,0,0,1,<15,15>,<30,30>,17,<>>
rcoin3 spaceD<<>,<700,700>,0,0,1,<15,15>,<30,30>,17,<>>
rcoin4 spaceD<<>,<700,700>,0,0,1,<15,15>,<30,30>,17,<>>

astro1 spaceD<<>,<700,700>,0,0,1,<40,37>,<80,74>,0,<>>
astro2 spaceD<<>,<700,700>,0,0,1,<40,37>,<80,74>,0,<>>
astro3 spaceD<<>,<700,700>,0,0,1,<40,37>,<80,74>,0,<>>
astro4 spaceD<<>,<700,700>,0,0,1,<40,37>,<80,74>,0,<>>
astro5 spaceD<<>,<700,700>,0,0,1,<40,37>,<80,74>,0,<>>

usBg bgS<>
ruBg bgS<>

usru DWORD 0

tmpscore DWORD ?