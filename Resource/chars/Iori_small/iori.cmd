
;================================
;Iori Yagami X CMD FILE [HARD AI]
;================================

;-| Single Button |---------------------------------------------------------

[Command]
name = "a"
command = a
time = 1

[Command]
name = "b"
command = b
time = 1

[Command]
name = "c"
command = c
time = 1

[Command]
name = "x"
command = x
time = 1

[Command]
name = "y"
command = y
time = 1

[Command]
name = "z"
command = z
time = 1

[Command]
name = "s"
command = s
time = 1

;-| Hold Dir |--------------------------------------------------------------

[Command]
name = "holdfwd"
command = /$F
time = 1

[Command]
name = "holdback"
command = /$B
time = 1

[Command]
name = "holdup"
command = /$U
time = 1

[Command]
name = "holddown"
command = /$D
time = 1

;-| Hold Button |----------------------------------------------------------

[Command]
name = "holda"
command = /a
time = 1

[Command]
name = "holdb"
command = /b
time = 1

[Command]
name = "holdc"
command = /c
time = 1

[Command]
name = "holdx"
command = /x
time = 1

[Command]
name = "holdy"
command = /y
time = 1

[Command]
name = "holdz"
command = /z
time = 1

[Command]
name = "holds"
command = /s
time = 1

;-| CPU |--------------------------------------------------------------

[Command]
name = "a2"
command = a
time = 1

[Command]
name = "b2"
command = b
time = 1

[Command]
name = "c2"
command = c
time = 1

[Command]
name = "x2"
command = x
time = 1

[Command]
name = "y2"
command = y
time = 1

[Command]
name = "z2"
command = z
time = 1

[Command]
name = "s2"
command = s
time = 1

[Command]
name = "holdfwd2"
command = /$F
time = 1

[Command]
name = "holdback2"
command = /$B
time = 1

[Command]
name = "holdup2"
command = /$U
time = 1

[Command]
name = "holddown2"
command = /$D
time = 1

[Command]
name = "holda2"
command = /a
time = 1

[Command]
name = "holdb2"
command = /b
time = 1

[Command]
name = "holdc2"
command = /c
time = 1

[Command]
name = "holdx2"
command = /x
time = 1

[Command]
name = "holdy2"
command = /y
time = 1

[Command]
name = "holdz2"
command = /z
time = 1

[Command]
name = "holds2"
command = /s
time = 1

[Command]
name = "recovery2"
command = x+a
time = 1

;=====================[SHORTCUTS]======================
;NOTE: DELETE THIS GROUP OF CMDS TO REMOVE SHORTCUT DMS
;      OR MODIFY THEM TO USE ROLL/STRIKER/CD.

;Debug
[Command]
name = "asobi1"
command = z
time = 1

;Debug
[Command]
name = "sugi"
command = z
time = 1

;Debug
[Command]
name = "2kdm"
command = c
time = 1

;Debug
[Command]
name = "2ksdm"
command = c
time = 1

;=================[Hyper Moves]======================

;Kototsuki you
[Command]
name = "2ksdm"
command = ~D,DB,B,D,DB,B, a+b
time = 25

;2K DM
[Command]
name = "2kdm"
command = ~D,DF,F,D,DF,F,x
time = 25

[Command]
name = "2kdm"
command = ~D,DF,F,D,DF,F,y
time = 25

;Yami Sugi
[Command]
name = "sugi"
command = ~D,DF,F,D,DF,F,D,DF,F,D,DF,F, x+y
time = 60

;Ya Otome
[Command]
name = "asobi1"
command = ~D,DF,F,D,DB,B, x
time = 30

;Ya Otome
[Command]
name = "asobi2"
command = ~D,DF,F,D,DB,B, y
time = 30

;Ya Otome
[Command]
name = "asobi1"
command = ~D,DF,F,D,B, x
time = 30

;Ya Otome
[Command]
name = "asobi2"
command = ~D,DF,F,D,B, y
time = 30

;--------------------------------------
;REVERSE
;Ya Otome
[Command]
name = "revasobi1"
command = ~D,DB,B,D,DF,F, x
time = 30

;Ya Otome
[Command]
name = "revasobi2"
command = ~D,DB,B,D,DF,F, y
time = 30

;Ya Otome
[Command]
name = "revasobi1"
command = ~D,DB,B,D,F, x
time = 30

;Ya Otome
[Command]
name = "revasobi2"
command = ~D,DB,B,D,F, y
time = 30

;=================[Special Moves]====================

[Command]
name = "kuzukaze"
command = ~F,DF,D,DB,B,F, x
time = 30

[Command]
name = "kuzukaze"
command = ~F,DF,D,DB,B,F, y
time = 30

[Command]
name = "kuzukaze"
command = ~DF,B,F, x
time = 30

[Command]
name = "kuzukaze"
command = ~DF,B,F, y
time = 30

[Command]
name = "kuzukaze"
command = ~DF,DB,F, x
time = 30

