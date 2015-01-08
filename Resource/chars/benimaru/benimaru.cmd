;===========================
;Benimaru CMD FILE [HARD AI]
;===========================

;-| Single Button |---------------------------------------------------------

[Command]
name = "b"
command = a
time = 1

[Command]
name = "d"
command = b
time = 1

[Command]
name = "c1"
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
name = "holdfwd";Required (do not remove)
command = /$F
time = 1

[Command]
name = "holdback";Required (do not remove)
command = /$B
time = 1

[Command]
name = "holdup";Required (do not remove)
command = /$U
time = 1

[Command]
name = "holddown";Required (do not remove)
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
name = "b2"
command = a
time = 1

[Command]
name = "d2"
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

;-| Taunt |--------------------------------------------------------

[Command]
name = "taunt"
command = s
time = 1

;-| Shortcuts |--------------------------------------------------------
[Command]
name = "RaikoukenX"
command = ~D, F, z
time = 35

; Raikouken (low)
[Command]
name = "RaikoukenA"
command = ~D, F, z
time = 35

; ElecTrigger
[Command]
name = "ElecTriggerX"
command = ~D, B, z
time = 35

[Command]
name = "ElecTrigger"
command = ~D, B, z
time = 35

; Gen'ei Hurricane
[Command]
name = "Gen'ei HurricaneX"
command = ~D, B, c
time = 35

[Command]
name = "Gen'ei Hurricane"
command = ~D, B, c
time = 35

[Command]
name = "SparkB"
command = ~D, F, c
time = 35

[Command]
name = "SparkX"
command = ~D, F, c
time = 35

;-| Super Motions |--------------------------------------------------------

; Raikouken SDM
[Command]
name = "RaikoukenX"
command = ~D, F, D, F, x+y
time = 30

; ElecTrigger SDM
[Command]
name = "ElecTriggerX"
command = ~DF, B, DF, B, x+y
time = 60

; Gen'ei Hurricane SDM
[Command]
name = "Gen'ei HurricaneX"
command = ~D, B, D, B, a+b
time = 30

; Raikouken (low)
[Command]
name = "RaikoukenA"
command = ~D, F, D, F, x
time = 30

; Raikouken (high)
[Command]
name = "RaikoukenC"
command = ~D, F, D, F, y
time = 30

; ElecTrigger
[Command]
name = "ElecTrigger"
command = ~DF, B, DF, B, x
time = 60

[Command]
name = "ElecTrigger"
command = ~DF, B, DF, B, y
time = 60

; Gen'ei Hurricane
[Command]
name = "Gen'ei Hurricane"
command = ~D, B, D, B, a
time = 30

[Command]
name = "Gen'ei Hurricane"
command = ~D, B, D, B, b
time = 30

; Spark
[Command]
name = "SparkX"
command = ~D, F, D, F, a+b
time = 30

; Spark
[Command]
name = "SparkA"
command = ~D, F, D, F, a
time = 30

[Command]
name = "SparkB"
command = ~D, F, D, F, b
time = 30

;-| Special Motions |------------------------------------------------------
;Flip Kick A
[Command]
name = "flipA"
command = ~F,D,DF, a
time = 12

;Flip Kick B
[Command]
name = "flipB"
command = ~F,D,DF, b
time = 12

;Raijinken
[Command]
name = "Raijinken A"
command = ~D, F, x
time = 15

[Command]
name = "Raijinken C"
command = ~D, F, y
time = 15

;Iaigeri
[Command]
name = "Iaigeri"
command = ~D, F, a
time = 12

[Command]
name = "Iaigeri"
command = ~D, F, b
time = 12

;Handou Sandan Geri
[Command]
name = "Handou Sandan Geri B"
command = ~D, U, a
time = 20

[Command]
name = "Handou Sandan Geri D"
command = ~D, U, b
time = 20

;Shinkuu Katategoma
[Command]
name = "Shinkuu Katategoma A"
command = ~D, B, x
time = 15

[Command]
name = "Shinkuu Katategoma C"
command = ~D, B, y
time = 15

;Benimaru Koreda
[Command]
name = "Benimaru Koreda"
command = ~F, DF, B, F, x
time = 30

[Command]
name = "Benimaru Koreda"
command = ~F, DF, B, F, y
time = 30

;Benimaru Koreda
[Command]
name = "Benimaru Koreda"
command = ~DF, B, F, x
time = 30