[Command]
name = "kuzukaze"
command = ~DF,DB,F, y
time = 30

[Command]
name = "kototsuki1"
command = ~F,DF,D,DB,B, a
time = 30

[Command]
name = "kototsuki2"
command = ~F,DF,D,DB,B, b
time = 30

[Command]
name = "kototsuki1"
command = ~DF,DB, a
time = 30

[Command]
name = "kototsuki2"
command = ~DF,DB, b
time = 30

;Oni Yaki 1
[Command]
name = "oniyaki1"
command = ~F,D,DF, x
time = 20

;Oni Yaki 2
[Command]
name = "oniyaki2"
command = ~F,D,DF, y
time = 20

;Yami Barai 1
[Command]
name = "barai1"
command = ~D,DF,F, x
time = 20

;Yami Barai 2
[Command]
name = "barai2"
command = ~D,DF,F, y
time = 20

;Aoi Hana 1
[Command]
name = "aoi1"
command = ~D,DB,B, x
time = 20

;Aoi Hana 2
[Command]
name = "aoi2"
command = ~D,DB,B, y
time = 20

;Scorch 1
[Command]
name = "scorch1"
command = ~F,D,DF, a
time = 20

;Scorch 2
[Command]
name = "scorch2"
command = ~F,D,DF, b
time = 20

;--------------------------------------------
;RUN 
[Command]
name = "FF"
command = F, F
time = 15

;Back
[Command]
name = "BB"
command = B, B
time = 10

;Animation Switch
[Command]
name = "switch"
command = ~D,D, s
time = 20

[Command]
name = "taunt"
command = s
time = 1

[Command]
name = "striker"
command = a+y
time = 1

;-|Button Combination|-----------------------------------------------

[Command]
name = "max"
command = x+y+a
time = 1

[Command]
name = "longjump"
command = D, $U
time = 18

[Command]
name = "recovery"
command = x+a
time = 1

[Command]
name = "dodge"
command = x+y
time = 1

[Command]
name = "knockdown"
command = y+b
time = 1

[Command]
name = "roll"
command = x+a
time = 1

[Command]
name = "schange"
command = x+b
time = 1

[Command]
name = "ac"
command = a+c
time = 1

[Command]
name = "bc"
command = b+c
time = 1

[Command]
name = "abc"
command = a+b+c
time = 1

[Command]
name = "yb"
command = y+b
time = 1

[Command]
name = "xa"
command = x+a
time = 1

[Command]
name = "ab"
command = a+b
time = 1

[Command]
name = "xz"
command = x+z
time = 1

[Command]
name = "yz"
command = y+z
time = 1

;POWER UP
[Command]
name = "xyz"
command = x+y+z
time = 1

[Command]
name = "armor"
command = a+b+y
time = 1

[Command]
name = "counter"
command = x+y+b
time = 1

[Command]
name = "crossup"
command = ~b,a
time = 5

;------------------------------------------------------------------------------
;HOLD BUTTONS

[Command]
name = "hold_a"
command = /$a
time = 1

[Command]
name = "hold_b"
command = /$b
time = 1

[Command]
name = "hold_c"
command = /$c
time = 1

[Command]
name = "hold_x"
command = /$x
time = 1

[Command]
name = "hold_y"
command = /$y
time = 1

[Command]
name = "hold_z"
command = /$z
time = 1

[Command]
name = "hold_s"
command = /$s
time = 1

;==================================================================================
;DIR

[Command]
name = "fwd"
command = F
time = 1

[Command]
name = "back"
command = B
time = 1

;==================================================================================
;HOLD DIR

[Command]
name = "/DB"
command = /DB
time = 1

;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;HOLD DIR + BUTTON

[Command]
name = "holdfwd_x"
command = /$F, x
time = 1

[Command]
name = "holdfwd_y"
command = /$F, y
time = 1

[Command]
name = "fwd_a"
command = /F,a
time = 1

[Command]
name = "fwd_b"
command = /F,b
time = 1

[Command]
name = "fwd_x"
command = /F,x

[Command]
name = "fwd_z"
command = /F,z

[Command]
name = "back_z"
command = /B,z

[Command]
name = "back_a"
command = /B,a

[Command]
name = "back_x"
command = /B,x

[Command]
name = "fwd_y"
command = /F,y

[Command]
name = "back_y"
command = /B,y

[Command]
name = "down_y"
command = /D, y

[Command]
name = "down_b"
command = /D, b

[Command]
name = "down_z"
command = /D, z

;=========================================================
; -----------------<> COMMAND CODES <>------------------
;=========================================================

[Statedef -1]

[State -1, AI Helper Check]
type = ChangeState
trigger1 = IsHelper(9741)
value = 9741

[State -1, AI Helper Check 2]
type = ChangeState
trigger1 = IsHelper(9742)
value = 9742

;=========================
; COMBO VAR 
;=========================

;========================================
[State -1, Combo1]
type = Varset
trigger1 = 1
var(39) = 0