[Command]
name = "Benimaru Koreda"
command = ~DF, B, F, y
time = 30


;-| Double Tap |-----------------------------------------------------------
[Command]
name = "FF";Required (do not remove)
command = F, F
time = 10

[Command]
name = "BB";Required (do not remove)
command = B, B
time = 10

;-| 2/3 Button Combination |-----------------------------------------------
[Command]
name = "recovery";Required (do not remove)
command = x+a
time = 1

[Command]
name = "ab"
command = x+a
time = 1

[Command]
name = "cd"
command = y+b
time = 1

;-| Dir + Button |---------------------------------------------------------
[Command]
name = "fwd_a"
command = /F,x
time = 1

[Command]
name = "fwd_b"
command = /F,a
time = 1

[Command]
name = "fwd_c"
command = /F,y
time = 1

[Command]
name = "fwd_d"
command = /F,b
time = 1

[Command]
name = "back_a"
command = /B,x
time = 1

[Command]
name = "back_b"
command = /B,a
time = 1

[Command]
name = "back_c"
command = /B,y
time = 1

[Command]
name = "back_d"
command = /B,b
time = 1

[Command]
name = "down_a"
command = /$D,x
time = 1

[Command]
name = "down_b"
command = /$D,a
time = 1

[Command]
name = "down_c"
command = /$D,y
time = 1

[Command]
name = "down_d"
command = /$D,b
time = 1

[Command]
name = "fwd_ab"
command = /F, x+a
time = 1

[Command]
name = "back_ab"
command = /B, x+a
time = 1

[Command]
name = "back_ab"
command = /DB, x+a
time = 1

[Command]
name = "longjump"
command = ~D, $U
time = 8

[Command]
name = "longjump"
command = ~DF, $U
time = 8

[Command]
name = "longjump"
command = ~DB, $U
time = 8

;-| Single Button |---------------------------------------------------------
[Command]
name = "a"
command = x
time = 1

[Command]
name = "c"
command = y
time = 1

;-| Hold Button |-----------------------------------------------------------
[Command]
name = "hold_a"
command = /x
time = 1

[Command]
name = "hold_b"
command = /a
time = 1

[Command]
name = "hold_c"
command = /y
time = 1

[Command]
name = "hold_d"
command = /b
time = 1

[Command]
name = "hold_z"
command = /z
time = 1

[Command]
name = "hold_cc"
command = /c
time = 1

[Command]
name = "hold_s"
command = /s
time = 1

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
[State -1, Combo1]
type = Varset
trigger1 = 1
var(39) = 0

[State -1, Combo2]
type = Varset
trigger1 = stateno = 200 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger2 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 210 && animelemtime(4) > 1 && animelemtime(6) < 0
trigger4 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger5 = stateno = 225 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger6 = stateno = 235 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger7 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger8 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger9 = stateno = 420 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger10 = stateno = 430 && animelemtime(4) > 1 && animelemtime(6) < 0
trigger11 = stateno = 255 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger12 = stateno = 265 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger13 = stateno = 240 && animelemtime(5) > 1 && animelemtime(7) < 0
trigger14 = stateno = 703 && animelemtime(3) > 1 && animelemtime(5) < 0
ignorehitpause = 1
var(39) = var(39) | 1


;=========================
; SUPER CANCELS
;=========================
[State -1, C.Combo1]
type = Varset
trigger1 = 1
var(42) = 0

[State -1, C.Combo3]
type = Varset
triggerall = var(40) > 0 || 1
trigger1 = stateno = 1110 && animelemtime(5) > 1
trigger2 = stateno = 1125 && animelemtime(5) > 1
trigger3 = stateno = 1200 && animelemtime(4) > 1 && animelemtime(17) <= 0
trigger4 = stateno = 1210 && animelemtime(4) > 1 && animelemtime(17) <= 0
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

;===========================================================================
;SUPER ATTACKS (Chou Hissatsu Waza)
;===========================================================================
;Spark SDM
[State -1]
type = ChangeState
value = 3900
;triggerall = var(9) != 1
triggerall = power >= 2000 && command = "SparkX"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 3000 && var(42) = 1

;Raikouken SDM
[State -1]
type = ChangeState
value = 3500
triggerall = var(9) != 1
triggerall = power >= 2000 && command = "RaikoukenX"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 3000 && var(42) = 1

;Genei Hurricane
[State -1]
type = ChangeState
value = 3600
;triggerall = var(9) != 1
triggerall = power >= 2000 && command = "Gen'ei HurricaneX"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 3000 && var(42) = 1

;ElecTrigger
[State -1]
type = ChangeState
value = 3700
triggerall = var(9) != 1
triggerall = power >= 2000 && command = "ElecTriggerX"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 3000 && var(42) = 1

;===============================================================
;Spark
[State -1]
type = ChangeState
value = 3800
;triggerall = var(9) != 1
triggerall = power >= 1000 && command = "SparkA"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

[State -1]
type = ChangeState
value = 3850
;triggerall = var(9) != 1
triggerall = power >= 1000 && command = "SparkB"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

;Raikouken A
[State -1]
type = ChangeState
value = 3000
triggerall = var(9) != 1
triggerall = power >= 1000 && command = "RaikoukenA"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

;Raikouken C
[State -1]
type = ChangeState
value = 3050
triggerall = var(9) != 1
triggerall = power >= 1000 && command = "RaikoukenC"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

;Genei Hurricane
[State -1]
type = ChangeState
value = 3100
triggerall = var(9) != 1
triggerall = power >= 1000 && command = "Gen'ei Hurricane"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

;ElecTrigger
[State -1]
type = ChangeState
value = 3200
triggerall = var(9) != 1
triggerall = power >= 1000 && command = "ElecTrigger"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1
trigger3 = power >= 2000 && var(42) = 1

;===========================================================================
;SPECIAL ATTACKS (Hissatsu Waza)
;===========================================================================
;Flip Kick A
[State -1]
type = ChangeState
value = 1600
triggerall = var(9) != 1
triggerall = command = "flipA"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

;Flip Kick B
[State -1]
type = ChangeState
value = 1650
triggerall = var(9) != 1
triggerall = command = "flipB"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

;Iaigeri
[State -1]
type = ChangeState
value = 1100
triggerall = var(9) != 1
triggerall = command = "Iaigeri"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

;Benimaru Koreda
[State -1]
type = ChangeState
value = 1300
triggerall = var(9) != 1
triggerall = command = "Benimaru Koreda"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

;Raijinken
[State -1]
type = ChangeState
value = 1000
triggerall = var(9) != 1
triggerall = command = "Raijinken A"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

[State -1]
type = ChangeState
value = 1050
triggerall = var(9) != 1
triggerall = command = "Raijinken C"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

;Shinkuu Katategoma
[State -1]
type = ChangeState
value = 1200
triggerall = var(9) != 1
triggerall = command = "Shinkuu Katategoma A"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

[State -1]
type = ChangeState
value = 1210
triggerall = var(9) != 1
triggerall = command = "Shinkuu Katategoma C"
trigger1 = statetype != A && ctrl
trigger2 = var(39) = 1

;Air Raijinken
[State -1]
type = ChangeState
value = 1400
;triggerall = var(9) != 1
triggerall = command = "Raijinken A"
trigger1 = statetype = A && ctrl
trigger1 = pos y <= -50

[State -1]
type = ChangeState
value = 1450
;triggerall = var(9) != 1
triggerall = command = "Raijinken C"
trigger1 = statetype = A && ctrl
trigger1 = pos y <= -50

;===========================================================================
;DASH/BACKHOP
;===========================================================================
;RunFwd
[State -1]
type = ChangeState
value = 100
;triggerall = var(9) != 1
trigger1 = command = "FF"
trigger1 = statetype = S && ctrl

;RunBack
[State -1]
type = ChangeState
value = 105
;triggerall = var(9) != 1
trigger1 = command = "BB"
trigger1 = statetype = S && ctrl

;===========================================================================
;NORMAL THROWS (Nage)
;===========================================================================
;C THROW (close dir+Strong Punch)
[State -1]
type = ChangeState
value = 800
trigger1 = var(4) <= 0
trigger1 = statetype = S && ctrl && p2bodydist X < 10 ;Near P2
trigger1 = (command = "back_c" || command = "fwd_c") && stateno != 100 && (p2statetype = S || p2statetype = C) && p2movetype != H

;D THROW (close dir+Strong Kick)
[State -1]
type = ChangeState
value = 850
trigger1 = var(4) <= 0
trigger1 = statetype = S && ctrl && p2bodydist X < 10 ;Near P2
trigger1 = (command = "back_d" || command = "fwd_d") && stateno != 100 && (p2statetype = S || p2statetype = C)  && p2movetype != H