[State -1, Combo2]
type = Varset
trigger1 = stateno = 210 && animelemtime(4) > 1 && animelemtime(5) < 0
trigger2 = stateno = 230 && animelemtime(3) > 1 && animelemtime(4) < 0
trigger3 = stateno = 250 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger4 = stateno = 400 && animelemtime(3) > 1 && animelemtime(4) < 0
trigger5 = stateno = 440 && animelemtime(5) > 1 && animelemtime(6) < 0
trigger6 = stateno = 280 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger7 = stateno = 703 && animelemtime(5) > 1 && animelemtime(6) < 0 
trigger8 = stateno = 215 && animelemtime(5) > 1 && animelemtime(6) < 0 
trigger9 = stateno = 217 && animelemtime(4) > 1 && animelemtime(5) < 0 
trigger10 = stateno = 237 && animelemtime(9) > 1 && animelemtime(13) < 0 && movecontact
ignorehitpause = 1
var(39) = var(39) | 1

;======================
;COUNTER MODE COMBO VAR
;======================

[State -1, C.Combo1]
type = Varset
trigger1 = 1
var(42) = 0

[State -1, C.Combo3]
type = Varset
triggerall = var(40) > 0 || 1
trigger1 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger2 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger3 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2300 && Animelemtime(4) > 0
trigger6 = stateno = 2350 && Animelemtime(4) > 0
ignorehitpause = 1
var(42) = var(42) | 1

[State -1, KOF2K1 Special Cancel]
type = Varset
trigger1 = var(42) = 1
ignorehitpause = 1
var(45) = var(45)|1

[State -1, KOF2K1 Special Cancel]
type = Varset
trigger1 = var(42) = 0
var(45) = 0

;==============================================================================
;------|HYPER MOVES|-----
;==============================================================================

[State -1, 2K DM]
type = ChangeState
value = 3500
triggerall = var(9) != 1
triggerall = command = "2kdm" 
triggerall = power >= 1000
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

[State -1, SHIKI YAOTOME 1]
type = ChangeState
value = 3000
triggerall = var(9) != 1
triggerall = command = "asobi1" 
triggerall = power >= 1000
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

[State -1, SHIKI YAOTOME 2]
type = ChangeState
value = 3100
triggerall = var(9) != 1
triggerall = command = "asobi2" 
triggerall = power >= 1000
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

;====================================================================================
;---|SPECIAL MOVES|----
;====================================================================================

[State -1, Kototsuki 1]
type = ChangeState
value = 2500
triggerall = var(9) != 1
triggerall = command = "kototsuki1" 
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Kototsuki 2]
type = ChangeState
value = 2550
triggerall = var(9) != 1
triggerall = command = "kototsuki2" 
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Claw Scorch 1]
type = ChangeState
value = 2600
triggerall = var(9) != 1
triggerall = command = "scorch1"
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Claw Scorch 2]
type = ChangeState
value = 2650
triggerall = var(9) != 1
triggerall = command = "scorch2"
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, KuzuKaze]
type = ChangeState
value = 2400
triggerall = var(9) != 1
triggerall = command = "kuzukaze" 
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Oni Yaki 1]
type = ChangeState
value = 2300
triggerall = var(9) != 1
triggerall = command = "oniyaki1" 
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Oni Yaki 2]
type = ChangeState
value = 2350
triggerall = var(9) != 1
triggerall = command = "oniyaki2" 
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Aoi Hana 1]
type = ChangeState
value = 2100
triggerall = var(9) != 1
triggerall = command = "aoi1" 
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2620 && Animelemtime(1) > 1 && Animelemtime(3) <= 0
trigger4 = stateno = 2670 && Animelemtime(1) > 1 && Animelemtime(3) <= 0

[State -1, Aoi Hana 2]
type = ChangeState
value = 2200
triggerall = var(9) != 1
triggerall = command = "aoi2" 
trigger1 = statetype != A  && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2620 && Animelemtime(1) > 1 && Animelemtime(3) <= 0
trigger4 = stateno = 2670 && Animelemtime(1) > 1 && Animelemtime(3) <= 0

[State -1, Yami Barai 1]
type = ChangeState
value = 2000
triggerall = var(9) != 1
triggerall = command = "barai1" && numprojid(2005) <= 0
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

[State -1, Yami Barai 2]
type = ChangeState
value = 2050
triggerall = var(9) != 1
triggerall = command = "barai2" && numprojid(2005) <= 0
trigger1 = statetype != A && ctrl 
trigger2 = var(39) = 1
trigger3 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger4 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 11
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 11

;========================
; GROOVE CMDS
;========================

;COUNTER
[State -1]
type = Null ;ChangeState
value = 4850
triggerall = var(9) != 1
triggerall = command = "holdx" && command = "holdy" && command = "holda"
triggerall = numhelper(4805) <= 0 && power >= 3000
triggerall = var(40) <= 0
trigger1 = (stateno = [0,12]) && ctrl

;ARMOR
[State -1]
type = Null ;ChangeState
value = 4800
triggerall = var(9) != 1
triggerall = command = "holdy" && command = "holdb" && command = "holda"
triggerall = numhelper(4705) <= 0 && power >= 3000
triggerall = var(40) <= 0
trigger1 = (stateno = [0,12]) && ctrl

[State -1, Charge] 
type = ChangeState
value = 704
triggerall = var(9) != 1
triggerall = command = "hold_x" && command = "hold_y"
triggerall = life > 0 && statetype != A
triggerall = power < 3000 && var(40) <= 0 && var(37) <= 0
trigger1 = ctrl

;---------------------------------
[State -1,rollB Counter]
type = ChangeState
value = 710
triggerall = var(9) != 1
triggerall = command = "roll" && command = "holdback"
triggerall = power >= 1000 && life > 0 && statetype != A
trigger1 = stateno = 150 
trigger2 = stateno = 152 

[State -1,RollF counter]
type = ChangeState
value = 711
triggerall = var(9) != 1
triggerall = command = "roll" && command = "holdfwd"
triggerall = power >= 1000 && life > 0 && statetype != A
trigger1 = stateno = 150 
trigger2 = stateno = 152 

[State -1,CD counter]
type = ChangeState
value = 712
triggerall = var(9) != 1
triggerall = command = "knockdown"
triggerall = power >= 1000 && life > 0 && statetype != A
trigger1 = stateno = 150 
trigger2 = stateno = 152 

[State -1,rollB]
type = ChangeState
value = 701
triggerall = var(9) != 1
triggerall = command = "roll" && command = "holdback"
triggerall = life > 0 && statetype != A
trigger1 = ctrl

[State -1,rollF] 
type = ChangeState
value = 700
;triggerall = var(9) != 1
triggerall = command = "roll" && command = "holdfwd"
triggerall = life > 0 && statetype != A
trigger1 = ctrl

[State -1, Sidestep] 
type = ChangeState
value = 702
;triggerall = var(9) != 1
triggerall = command = "roll"
triggerall = life > 0 && statetype != A
trigger1 = ctrl

;=============================================================================
;-------------[Throws]------------------------
;===========================================================================
;GrabY
[State -1, GrabY ]
type = ChangeState
value = 300
triggerall = command = "y"
triggerall = statetype = S && ctrl && stateno != 100
trigger1 = command = "holdfwd" && p2bodydist X < 3 && p2movetype != H
trigger1 = (p2statetype = S) || (p2statetype = C)
trigger2 = command = "holdback" && p2bodydist X < 5 && p2movetype != H
trigger2 = (p2statetype = S) || (p2statetype = C)
;---------------------------------------------------------------------------
;---------------------------------------------------------------------------
;GrabB
[State -1, GrabB ]
type = ChangeState
value = 310
triggerall = command = "b"
triggerall = statetype = S && ctrl && stateno != 100
trigger1 = command = "holdfwd" && p2bodydist X < 3 && p2movetype != H
trigger1 = (p2statetype = S) || (p2statetype = C)
trigger2 = command = "holdback" && p2bodydist X < 5 && p2movetype != H
trigger2 = (p2statetype = S) || (p2statetype = C)
;===========================================================================

[State -1,Knockdown]
type = ChangeState
value = 280
triggerall = var(9) != 1
triggerall = command = "knockdown" 
trigger1 = statetype = S && ctrl 

;-------------------------------------------
[State -1,JCD]
type = ChangeState
value = 660
triggerall = var(9) != 1
triggerall = command = "knockdown"
trigger1 = statetype = A && ctrl
;-------------------------------------------
[State -1,Crossup]
type = ChangeState
value = 670
triggerall = var(9) != 1
triggerall = command = "a" 
trigger1 = statetype = A && ctrl 
trigger1 = ifelse(p2bodydist x < 0, command = "holdfwd", command = "holdback")
;========================[BASIC ATTACKS ]==================================

;Fwd-LP
[State -1, Fwd-LP]
type = ChangeState
value = 215
ignorehitpause = 1
triggerall = var(9) != 1
;triggerall = ifelse(movehit, hitpausetime = 10,1)
triggerall = command = "x" && command = "holdfwd"
trigger1 = statetype = S && ctrl
trigger2 = stateno = 210 && animelemtime(4) > 1 && animelemtime(5) < 0
trigger3 = stateno = 230 && animelemtime(3) > 1 && animelemtime(4) < 0
trigger4 = stateno = 250 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger5 = stateno = 400 && animelemtime(3) > 1 && animelemtime(4) < 0
trigger6 = stateno = 440 && animelemtime(5) > 1 && animelemtime(6) < 0
trigger7 = stateno = 280 && animelemtime(3) > 1 && animelemtime(5) < 0