;D THROW (close dir+Strong Kick)
[State -1]
type = ChangeState
value = 900
trigger1 = statetype = A && ctrl && p2bodydist X < 20 && p2bodydist Y > -25 && p2bodydist Y < 25
trigger1 = (command = "back_d" || command = "fwd_d") && p2statetype = A && p2movetype != H

;===========================================================================
;CD ATTACKS
;===========================================================================
; Standing CD
[State -1]
type = ChangeState
value = 240
triggerall = var(9) != 1
trigger1 = command = "cd" && statetype != A && ctrl

; CD Counter
[State -1]
type = ChangeState
value = 245
;triggerall = var(9) != 1
trigger1 = command = "cd" && power >= 1000 && stateno = [150,153]

;===========================================================================
;ROLLS
;===========================================================================
[State -1, Charge]
type = ChangeState
value = 704
triggerall = var(9) != 1
triggerall = command = "hold_a" && command = "hold_c"
triggerall = life > 0 && statetype != A
triggerall = power < 3000 && var(40) <= 0 && var(37) <= 0
trigger1 = ctrl

; Guard Cancel Roll backward
[State -1]
type = ChangeState
value = 770
triggerall = var(9) != 1
trigger1 = command = "back_ab" && power >= 1000 && stateno = [150,153]

; Guard Cancel Roll Forward
[State -1]
type = ChangeState
value = 760
;triggerall = var(9) != 1
trigger1 = command = "ab" && power >= 1000 && stateno = [150,153]

;Roll Backward
[State -1]
type = ChangeState
value = 740
triggerall = var(9) != 1
trigger1 = command = "back_ab" && statetype = S && ctrl

;Roll Forward
[State -1]
type = ChangeState
value = 700
triggerall = var(9) != 1
trigger1 = command = "fwd_ab" && statetype = S && ctrl

[State -1, Sidestep]
type = ChangeState
value = 702
;triggerall = var(9) != 1
triggerall = command = "ab"
triggerall = life > 0 && statetype != A
trigger1 = ctrl

;===========================================================================
;COMMAND NORMAL ATTACKS
;===========================================================================
;Forward + B Normal
[State -1]
type = ChangeState
value = 250
triggerall = var(9) != 1
triggerall = command = "fwd_b" && command != "holddown"
trigger1 = statetype = S && ctrl

;Forward + B Combo (KOF2K1 Style)
[State -1]
type = ChangeState
value = 260
triggerall = var(9) != 1
triggerall = command = "fwd_b" && command != "holddown"
trigger1 = var(39) = 1 && stateno != 255 && stateno != 265 && stateno != 240

;Flying Drill
[State -1]
type = ChangeState
value = 650
;triggerall = var(9) != 1
triggerall = command = "down_d" && statetype = A
trigger1 = ctrl
trigger2 = stateno = 620 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger3 = stateno = 106

;===========================================================================
;CROUCHING NORMAL ATTACKS
;===========================================================================
;Crouching A
[State -1]
type = ChangeState
value = 400
triggerall = var(9) != 1
triggerall = command = "a"
triggerall = command = "holddown"
trigger1 = statetype = C && ctrl
trigger2 = stateno = 200 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger4 = stateno = 210 && animelemtime(4) > 1 && animelemtime(6) < 0
trigger5 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger6 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger7 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0

;Crouching B
[State -1]
type = ChangeState
value = 410
triggerall = var(9) != 1
triggerall = command = "b"
triggerall = command = "holddown"
trigger1 = statetype = C && ctrl
trigger2 = stateno = 200 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger4 = stateno = 210 && animelemtime(4) > 1 && animelemtime(6) < 0
trigger5 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger6 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger7 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0

;Crouching C
[State -1]
type = ChangeState
value = 420
triggerall = var(9) != 1
triggerall = command = "c"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl

;Crouching D
[State -1]
type = ChangeState
value = 430
triggerall = var(9) != 1
triggerall = command = "d"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl

;===========================================================================
;CLOSE STANDING NORMAL ATTACKS
;===========================================================================
;Close A
[State -1]
type = ChangeState
value = 205
triggerall = var(9) != 1
triggerall = command = "a" && command != "holddown"
triggerall = p2bodydist x < 20
trigger1 = statetype = S && ctrl
trigger2 = stateno = 200 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger4 = stateno = 210 && animelemtime(4) > 1 && animelemtime(6) < 0
trigger5 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger6 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger7 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0