;Fwd-LK
[State -1, Fwd-LK]
type = ChangeState
value = 235
ignorehitpause = 1
triggerall = var(9) != 1
triggerall = command = "a" && command = "holdfwd"
trigger1 = statetype = S && ctrl

;Fwd-LK
[State -1, Fwd-LK]
type = ChangeState
value = 237
ignorehitpause = 1
triggerall = var(9) != 1
;triggerall = ifelse(movehit, hitpausetime = 10,1)
triggerall = command = "a" && command = "holdfwd"
trigger1 = stateno = 210 && animelemtime(4) > 1 && animelemtime(5) < 0
trigger2 = stateno = 230 && animelemtime(3) > 1 && animelemtime(4) < 0
trigger3 = stateno = 250 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger4 = stateno = 400 && animelemtime(3) > 1 && animelemtime(4) < 0
trigger5 = stateno = 440 && animelemtime(5) > 1 && animelemtime(6) < 0
trigger6 = stateno = 280 && animelemtime(3) > 1 && animelemtime(5) < 0

;Lp Close
[State -1,Low Punch CLose]
type = ChangeState
value = 210
triggerall = var(9) != 1
triggerall = command = "x" && command != "holddown"
triggerall = p2bodydist x < 15
trigger1 = statetype = S && ctrl
trigger2 = stateno = 420 && animelemtime(4) > 0 && animelemtime(5) < 0

;Lp
[State -1,Lowpunch]
type = ChangeState
value = 200
triggerall = var(9) != 1
triggerall = command = "x"
triggerall = p2bodydist x >= 15
trigger1 = statetype = S && ctrl

;lk close
[State -1,LKClose]
type = ChangeState
value = 230
triggerall = var(9) != 1
triggerall = command = "a" && command != "holddown"
triggerall = p2bodydist x <= 22
trigger1 = statetype = S && ctrl
trigger2 = stateno = 420 && animelemtime(5) >=0 && animelemtime(6) <= 1

;lk
[State -1,LK]
type = ChangeState
value = 220
triggerall = var(9) != 1
triggerall = command = "a"
triggerall = p2bodydist x > 20
trigger1 = statetype = S && ctrl

;Hp close
[State -1,HPClose]
type = ChangeState
value = 250
triggerall = var(9) != 1
triggerall = command = "y"
triggerall = p2bodydist x <= 30
trigger1 = statetype = S && ctrl

;Hp 
[State -1,HP]
type = ChangeState
value = 240
triggerall = var(9) != 1
triggerall = command = "y"
triggerall = p2bodydist x > 30
triggerall = stateno != 250 && stateno != 240
trigger1 = statetype = S && ctrl

;Hk close
[State -1,HKClose]
type = ChangeState
value = 270
triggerall = var(9) != 1
triggerall = command = "b"
triggerall = p2bodydist x <= 25
trigger1 = statetype = S && ctrl

;Hk 
[State -1,HK]
type = ChangeState
value = 260
triggerall = var(9) != 1
triggerall = command = "b"
trigger1 = statetype = S && ctrl

[State -1,CLP]
type = ChangeState
value = 400
triggerall = var(9) != 1
triggerall = command = "x" && command = "holddown"
trigger1 = statetype = C && ctrl
trigger2 = stateno = 420 && animelemtime(4) > 1 && animelemtime(5) < 0

[State -1,CLK]
type = ChangeState
value = 420
triggerall = var(9) != 1
triggerall = command = "a" && command = "holddown"
trigger1 = statetype = C && ctrl

[State -1,CHP]
type = ChangeState
value = 440
triggerall = var(9) != 1
triggerall = command = "y"
trigger1 = statetype = C && ctrl

[State -1,CHK]
type = ChangeState
value = 460
triggerall = var(9) != 1
triggerall = command = "b"
trigger1 = statetype = C && ctrl

;----------------------------------------

[State -1,JLP]
type = ChangeState
value = 600
triggerall = var(9) != 1
triggerall = command = "x"
trigger1 = statetype = A && ctrl

[State -1,JLK]
type = ChangeState
value = 610
triggerall = var(9) != 1
triggerall = command = "a"
trigger1 = statetype = A && ctrl

[State -1,JHP]
type = ChangeState
value = 630
triggerall = var(9) != 1
triggerall = command = "y"
trigger1 = statetype = A && ctrl

[State -1,JHK]
type = ChangeState
value = 640
triggerall = var(9) != 1
triggerall = command = "b"
trigger1 = statetype = A && ctrl

[State -1,Animation Switch]
type = ChangeState
value = 196
triggerall = var(9) != 1
trigger1 = command = "switch"
trigger1 = statetype != A && ctrl

[State -1,TAUNT]
type = ChangeState
value = 195
triggerall = var(9) != 1
trigger1 = command = "taunt"
trigger1 = statetype != A && ctrl

[State -1,RUN]
type = ChangeState
value = 100
triggerall = var(9) != 1
triggerall = command = "FF"
trigger1 = statetype = S && ctrl

[State -1,HOPBACK]
type = ChangeState
value = 105
triggerall = var(9) != 1
trigger1 = command = "BB"
trigger1 = statetype = S && ctrl


;=====================================================================================
;-----[ AI MODIFICATION ]-----
;=====================================================================================
; High percent stand guard
[State -1]
type = ChangeState
value = 130
triggerall = p2movetype = A;access only when opponent attack
triggerall = P2bodydist X <= 40;access only when near
triggerall = random <= 700;high percent
triggerall = statetype != A;perform when not in air
triggerall = var(9) = 1;only AI can access
triggerall = ctrl;make sure AI had control
triggerall = stateno != 120
trigger1 = p2statetype = S

[State -1]
type = ChangeState
value = 130
triggerall = p2movetype = A;access only when opponent attack
triggerall = P2bodydist X <= 40;access only when near
triggerall = random <= 700;high percent
triggerall = statetype != A;perform when not in air
triggerall = var(9) = 1;only AI can access
triggerall = ctrl;make sure AI had control
triggerall = stateno != 130
trigger1 = p2statetype = A

;---------------------------------------------------------------------------
; High percent crouch guard
[State -1]
type = ChangeState
value = 131
triggerall = p2movetype = A;access only when opponent attack
triggerall = P2bodydist X <= 40;access only when near
triggerall = statetype != A;perform when not in air
triggerall = random <= 700;high percent
triggerall = var(9) = 1;only AI can access
triggerall = ctrl;make sure AI had control
triggerall = stateno != 131
trigger1 = p2statetype = C
;---------------------------------------------------------------------------

[State -1, Crossover]
type = ChangeState
value = 670
triggerall = var(9) = 1
triggerall = statetype = A && vel x != 0
triggerall = p2bodydist x <= -25 
trigger1 = vel y > .42 || p2bodydist Y <= 50 
trigger1 = ctrl

[State -1,JLK/JLP]
type = ChangeState
value = ifelse(random <=500,600,610)
triggerall = var(9) = 1
triggerall = random <= 500
trigger1 = statetype = A && (p2bodydist x = [1,40]) && p2bodydist Y <= 70 
trigger1 = ctrl && vel y > 0
trigger2 = stateno = 201 && ctrl && (p2bodydist x = [20,40]) && vel y > 0
trigger3 = statetype = A && (p2bodydist x = [1,40]) && p2statetype = A && ctrl

[State -1,JHK]
type = ChangeState
value = 640
triggerall = var(9) = 1
trigger1 = statetype = A && (p2bodydist x = [1,40]) && p2bodydist Y <= 70 
trigger1 = ctrl && vel y > 0
trigger2 = stateno = 201 && ctrl && (p2bodydist x = [20,40]) && vel y > 0
trigger3 = statetype = A && (p2bodydist x = [1,40]) && p2statetype = A && ctrl

[State -1,JCD]
type = ChangeState
value = 660
triggerall = var(9) = 1
triggerall = random <= 500
trigger1 = statetype = A && (p2bodydist x = [1,32]) && p2statetype = A && ctrl

;---------------------------------------------------------------------------
; High percent air guard
[State -1]
type = null ;ChangeState
value = 132
triggerall = p2movetype = A;access only when opponent attack
triggerall = P2bodydist X <= 40;access only when near
triggerall = P2life != 0;don't player when opponent had die
triggerall = statetype = A;perform when in air
triggerall = random <= 500;high percent
triggerall = var(9) = 1;only AI can access
triggerall = ctrl
triggerall = stateno != 132
trigger1 = p2statetype = A
;---------------------------------------------------------------------------

[State -1,Kuzukaze]
type = ChangeState
value = 2400
ctrl = 0
triggerall = var(9) = 1
trigger1 = (p2movetype = A || p2stateno = [700,799])&& random <= 1000 && p2bodydist x <= 25 && p2statetype != A 
trigger1 = p2statetype != L && statetype != A && ctrl && var(5) <= 0

;Hp close
[State -1,HPClose]
type = ChangeState
value = 250
triggerall = var(9) = 1
triggerall = (p2bodydist x = [0,23]) && p2movetype != A && p2statetype != A
triggerall = random <= 500 && p2statetype != L 
triggerall = statetype != A && ctrl
trigger1 = (p2stateno = [120,160]) && p2statetype != S
trigger2 = (p2stateno != [120,160])
trigger3 = p2stateno = 2420 && movetype = I

[State -1,CLK]
type = ChangeState
value = 230
triggerall = var(9) = 1
triggerall = p2statetype = S
trigger1 = (p2bodydist x = [5,15]) && random <= 800
trigger1 = statetype != A && ctrl
trigger2 = (p2bodydist x = [0,18]) && random <= 1000 && movecontact
trigger2 = stateno = 420 && animelemtime(5) >=0 && animelemtime(6) <= 1