;Forward + B
[State -1]
type = ChangeState
value = 290
triggerall = var(9) != 1
triggerall = command = "fwd_b"
trigger1 = statetype = S && ctrl

;Close B
[State -1]
type = ChangeState
value = 215
triggerall = var(9) != 1
triggerall = command = "b"
triggerall = p2bodydist x < 20
triggerall = command != "holddown"
trigger1 = statetype = S && ctrl
trigger2 = stateno = 200 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger4 = stateno = 210 && animelemtime(4) > 1 && animelemtime(6) < 0
;trigger5 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger5 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger6 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0

;Close C
[State -1]
type = ChangeState
value = 225
triggerall = var(9) != 1
triggerall = command = "c"
triggerall = p2bodydist x < 20
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;Close D
[State -1]
type = ChangeState
value = 235
triggerall = var(9) != 1
triggerall = command = "d"
triggerall = p2bodydist x < 20
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;===========================================================================
;STANDING NORMAL ATTACKS
;===========================================================================
;Standing A
[State -1]
type = ChangeState
value = 200
triggerall = var(9) != 1
triggerall = command = "a"
triggerall = command != "holddown"
trigger1 = statetype = S && ctrl
trigger2 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger4 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger5 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0

;Standing B
[State -1]
type = ChangeState
value = 210
triggerall = var(9) != 1
triggerall = command = "b"
triggerall = command != "holddown"
trigger1 = statetype = S && ctrl
trigger2 = stateno = 205 && animelemtime(2) > 1 && animelemtime(4) < 0
trigger3 = stateno = 215 && animelemtime(3) > 1 && animelemtime(5) < 0
trigger4 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger5 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0

;Standing C
[State -1]
type = ChangeState
value = 220
triggerall = var(9) != 1
triggerall = command = "c"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;Standing D
[State -1]
type = ChangeState
value = 230
triggerall = var(9) != 1
triggerall = command = "d"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;===========================================================================
;JUMPING NORMAL ATTACKS
;===========================================================================
;Jumping CD
[State -1]
type = ChangeState
value = 640
triggerall = var(9) != 1
triggerall = command = "cd"
trigger1 = statetype = A
trigger1 = ctrl

;Jumping Up A
[State -1]
type = ChangeState
value = 605
triggerall = var(9) != 1
trigger1 = command = "a"
trigger1 = statetype = A
trigger1 = ctrl
trigger1 = stateno != 950 && vel x = 0

;Jumping A
[State -1]
type = ChangeState
value = 600
triggerall = var(9) != 1
trigger1 = command = "a"
trigger1 = statetype = A
trigger1 = ctrl

;Jumping B
[State -1]
type = ChangeState
value = 610
triggerall = var(9) != 1
trigger1 = command = "b"
trigger1 = statetype = A
trigger1 = ctrl

;Jumping C
[State -1]
type = ChangeState
value = 620
triggerall = var(9) != 1
trigger1 = command = "c"
trigger1 = statetype = A
trigger1 = ctrl

;Jumping Up D
[State -1]
type = ChangeState
value = 635
;triggerall = var(9) != 1
trigger1 = command = "d"
trigger1 = statetype = A
trigger1 = ctrl
trigger1 = stateno != 950 && vel x = 0

;Jumping D
[State -1]
type = ChangeState
value = 630
triggerall = var(9) != 1
trigger1 = command = "d"
trigger1 = statetype = A
trigger1 = ctrl

;===========================================================================
;TAUNT
;===========================================================================
[State -1]
type = ChangeState
value = 195
triggerall = var(9) != 1
triggerall = command = "s"
trigger1 = statetype = S
trigger1 = ctrl

;=====================================================================================
;-----[ AI MODIFICATION ]-----
;=====================================================================================

;Raikouken SDM/Genei SDM
[State -1, RaikoukenSDM]
type = ChangeState
value = ifelse(random <= 700,3500,3600)
triggerall = var(9) = 1
triggerall = power >= 2000
triggerall = statetype != A && ctrl
trigger1 = (p2bodydist x = [30,60]) && p2statetype = A && p2movetype != H
trigger2 = stateno = 265 && animelemtime(3) > 0 && animelemtime(4) < 0 && movehit
trigger3 = power >= 3000 && var(42) = 1 && movehit && random <= 500