[State -1,CrLK]
type = ChangeState
value = 420
triggerall = var(9) = 1
triggerall = (p2bodydist x = [5,15]) && random <= 1000
triggerall = p2statetype = S && p2statetype != A && p2movetype != H
trigger1 = statetype != A && ctrl

;Fwd-LP
[State -1, Fwd-LP]
type = ChangeState
value = 215
triggerall = var(9) = 1
triggerall = random <= 900
trigger1 = stateno = 210 && animelemtime(4) > 1 && animelemtime(5) < 0 && movecontact
trigger2 = stateno = 230 && animelemtime(3) > 1 && animelemtime(4) < 0 && movecontact
trigger3 = stateno = 400 && animelemtime(3) > 1 && animelemtime(4) < 0 && movecontact
trigger4 = p2stateno = 2420 && movetype = I && ctrl && statetype != A

;Forward + B
[State -1,FwdB]
type = ChangeState
value = 237
triggerall = var(9) = 1
trigger1 = movecontact && p2statetype != A
trigger1 = stateno = 250 && animelemtime(3) > 1 && animelemtime(5) < 0

[State -1, JUMP]
type = ChangeState
value = 40
triggerall = var(9) = 1
triggerall = statetype != A && ctrl && frontedgebodydist > 80
trigger1 = (p2bodydist x = [90,120]) && p2statetype != A && random <= 100 && p2movetype != H && p2movetype != A
trigger2 = (p2bodydist x = [0,40])   && p2statetype = C  && random <= 100 && p2movetype != H && p2movetype != A
trigger3 = (p2bodydist x = [51,89])  && p2stateno = 5120 && random <= 400
trigger4 = (p2bodydist x = [0,50])   && p2stateno = 5120 && random <= 600
trigger5 = (p2bodydist x = [90,120]) && p2stateno = 5120 && random <= 400

[State -1,Counter]
type = ChangeState
value = ifelse(random <= 400,712,711)
triggerall = var(9) = 1
triggerall = backedgebodydist <= 50
triggerall = power >= 1000 && (life = [1,50]) && statetype != A
trigger1 = stateno = 150 
trigger2 = stateno = 152 

;Poke attacks
[State -1,HK/Fwd+LP]
type = ChangeState
value = ifelse(random <= 500,215,260)
triggerall = var(9) = 1
triggerall = p2movetype != A && p2movetype != H && p2statetype != L && (p2bodydist x = [55,75]) && p2statetype != A
trigger1 = statetype != A && ctrl && random <= 150

;Crouch A
[State -1]
type = ChangeState
value = 400
triggerall = var(9) = 1
trigger1 = statetype != A && ctrl && p2movetype != H
trigger1 = random <= 300 && p2stateno != 100 && p2movetype != A && (p2bodydist x = [80,120]) && (enemy, vel x <= 0)
trigger2 = random <= 500 && stateno = 420 && animelemtime(4) > 1 && animelemtime(5) < 0 && movecontact

[State -1, SHIKI YAOTOME 2]
type = ChangeState
value = 3100
triggerall = var(9) = 1
triggerall = power >= 2000 && movehit && random <= 500
trigger1 = stateno = 237 && animelemtime(11) > 1 && animelemtime(13) < 0 
trigger2 = stateno = 703 && animelemtime(5) > 1 && animelemtime(6) < 0 
trigger3 = stateno = 215 && animelemtime(5) > 1 && animelemtime(6) < 0 && var(1) < 1
trigger4 = stateno = 217 && animelemtime(4) > 1 && animelemtime(5) < 0
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && power >= 3000
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && power >= 3000

[State -1, Aoi Hana 2]
type = ChangeState
value = 2200
triggerall = var(9) = 1
triggerall = ifelse(moveguarded, frontedgebodydist > 130, movehit)
trigger1 = stateno = 237 && animelemtime(11) > 1 && animelemtime(13) < 0 && p2bodydist x <= 60
trigger2 = stateno = 703 && animelemtime(5) > 1 && animelemtime(6) < 0 && p2bodydist x <= 60
trigger3 = stateno = 215 && animelemtime(5) > 1 && animelemtime(6) < 0 && var(1) < 1 
trigger4 = stateno = 217 && animelemtime(4) > 1 && animelemtime(5) < 0

[State -1, Aoi Hana 1]
type = ChangeState
value = 2100
triggerall = var(9) = 1
triggerall = movehit 
trigger1 = stateno = 2620 && Animelemtime(1) > 1 && Animelemtime(3) <= 0

[State -1, SHIKI YAOTOME 2]
type = ChangeState
value = 3100
triggerall = var(9) = 1
triggerall = power >= 2000 && movehit && random <= 500
trigger1 = stateno = 237 && animelemtime(11) > 1 && animelemtime(13) < 0 
trigger2 = stateno = 703 && animelemtime(5) > 1 && animelemtime(6) < 0 
trigger3 = stateno = 215 && animelemtime(5) > 1 && animelemtime(6) < 0 && var(1) < 1
trigger4 = stateno = 217 && animelemtime(4) > 1 && animelemtime(5) < 0
trigger5 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && power >= 3000
trigger6 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && power >= 3000