;Spark SDM
[State -1, SparkSDM]
type = ChangeState
value = ifelse(random <= 800,3900,3900)
triggerall = var(9) = 1
triggerall = power >= 2000
triggerall = statetype != A && ctrl
trigger1 = (p2bodydist x = [30,60]) && p2statetype = A && p2movetype != H
trigger2 = stateno = 265 && animelemtime(3) > 0 && animelemtime(4) < 0 && movehit
trigger3 = power >= 3000 && var(42) = 1 && movehit && random <= 500

;Spark DM
[State -1, SparkDM]
type = ChangeState
value = ifelse(random<=900,3800,3850)
triggerall = var(9) = 1
triggerall = power >= 1000
triggerall = statetype != A && ctrl
trigger1 = (p2bodydist x = [30,50]) && p2statetype = A && p2movetype != H
trigger2 = power >= 2000 && var(42) = 1 && movehit && random <= 500

;Raikouken C/ Genei
[State -1, RaikoukenDM]
type = ChangeState
value = ifelse(random<=900,3050,3100)
triggerall = var(9) = 1
triggerall = power >= 1000
triggerall = statetype != A && ctrl
trigger1 = (p2bodydist x = [30,50]) && p2statetype = A && p2movetype != H
trigger2 = power >= 2000 && var(42) = 1 && movehit && random <= 500

;Raikouken A/Genei
[State -1,RaikoukenDM]
type = ChangeState
value = ifelse(random<=500,3000,3100)
triggerall = var(9) = 1
triggerall = power >= 1000
trigger1 = stateno = 265 && animelemtime(3) > 0 && animelemtime(4) < 0 && movehit
trigger2 = stateno = 420 && animelemtime(3) > 1 && animelemtime(5) < 0 && movehit
trigger3 = power >= 2000 && var(42) = 1 && movehit && random <= 500

[State -1,Flip Kick]
type = ChangeState
value = ifelse (random <= 500,1600,1650)
triggerall = var(9) = 1
trigger1 = (p2bodydist x = [0,30]) && p2statetype = A && ctrl && statetype != A
trigger1 = ifelse((p2stateno = [3300,3315]),p2movetype = H,p2movetype != H)

;Raijiken C
[State -1, RaijikenC]
type = ChangeState
value = 1050
ctrl = 0
triggerall = var(9) = 1
trigger1 = p2statetype = A && (p2bodydist x = [40,50]) && p2bodydist y <= -110
trigger1 = random <= 400 && statetype != A && ctrl
trigger2 = random <= 200 && p2stateno = 40 && statetype != A && ctrl

;Electrigger SDM
[State -1, ElectriggerSDM]
type = ChangeState
value = 3700
ctrl = 0
triggerall = var(9) = 1
triggerall = (power >= 2000 && statetype != A)
trigger1 = p2bodydist x <= 15 && p2statetype != A && p2statetype != L
trigger1 = statetype != A && ctrl && var(5) <= 0

;Electrigger DM
[State -1, Electrigger]
type = ChangeState
value = 3200
ctrl = 0
triggerall = var(9) = 1
triggerall = (power >= 1000 && statetype != A)
trigger1 = p2bodydist x <= 15 && p2statetype != A && p2statetype != L
trigger1 = statetype != A && ctrl && var(5) <= 0

;Koreda
[State -1,Koreda]
type = ChangeState
value = 1300
ctrl = 0
triggerall = var(9) = 1
triggerall = random <= 1000 && p2bodydist x <= 20 && p2statetype != L && p2movetype != H
trigger1 = statetype != A && ctrl ;&& var(5) <= 0
trigger2 = stateno = 400 && animelemtime(2) > 1 && animelemtime(3) < 0
trigger3 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0


;Iaigeri
[State -1,Iaigeri]
type = ChangeState
value = 1100
triggerall = var(9) = 1
trigger1 = statetype != A
trigger1 = p2bodydist x <= 20
trigger1 = stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0 && movecontact

;Hk/Hp close
[State -1,HK/HPClose]
type = ChangeState
value = ifelse(random<=700,225,235)
triggerall = var(9) = 1
trigger1 = (p2bodydist x = [0,19]) && p2movetype != A && p2statetype != A
trigger1 = random <= 900 && p2statetype != L
trigger1 = statetype = S && ctrl

[State -1,StHP]
type = ChangeState
value = 220
triggerall = var(9) = 1
triggerall = (p2bodydist x = [45,65]) && random <= 500
triggerall = p2statetype != L && p2statetype != A
trigger1 = statetype != A && ctrl && p2stateno <= 100

[State -1, CrLK]
type = ChangeState
value = 410
triggerall = var(9) = 1 && NumEnemy
triggerall = statetype != A && (ctrl || (stateno = [100,101])) && p2movetype != H
trigger1 = random <= 50 && p2stateno != 100 && p2movetype != A && (p2bodydist x = [100,140]) && (enemynear, vel x <= 0)
trigger2 = random <= 500 && p2statetype = S && p2bodydist x <= 25
trigger2 = ifelse((p2stateno = [200,999]), p2movetype != I,1)
trigger3 = random <= 500 && stateno = 410 && animelemtime(2) > 1 && animelemtime(4) < 0 && moveguarded


;Charge
[State -1, Charge]
type = ChangeState
value = 704
ctrl = 0
triggerall = var(9) = 1
trigger1 = p2movetype = H && (p2stateno = [7000,7050])
trigger1 = statetype != A && ctrl && stateno != 704
trigger1 = random <= 700 && power < 3000 && var(40) <= 0

;---------------------------------------------------------------------------
; High percent stand guard
[State -1]
type = ChangeState
value = 130
triggerall = p2movetype = A
triggerall = P2bodydist X <= 50
triggerall = random <= 900
triggerall = statetype != A
triggerall = var(9) = 1
triggerall = ctrl
triggerall = stateno != 120
trigger1 = p2statetype = S

[State -1]
type = ChangeState
value = 130
triggerall = p2movetype = A
triggerall = P2bodydist X <= 40
triggerall = random <= 900
triggerall = statetype != A
triggerall = var(9) = 1
triggerall = ctrl
triggerall = stateno != 130
trigger1 = p2statetype = A
;---------------------------------------------------------------------------

; High percent crouch guard
[State -1]
type = ChangeState
value = 131
triggerall = p2movetype = A;access only when opponent attack
triggerall = P2bodydist X <= 60;access only when near
triggerall = statetype != A;perform when not in air
triggerall = var(9) = 1;only AI can access
triggerall = ctrl || stateno = 151
triggerall = stateno != 131
trigger1 = p2statetype = C
;-----------------------------------------------------------------------------------------
;---------------------------------------------------------------------------

[State -1,JHKD/JHPD]
type = ChangeState
value = ifelse(random <=200,620,630)
triggerall = var(9) = 1 && NumEnemy
triggerall = statetype = A && ctrl
trigger1 = random <= 700 && p2bodydist x <= 50 && p2statetype != A && p2statetype != L
trigger1 = p2bodydist y <= 60 && vel y >= 0 && ifelse(enemynear, vel x < 0, p2stateno != 20,1)
trigger2 = random <= 600 && p2bodydist x <= 60 && p2statetype != A && p2statetype != L
trigger2 = p2bodydist y <= 80 && vel y >= 0 && p2movetype = A
trigger3 = random <= 100 && p2bodydist x <= 50 && p2statetype != A && p2statetype != L
trigger3 = p2bodydist y <= 60 && vel y >= 0

[State -1,JLK]
type = ChangeState
value = ifelse(random <=700,600,610)
triggerall = var(9) = 1
trigger1 = statetype = A && ctrl
trigger1 = random <= 400 && p2bodydist x <= 100 && p2statetype = A && p2movetype != H

[State -1,JCD]
type = ChangeState
value = 640
triggerall = var(9) = 1
trigger1 = random <= 100 && p2bodydist x <= 60 && p2statetype != A && p2statetype != L
trigger1 = p2bodydist y <= 80 && vel y >= 0 && p2movetype = A && statetype = A && ctrl
trigger2 = statetype = A && ctrl
trigger2 = random <= 100 && p2bodydist x <= 100 && p2statetype = A

[State -1,ROLL Forward]
type = ChangeState
value = 700
triggerall = var(9) = 1 && NumEnemy
triggerall = statetype != A && ctrl && p2movetype != H
trigger1 = (p2bodydist x = [31,90]) && p2movetype = A && frontedgebodydist > 60 && random <= 500
trigger1 = p2stateno >= 1000 && (enemynear, facing) != facing
trigger1 = enemynear, HitDefAttr = SCA,AA && p2statetype != A