[State -1,Oniyaki]
type = ChangeState
value = ifelse (random <= 500,2350,2300)
triggerall = var(9) = 1
triggerall = ctrl && statetype != A && random <= 500
trigger1 = (p2bodydist x = [20,50]) && p2statetype = A && p2bodydist y < -40 && stateno != 2200
trigger1 = ifelse((p2stateno = [3300,3315]),p2movetype = H,p2movetype != H)
trigger2 = (p2bodydist x = [5,30]) && p2movetype = A 
trigger2 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1
trigger3 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1

[State -1, Yami Barai]
type = ChangeState
value = 2050
triggerall = var(9) = 1
triggerall = numprojid(2005) <= 0 && frontedgebodydist > 130 && random <= 500
trigger1 = statetype != A && ctrl && p2bodydist x > 200 && p2movetype != A && p2statetype != A && random <= 100 
trigger2 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && moveguarded
trigger3 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && moveguarded
trigger4 = random <= 500 && statetype != A && ctrl && (p2stateno = [200,500]) && p2bodydist x >= 100 && p2statetype != A
trigger5 = random <= 200 && statetype != A && ctrl && p2stateno = 5120 && p2bodydist x >= 120
trigger6 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && !movehit
trigger7 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && !movehit

[State -1, 2K DM]
type = ChangeState
value = 3500
triggerall = var(9) = 1 && power >= 2000
triggerall = numprojid(2005) <= 0 && frontedgebodydist > 130 && random <= 200
trigger1 = statetype != A && ctrl && p2bodydist x <= 40 && p2movetype != A && p2statetype != A && random <= 100 
trigger2 = random <= 500 && statetype != A && ctrl && (p2stateno = [200,500]) && p2bodydist x >= 30 && p2statetype != A
trigger3 = random <= 200 && statetype != A && ctrl && p2stateno = 5120 && p2bodydist x >= 50
trigger4 = stateno = 2100 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && !movehit
trigger5 = stateno = 2200 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && !movehit


[State -1, KototsukiIn]
type = ChangeState
value = ifelse(random <= 500,2500,2550)
triggerall = var(9) = 1 && random <= 400
trigger1 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && movehit
trigger2 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && movehit

[State -1, Claw Scorch]
type = ChangeState
value = 2600
triggerall = var(9) = 1 && random <= 700 &&  p2statetype = C
trigger1 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && movecontact
trigger2 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && movecontact

[State -1, Oniyaki]
type = ChangeState
value = ifelse(random <= 200,2350,2300)
triggerall = var(9) = 1 && random <= 400
trigger1 = stateno = 2120 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && movehit
trigger2 = stateno = 2220 && Animelemtime(5) > 1 && Animelemtime(6) <= 1 && movehit

[State -1,Grab]
type = ChangeState
value = ifelse(random <= 500,300,310)
triggerall = var(9) = 1
trigger1 = var(4) <= 0 && random <= 400 
trigger1 = p2stateno != 131 && p2stateno != 130 && P2bodydist X <= 10 && p2stateno != 1302 && statetype != A && p2statetype != A && p2statetype != L && p2stateno != 5120
trigger1 = p2movetype != H && p2movetype != A && ctrl

[State -1,ROLL BACK]
type = ChangeState
value = 701
triggerall = var(9) = 1
triggerall = statetype != A && ctrl && p2movetype != H
trigger1 = (p2bodydist x = [15,50]) && p2movetype = A && backedgebodydist > 60 && random <= 500

[State -1,HOPBACK]
type = ChangeState
value = 105
triggerall = var(9) = 1
triggerall = statetype != A && ctrl && p2movetype != H && backedgedist > 80
trigger1 = random <= 200 && P2statetype = L && (p2bodydist x = [10,40]) && frontedgebodydist <= 50
trigger2 = random <= 700 && p2movetype != A && frontedgebodydist <= 50

[State -1,RUN]
type = ChangeState
value = 100
triggerall = var(9) = 1
trigger1 = (stateno != [100,101]) && statetype = S && ctrl
trigger1 = p2bodydist x > 40 &&  p2movetype != A && random < 300

[State -1,Groundrecover]
type = ChangeState
value = 5201
triggerall = var(9) = 1  && canrecover
trigger1 = Vel Y > 0 && Pos Y >= 0 && life >0 && random <= 100 && (stateno = [5050,5060])

[State -1,ROLL BACK/Sidestep]
type = ChangeState
value = ifelse(random <= 500, 701,702)
triggerall = var(9) = 1 && NumEnemy
triggerall = statetype != A && ctrl && p2movetype != H && enemynear, HitDefAttr = SCA,AA
trigger1 = (p2bodydist x = [30,70]) && p2movetype = A && backedgebodydist > 60 && random <= 700
trigger1 = p2statetype != A