[State -1,ROLL BACK/Sidestep]
type = ChangeState
value = ifelse(random <= 500, 702,740)
triggerall = var(9) = 1 && NumEnemy
triggerall = statetype != A && ctrl && p2movetype != H && enemynear, HitDefAttr = SCA,AA
trigger1 = (p2bodydist x = [30,70]) && p2movetype = A && backedgebodydist > 60 && random <= 700
trigger1 = p2statetype != A

[State -1, JUMP]
type = ChangeState
value = 40
triggerall = var(9) = 1
triggerall = statetype != A && ctrl && p2movetype != H
trigger1 = (p2bodydist x = [150,180]) && p2statetype != A && random <= 100 && p2movetype != A
trigger2 = (p2bodydist x = [10,20])  && p2statetype = C && random <= 200

;CrHP
[State -1, CrHP]
type = ChangeState
value = 420
triggerall = var(9) = 1
trigger1 = (p2bodydist x = [15,30]) && p2statetype != A && p2movetype != A
trigger1 = random <= 900 && p2statetype != L
trigger1 = statetype != A && ctrl

[State -1,CrHK]
type = ChangeState
value = 430
triggerall = var(9) = 1
trigger1 = (p2bodydist x = [35,50]) && random <= 200
trigger1 = p2statetype = S && p2movetype != A
trigger1 = statetype != A && ctrl

[State -1,Drill]
type = ChangeState
value = 650
triggerall = var(9) = 1
triggerall = random <= 700 && statetype = A
triggerall = p2bodydist x <= 50 && p2statetype = C
triggerall = vel x <= 0 && pos y <= -45
trigger1 = vel y < 0 && ctrl
trigger2 = vel y < .45 && stateno = 201 && ctrl

[State -1,CD counter]
type = ChangeState
value = 245
triggerall = var(9) = 1
triggerall = backedgebodydist <= 50
triggerall = power >= 1000 && life > 0 && statetype != A
trigger1 = stateno = 150
trigger2 = stateno = 152

;Shinkuu Katategoma
[State -1,Shinkuu]
type = ChangeState
value = 1210
triggerall = var(9) = 1
triggerall = statetype != A && p2bodydist x = [20,50]
trigger1 = stateno = 265 && animelemtime(3) > 0 && animelemtime(4) < 0 && movecontact
trigger2 = stateno = 420 && animelemtime(3) > 1 && animelemtime(5) < 0 && movecontact

;Forward + B
[State -1,FwdB]
type = ChangeState
value = 260
triggerall = var(9) = 1
triggerall = movecontact && p2statetype != A
trigger1 = stateno = 225 && animelemtime(3) > 1 && animelemtime(5) < 0 && movecontact
trigger2 = stateno = 235 && animelemtime(3) > 1 && animelemtime(5) < 0 && movecontact
trigger3 = stateno = 420 && animelemtime(3) > 1 && animelemtime(5) < 0 && moveguarded

;Raijinken A
[State -1,Raijiken]
type = ChangeState
value = 1000
triggerall = var(9) = 1
triggerall = statetype != A && p2bodydist x = [0,20]
trigger1 = stateno = 265 && animelemtime(3) > 0 && animelemtime(4) < 0 && movehit
trigger2 = stateno = 420 && animelemtime(3) > 1 && animelemtime(5) < 0 && movehit

[State -1,HOPBACK]
type = ChangeState
value = 105
triggerall = var(9) = 1
triggerall = statetype != A && ctrl && backedgedist > 80
trigger1 = random <= 800 && p2movetype != A && P2statetype = L && (p2bodydist x = [50,90]) && frontedgebodydist <= 50
trigger2 = random <= 800 && p2movetype != A && frontedgebodydist <= 50 && P2statetype = L

[State -1,RUN]
type = ChangeState
value = 100
triggerall = var(9) = 1
trigger1 = (stateno != [100,101]) && statetype = S && ctrl
trigger1 = p2bodydist x > 40 &&  p2movetype != A && p2statetype != L && random < 300

;Crouch A/B
[State -1]
type = ChangeState
value = ifelse(random <= 500,400,410)
triggerall = var(9) = 1 && NumEnemy
trigger1 = statetype != A && ctrl && random <= 300
trigger1 = p2stateno != 100 && p2movetype != A && (p2bodydist x = [80,120]) && (enemynear, vel x <= 0)

[State -1,Groundrecover]
type = ChangeState
value = 5201
triggerall = var(9) = 1  && canrecover && backedgebodydist > 70
trigger1 = Vel Y > 0 && Pos Y >= 0 && life >0 && random <= 100 && (stateno = [5050,5060])
