
;先行入力時誤認識防止用
[Command]
name = "hadou"
command = ~D,F,D
time = 20

;先行入力時誤認識防止用
[Command]
name = "hadou"
command = ~D,B,D
time = 20

;連打
[Command]
name = "renda"
command = a,a
time = 70

;連打
[Command]
name = "renda"
command = b,b
time = 70

;連打
[Command]
name = "renda"
command = x,x
time = 70

;連打
[Command]
name = "renda"
command = y,y
time = 70


;カウンターモード
[Command]
name = "Countermode"
command = a+x+y
time =1

;獄殺
[command]
name="gokusatu"
command=a,a,F,b,x
time=36


;神塵
[Command]
name = "kamukura"     
command = ~D, B, D, B, x
time = 26

;神塵
[Command]
name = "kamukura"     
command = ~D, B, D, B, y
time = 26

;大蛇薙LV3
[Command]
name = "oroti3"     
command = ~D, B, D, F, x+y
time = 26

;大蛇薙LV3
[Command]
name = "oroti3"     
command = ~D, B, D, F, c
time = 26


;大蛇ナギ強
[Command]
name = "oroti2"     
command = ~D, B, D, F, y
time = 26

;大蛇ナギ弱
[Command]
name = "oroti1"     
command = ~D, B, D, F, x
time = 26


;蒸器LV2
[command]
name="musiki"
command=~D,F,D,F,x
time=30


;蒸器
[command]
name="musiki"
command=~D,F,D,F,y
time=30

;182
[Command]
name = "182"
command = D,F,D,F, a
time = 30

;182
[Command]
name = "182"
command = D,F,D,F, b
time = 30

;ＥＸ鬼焼き
[command]
name="exoni"
command=F,D,DF,x+y
time=20

;ＥＸ鬼焼き
[command]
name="exoni"
command=F,D,DF,c
time=20


;おにやき弱
[command]
name="jy"
command=~F,D,DF,x
time=12


;おにやき強
[command]
name="jk"
command=~F,D,DF,y
time=12

;じらいしん弱
[command]
name="ziraiy"
command=F,D,DF,a
time=20


;じらいしん強
[command]
name="ziraik"
command=F,D,DF,b
time=20




;ぎゃくよが 弱
[command]
name="gody"
command=DF,D,B,x
time=27

;ぎゃくよが 強
[command]
name="godk"
command=DF,D,B,y
time=27

;ぎゃくよが 強
[command]
name="godk"
command=DF,D,B,c
time=27

;ことづき EX1
[command]
name="exkotoduki"
command=DF,D,B,a+b
time=25

;ことづき EX1
[command]
name="exkotoduki"
command=DF,D,B,c
time=25



;ことづき 弱
[command]
name="exy"
command=DF,D,B,a
time=15


;ことづき 強
[command]
name="exk"
command=DF,D,B,b
time=15




;；７５式弱
[command]
name="by"
command=DF,F, a
time=10


;；75式強
[command]
name="bk"
command=DF,F, b
time=10


;ＲＥＤ　弱
[command]
name="redy"
command=~B,D,BD,a
time=20

;ＲＥＤ　強
[command]
name="redk"
command=~B,D,BD,b
time=20

;-------------

;ＥＸどくがみ
[command]
name="exdoku"
command=D, F, x+y
time=17

;ＥＸどくがみ2
[command]
name="exdoku"
command=D, F, c
time=17

;あらがみ
[Command]
name = "oke"     
command = DF, F, x
time = 10

;どくがみ
[Command]
name = "oke2"     
command = DF, F, y
time = 10

;ぬえつみ 弱
[command]
name="nuey"
command=DF,B,x
time=10

;ぬえつみ 強
[command]
name="nuek"
command=DF,B,y
time=15

;弱引き金
[command]
name = "hiki_j"
command = DF,D,B,a
time = 15

;みきりうがち
[command]
name = "mikiri_j"
command = D,~D,D,x
time = 15

;みきりうがち
[command]
name = "mikiri_k"
command = D,~D,D,y
time = 15

;だっしゅ
[Command]
name = "FF"     
command = F, F
time = 10

;ばっくすてっぷ
[Command]
name = "BB"     
command = B, B
time = 10


;うけみ
[Command]
name = "recovery"
command = x+a
time = 20


[Command]
name = "down_a"
command = /$D,a
time = 1

[Command]
name = "down_b"
command = /$D,b
time = 1

;じゃんぷにー
[command]
name="J,nee"
command= U, b
time=30

;じゃんぷあっぱー
[command]
name="j,appa"
command= U, a
time=30 


[command]
name="~a"
command=~x
time=1

[command]
name="~x"
command=~y
time=1

[command]
name="~b"
command=~a
time=1

[command]
name="~y"
command=~b
time=1


[command]
name="/a"
command=/x
time=1


[command]
name="/x"
command=/y
time=1

;同時押しボタンの押しっぱなし
[command]
name = "/c"
command = /c
time = 1

[command]
name="zenten"
command=a+x
time=4

;ふっとばし
[Command]
name = "huttobashi"
command = z
time = 1

;ぱんち
[Command]
name = "a"
command = x
time = 1

;きっく
[Command]
name = "b"
command = a
time = 1

;強パンチ
[Command]
name = "x"
command = y
time = 1

;強キック
[Command]
name = "y"
command = b
time = 1

;豪富
[command]
name="gouhu"
command=/F,a
time=1

;ばつよみ1
[command]
name="batu"
command=/F,x
time=1

;ばつよみ2
[command]
name="batu"
command=/F,y
time=1

;ばつよみ3
[command]
name="batu"
command=/F,c
time=1

[Command]
name = "x+y"
command = c
time = 1

[Command]
name = "x+y"
command = y+b
time = 1

[Command]
name = "c"
command = x+a
time = 1

[Command]
name = "ather c"
command = /B,x+a
time=30

[command]
name="dfy"
command=/DF,b
time=1


[command]
name="dx"
command=/$D,y
time=1

[command]
name="Bx"
command=/B,y
time=1

[command]
name="By"
command=/B,b
time=1

[command]
name="FJ"
command=UF
time=1

[command]
name="BJ"
command=UB
time=1

[command]
name="U"
command=U
time=1

[command]
name="D"
command=$D
time=1

[Command]
name= "canj"
command= /$U
time=1

[command]
name="/$a"
command=/$a
time=1

[command]
name="/$x"
command=/$x
time=1

[command]
name="tyouhatu"
command=s
time=1



; 押しっぱなし設定（いじらない）-------------------------------------------------------
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

;押しっぱなし
[Command]
name = "hold_x"
command = /x
;押しっぱなし
[Command]
name = "hold_x"
command = /y
;押しっぱなし
[Command]
name = "hold_x"
command = /a
;押しっぱなし
[Command]
name = "hold_x"
command = /b
;押しっぱなし
[Command]
name = "hold_x"
command = /c

[Command]
name = "hold_a"
command = /a

; 下の記述↓は絶対に消さないでください。
[Statedef -1]

;===========================================================================
;遅キャンステータス
[state -1,xxxy]
type = varset
v = 48
value = 5
trigger1 = stateno = 232
trigger2=stateno=200
trigger2=time = [6,9]
trigger3=Stateno=211
trigger3=time = [7,8]
trigger4=stateno=221
trigger4 = time = [12,14]
trigger5=stateno=232
trigger5 = time = [8,9]
trigger6=stateno=400
trigger6=time = [6,9]
trigger7=stateno=410
trigger7=0
trigger8=stateno=420
trigger8 = time = [7,9]
trigger9=stateno=420
trigger9 = time = [7,9]
trigger10=stateno=220
trigger10 = time = [15,17]
trigger11=stateno=245
trigger11 = time = [17,19]
trigger12=stateno=201
trigger13=stateno=250
trigger13 = time = [22,24]
trigger13 = Numhelper(255) = 0
trigger14=stateno=271
trigger14 = time = [5,8]
trigger15=stateno=440
trigger15=time = [10,14]
trigger15=animelem = 1 || animelem = 2 || animelem = 3 || animelem = 4 || animelem = 5
trigger16 = stateno = 803
ignorehitpause = 1
ignorepausetime = 1


;キャンセル可能ステータス消去
[state -1,xx24]
type = varset
trigger1 = stateno >= 1000
trigger2 = stateno = 231
trigger3 = stateno = 240
trigger4 = stateno = 211
trigger5 = stateno = 210
trigger6 = stateno = 300
trigger7 = stateno = 801
trigger8 = stateno = 245
trigger8 = time < 18
v = 48
value = 0

;カウンターモード鬼焼きスパキャン用
[state -1,321]
type = varset
triggerall = var(41) > 0
v = 48
value = 3
trigger1 = stateno = 2005
trigger2 = stateno = 2105


;超技キャンセル可能技ステータス
[state -1,x]
type = varset
v = 48
value = 2
triggerall = 0
trigger1 = 0
trigger2=stateno=200
trigger2 = time >= 4
trigger3=Stateno=211
trigger4=stateno=221
trigger5=stateno=232
trigger6=stateno=400
trigger7=stateno= time >= 4
trigger8=stateno=440
trigger9=stateno=420
trigger10=stateno=220
trigger11=stateno=245
trigger11 = time > 14
trigger12=stateno=201
trigger13=stateno=250 && var(44) = 0
trigger14=stateno=271 ;スパキャン
trigger15=stateno=440 ;スパキャン
trigger16=stateno=240 ;スパキャン
trigger17 = stateno = 420
ignorehitpause = 1
ignorepausetime = 1

;必殺技キャンセル可能技
[state -1,xxx]
type = varset
v = 48
value = 1
trigger1 = 0
trigger2=stateno=200
trigger2=time = [4,5]
trigger3=Stateno=211
trigger3=time = [5,6]
trigger4=stateno=221
trigger4 = time = [7,11]
trigger5=stateno=232
trigger5 = time = [5,7]
trigger6=stateno=400
trigger6=time = [4,5]
trigger7=stateno=410
trigger7=0
trigger8=stateno=420
trigger8 = time = [4,6]
trigger9=stateno=420
trigger9 = time = [4,6]
trigger10=stateno=220
trigger10 = time = [10,14]
trigger11=stateno=245
trigger11 = time = [14,16]
trigger12=stateno=201
trigger13=stateno=250
trigger13=time = [19,21]
trigger13 = Numhelper(255) = 0
trigger14=stateno=271
trigger14 = time = [1,4]
trigger15=stateno=440
trigger15=time = [8,9]
trigger15=animelem = 1 || animelem = 2 || animelem = 3 || animelem = 4 || animelem = 5
trigger16 = stateno = 803
ignorehitpause = 1
ignorepausetime = 1

;===========================================================================
;カウンターモード
[State -1,1]
type = ChangeState
value = 900
triggerall = command = "Countermode"
triggerall = statetype != A
triggerall=power>=3000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,3]
ignorehitpause = 1

;カウンターモード大蛇薙　弱
[state -1,2]
type = changestate
value = 39999
triggerall = command = "oroti1"
triggerall = var(41) >0
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = [1,3]
trigger3=Stateno=6010 ;琴月
trigger4=stateno=1050 ;派生ぬえつみ
ignorehitpause = 1

;カウンターモード大蛇薙　強
[state -1,2]
type = changestate
value = 310499
triggerall = command = "oroti2"
triggerall = var(41) >0
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = [1,3]
trigger3=Stateno=6010 ;琴月
trigger4=stateno=1050 ;派生ぬえつみ
trigger5=Stateno=2005 ;鬼焼き弱
trigger6=stateno=2105 ;鬼焼き強
ignorehitpause = 1

;カウンターモード182式
[state -1,2]
type = changestate
value = 315999
triggerall = command = "182"
triggerall = var(41) >0
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = [1,3]
trigger3=Stateno=6010 ;琴月
trigger4=stateno=1050 ;派生ぬえつみ
trigger5=Stateno=2005 ;鬼焼き弱
trigger6=stateno=2105 ;鬼焼き強
ignorehitpause = 1

;カウンター無式
[State -1]
type = ChangeState
value =317999
triggerall = command = "musiki"
triggerall = var(41) >0
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = [1,3]
trigger3=Stateno=6010 ;琴月
trigger4=stateno=1050 ;派生ぬえつみ
trigger5=Stateno=2005 ;鬼焼き弱
trigger6=stateno=2105 ;鬼焼き強
ignorehitpause = 1

;神塵
[State -1]
type = ChangeState
value = 19300
triggerall = command = "kamukura"
triggerall = statetype != A
triggerall=power>=3000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,2]
ignorehitpause = 1

;大蛇ナギ　ＬＶ3
[State -1]
type = ChangeState
value = 10999
triggerall = command = "oroti3"
triggerall = statetype != A
triggerall=power>=3000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,2]
ignorehitpause = 1

;大蛇ナギ　ＬＶ2
[State -1]
type = ChangeState
value = 10499
triggerall = command = "oroti2"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,2]
ignorehitpause = 1

;大蛇ナギ　ＬＶ１
[State -1]
type = ChangeState
value = 9999
triggerall = command = "oroti1"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,2]
ignorehitpause = 1

;182式
[State -1]
type = ChangeState
value =15999
triggerall = command = "182"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,2]
ignorehitpause = 1

;無式
[State -1]
type = ChangeState
value =17999
triggerall = command = "musiki"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = ctrl = 1
trigger2 = var(48) = [1,2]
ignorehitpause = 1


;おにやき強
[State -1]
type = ChangeState
value = 2100
triggerall = var(45) = 0
triggerall = command = "jk"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;おにやき弱
[State -1]
type = ChangeState
value = 2000
triggerall = var(45) = 0
triggerall = command = "jy"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;ことづき強
[State -1]
type = ChangeState
value = 6199
triggerall = command = "exk"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;ＲＥＤ弱
[State -1]
type = ChangeState
value = 3999
triggerall = command = "redy"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1


;ＲＥＤ強
[State -1]
type = ChangeState
value = 4050
triggerall = command = "redk"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;弱引き金
[State -1]
type = ChangeState
value =4270
triggerall = command = "hiki_j"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;あらがみ
[State -1]
type = ChangeState
value = 1000
triggerall = var(45) = 0
triggerall = command = "oke"
triggerall = statetype != A
trigger1=ctrl=1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;どくがみ
[State -1]
type = ChangeState
value = 1500
triggerall = var(45) = 0
triggerall = command = "oke2"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1


;----------------------------------------

;７５式改　弱
[State -1]
type = ChangeState
value = 3000
triggerall = var(45) = 0
triggerall = command = "by"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1


;７５式改　強
[State -1]
type = ChangeState
value = 3005
triggerall = var(45) = 0
triggerall = command = "bk"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;ぬえつみ　弱
[State -1]
type = ChangeState
value = 7000
triggerall = var(45) = 0
triggerall = command = "nuey"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;ぬえつみ　強
[State -1]
type = ChangeState
value = 7100
triggerall = var(45) = 0
triggerall = command = "nuek"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;生出しみきりうがち 弱
[State -1]
type = ChangeState
value = 1041
triggerall = var(45) = 0
triggerall = command = "mikiri_j"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;生出しみきりうがち　強
[State -1]
type = ChangeState
value = 1040
triggerall = var(45) = 0
triggerall = command = "mikiri_k"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 || var(48) = 5
ignorehitpause = 1

;だっしゅ
[State -1, Run Fwd]
type = ChangeState
value = 100
trigger1 = command = "FF"
trigger1 = statetype = S
trigger1 = ctrl

;---------------------------------------------------------------------------
;ばっくすてっぷ
[State -1, Run Back]
type = ChangeState
value = 105
trigger1 = command = "BB"
trigger1 = statetype = S
trigger1 = ctrl

;--------------------------------------

;ダウン回避
[state 321]
type = changestate
value = 797
triggerall = time > 10
triggerall = movetype = H
triggerall = statetype = A
triggerall = pos Y <=0
triggerall = pos Y >-18
triggerall = command = "zenten" 
triggerall =life >1
trigger1 = stateno = 5050
trigger2 = stateno = 5071
trigger3 = stateno = 5100

;ガーキャン後転
[state -1]
type=changestate
value=7961
triggerall=command="zenten"
triggerall=command="holdback"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = stateno=150
trigger2=stateno=151
trigger3=stateno=152
trigger4=stateno=153
ignorehitpause = 1

;ガーキャン前転
[state -1]
type=changestate
value=7951
triggerall=command="zenten"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = stateno=150
trigger2=stateno=151
trigger3=stateno=152
trigger4=stateno=153
ignorehitpause = 1

;後転
[state -1]
type=changestate
value=796
triggerall=command="zenten"
triggerall=command="holdback"
triggerall=ctrl=1
trigger1=statetype=S
trigger2=Statetype=C

;前転
[state -1]
type=changestate
value=795
triggerall=command="zenten"
triggerall=ctrl=1
trigger1=statetype=S
trigger2=Statetype=C


;---------------------------------------------------------------------------
;ぶんなげ
[State -1, Kung Fu Throw]
type = ChangeState
value = 700
triggerall = command = "x"
triggerall = statetype = S
triggerall = ctrl
triggerall = stateno != 100
trigger1 = command = "holdfwd"
trigger1 = p2bodydist X < 3
trigger1 = (p2statetype = S) || (p2statetype = C)
trigger1 = p2movetype != H
trigger2 = command = "holdback"
trigger2 = p2bodydist X < 5
trigger2 = (p2statetype = S) || (p2statetype = C)
trigger2 = p2movetype != H

;--------------------------
;ぎゃくにぶんなげ（わざわざつくらんでも・・・）
[State -1, Kung Fu Throw]
type = ChangeState
value = 811
triggerall = command = "ather c"
triggerall = statetype = S
triggerall = ctrl
triggerall = stateno != 100
trigger1 = command = "holdfwd"
trigger1 = p2bodydist X < 12
trigger1 = (p2statetype = S) || (p2statetype = C)
trigger1 = p2movetype != H
trigger2 = command = "holdback"
trigger2 = p2bodydist X < 15
trigger2 = (p2statetype = S) || (p2statetype = C)
trigger2 = p2movetype != H

;---------------------------------------------------------------------------
;ぶんなげ
[State -1, Kung Fu Throw]
type = ChangeState
value = 750
triggerall = command = "y"
triggerall = statetype = S
triggerall = ctrl
triggerall = stateno != 100
trigger1 = command = "holdfwd"
trigger1 = p2bodydist X < 3
trigger1 = (p2statetype = S) || (p2statetype = C)
trigger1 = p2movetype != H
trigger2 = command = "holdback"
trigger2 = p2bodydist X < 5
trigger2 = (p2statetype = S) || (p2statetype = C)
trigger2 = p2movetype != H


;===========================================================================
;ごうふ生
[State -1]
type = ChangeState
value = 240
triggerall = command = "holdfwd"
triggerall = command = "b"
triggerall = statetype != A
trigger1=ctrl=1
trigger2 = var(48) = 5
trigger2 = stateno != 245
;===========================================================================
;ごうふきゃんせる版
[State -1]
type = ChangeState
value = 245
triggerall = var(45) = 0
triggerall = command = "gouhu"
triggerall = statetype != A
trigger1 = ctrl = 1
trigger2 = var(48) = 1 
trigger2 = stateno != 245




;---------------------------------------------------------------------------
;後ろ強パンチ
[State -1, Stand Strong Punch]
type = ChangeState
value = 221
triggerall = command = "Bx"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl

;後ろ強キック
[State -1, Stand Strong Punch]
type = ChangeState
value = 230
triggerall = command = "By"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl


;ガードキャンセルふっとばし
[State -1, Kung Fu Throw]
type = ChangeState
value = 251
triggerall = command = "x+y"
triggerall = statetype != A
triggerall=power>=1000
trigger1 = stateno=150
trigger2=stateno=151
trigger3=stateno=152
trigger4=stateno=153
ignorehitpause = 1

;地上ふっとばし
[State -1, Kung Fu Throw]
type = ChangeState
value = 250
triggerall = command = "x+y"
triggerall = statetype = S
trigger1 = ctrl


;挑発
[State -1, Kung Fu Throw]
type = ChangeState
value = 195
triggerall = command = "tyouhatu"
triggerall = statetype = S
trigger1 = ctrl
triggerall=var(17)=0


;近距離立ち弱パンチ
[State -1, Kung Fu Throw]
type = ChangeState
value = 200
triggerall = command = "a"
triggerall = statetype = S
triggerall = command != "holddown"
triggerall = command != "holdfwd"
trigger1 = ctrl
trigger2=stateno=300
trigger3=stateno=400
trigger4=stateno = 201
trigger5 = stateno = 211
triggerall = p2bodydist X < 23


;近距離立ち弱キック
[State -1, Kung Fu Throw]
type = ChangeState
value = 211
triggerall = command = "b"
triggerall = command != "holddown"
triggerall = statetype != A
triggerall = command != "holdfwd"
trigger1 = ctrl
trigger2=stateno=300
trigger2 = movehit = 1
trigger3=stateno=400
trigger3 = movehit = 1
trigger4=stateno = 211
trigger4 = movehit = 1
trigger5 = stateno = 201
trigger5 = movehit = 1
triggerall = p2bodydist X < 23


;近距離立ち強パンチ
[State -1, Kung Fu Throw]
type = ChangeState
value = 270
triggerall = command = "x"
triggerall = statetype = S
trigger1 = ctrl
triggerall = p2bodydist X < 40

;近距離立ち強キック
[State -1, Kung Fu Throw]
type = ChangeState
value = 232
triggerall = command = "y"
triggerall = statetype = S
trigger1 = ctrl
triggerall = p2bodydist X < 47


;遠距離弱パンチ
[State -1, Stand Light Punch]
type = ChangeState
value = 200
triggerall = command = "a"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl
trigger2=stateno=200
trigger3 = stateno = 300
trigger3 = movehit = 1
trigger4 = stateno = 400
trigger4 = movehit = 1
trigger5 = stateno = 211
trigger5 = movehit = 1
trigger6 = stateno = 201
trigger6 = movehit = 1


;---------------------------------------------------------------------------
;遠距離弱キック
[State -1, Stand Strong Punch]
type = ChangeState
value = 210
triggerall = command = "b"
triggerall = command != "holddown"
triggerall = p2bodydist X >= 23
trigger1 = statetype = S
trigger1 = ctrl
trigger2=stateno=200
trigger3 = stateno = 300
trigger3 = movehit = 1
trigger4 = stateno = 400
trigger4 = movehit = 1
trigger5 = stateno = 211
trigger5 = movehit = 1
trigger6 = stateno = 201
trigger6 = movehit = 1


;---------------------------------------------------------------------------
;遠距離強パンチ
[State -1, Stand Strong Punch]
type = ChangeState
value = 220
triggerall = command = "x"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl


;-------------------------------
;遠距離強きっく
[State -1, Stand Strong Punch]
type = ChangeState
value = 231
triggerall = command = "y"
triggerall = command != "holddown"
trigger1 = statetype = S
trigger1 = ctrl



;---------------------------------------------------------------------------
;しゃがみあっぱー
[State -1, Crouching Light Punch]
type = ChangeState
value = 400
triggerall = command = "a"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl
trigger2 = stateno = 300
trigger3 = stateno = 400
trigger4 = stateno = 201
trigger4 = movehit = 1
trigger5 = stateno = 211
trigger5 = movehit = 1
trigger6 = stateno = 200
trigger6 = movehit = 1
;しゃがみあっぱー
[State -1, Crouching Light Punch]
type = ChangeState
value = 400
triggerall = command = "~a"
triggerall = command = "holddown"
trigger1 = stateno = 52

;---------------------------------------------------------------------------
;しゃがみきっく
[State -1, Crouching Strong Punch]
type = ChangeState
value = 300
triggerall = command = "b"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl =1
trigger2 = stateno = 300
trigger3 = stateno = 400
trigger4 = stateno = 201
trigger4 = movehit = 1
trigger5 = stateno = 211
trigger5 = movehit = 1
trigger6 = stateno = 200
trigger6 = movehit = 1
;しゃがみあっぱー
[State -1, Crouching Light Punch]
type = ChangeState
value = 300
triggerall = command = "~b"
triggerall = command = "holddown"
trigger1 = stateno = 52

;しゃがみ強パンチ
[State -1, Crouching Light Punch]
type = ChangeState
value = 420
triggerall = command = "x"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl
;しゃがみあっぱー
[State -1, Crouching Light Punch]
type = ChangeState
value = 420
triggerall = command = "~x"
triggerall = command = "holddown"
trigger1 = stateno = 52

;しゃがみ強キック
[State -1, Crouching Light Punch]
type = ChangeState
value = 440
triggerall = command = "y"
triggerall = command = "holddown"
trigger1 = statetype = C
trigger1 = ctrl
;しゃがみあっぱー
[State -1, Crouching Light Punch]
type = ChangeState
value = 440
triggerall = command = "~y"
triggerall = command = "holddown"
trigger1 = stateno = 52


;------------------------------
;奈落落とし
[state -1]
type=changestate
value=650
triggerall = command = "dx"
trigger1 = statetype = A
trigger1 = ctrl
trigger2=stateno=610
trigger3=stateno=105
;------------------------------
;空中フットばし
[state -1]
type=changestate
value=660
triggerall = command = "x+y"
trigger1 = statetype = A
trigger1 = ctrl


;---------------------------------------------------------------------------
;じゃんぷぱんち
[State -1, Jump Light Punch]
type = ChangeState
value = 600
triggerall = command = "a"
trigger1 = statetype = A
trigger1 = ctrl
;---------------------------------------------------------------------------
;じゃんぷきっく
[State -1, Jump Light Punch]
type = ChangeState
value = 610
triggerall = command = "b"
triggerall = statetype = A
trigger1 = ctrl 

;---------------------------------------------------------------------------
;垂直Ｊ強パンチ
[State -1, Jump Strong Punch]
type = ChangeState
value = 620
triggerall = command = "x"
triggerall = statetype = A
trigger1=ctrl=1

;---------------------------------------------------------------------------
;垂直Ｊ強キック
[State -1, Jump Strong Punch]
type = ChangeState
value = 630
triggerall = command = "y"
triggerall = statetype = A
trigger1 = ctrl 

;-------------------------
;大ジャンプ　前
;[state -1]
;type=changestate
;value=4520
;triggerall=statetype!=A
;triggerall=command="FJ"
;triggerall=var(15)=1
;trigger1=ctrl=1
;trigger1 = stateno = 40

;大ジャンプ前入力方法２
[state -1]
triggerall = ctrl = 1
type  = varset
trigger1=command="FJ"
trigger1=var(15)=1
trigger1 = pos Y = 0
v = 15
value = 2

;大ジャンプ前発動
[state -1]
type = changestate
triggerall = ctrl = 1
trigger1 = var (15) = 2
trigger1 = statetype = A
value = 4520
persistant = 0
;-------------------------
;大ジャンプ　
;[state -1]
;type=changestate
;value=4521
;triggerall=statetype!=A
;triggerall=command="U"
;triggerall=var(15)=1
;trigger1=ctrl=1
;trigger1 = stateno = 40

;大ジャンプ　後ろ
;[state -1]
;type=changestate
;value=4522
;triggerall=statetype!=A
;triggerall=command="BJ"
;triggerall=var(15)=1
;trigger1=ctrl=1
;trigger1 = stateno = 40

;大ジャンプ前入力方法２
[state -1]
type  = varset
triggerall = ctrl = 1
trigger1=command="BJ"
trigger1=var(15)=1
trigger1 = pos Y = 0
v = 15
value = 3

;大ジャンプ前発動
[state -1]
type = changestate
triggerall = ctrl = 1
trigger1 = var (15) = 3
trigger1 = statetype = A
value = 4522
persistant = 0
;*********************************************************
;先行入力関係
;*********************************************************
;===========通常技================
;ぶっとばし
[state -1]
type = varset
v = 29
value = 250
trigger1 = command = "x+y"
ignorehitpause = 1

[state -1]
type = varset
v = 29
value = 200
trigger1 = command = "a"
ignorehitpause = 1

;レバー入れ大P
[state -1]
type = varset
v = 29
value = 221
trigger1 = command = "holdback"
trigger1 = command = "x"
ignorehitpause = 1
;近距離立ち強P
[state -1]
type = varset
v = 29
value = 270
trigger1 = var(29) = 220
trigger1 = p2bodydist x < 40
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 220
trigger1 = command = "x"
trigger1 = command != "holdback"
ignorehitpause = 1
;レバー入れ小K
[state -1]
type = varset
v = 29
value = 240
trigger1 = command = "holdfwd"
trigger1 = command = "b"
ignorehitpause = 1
;近距離時
[state -1]
type = varset
v = 29
value = 211
trigger1 = command = "b"
trigger1 = p2bodydist x < 23
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 210
trigger1 = command = "b"
trigger1 = command != "holdfwd"
ignorehitpause = 1
;レバー入れ大K
[state -1]
type = varset
v = 29
value = 230
trigger1 = command = "holdback"
trigger1 = command = "y"
ignorehitpause = 1
;近距離時
[state -1]
type = varset
v = 29
value = 232
trigger1 = var(29) = 231
trigger1 = p2bodydist x < 47
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 231
trigger1 = command = "y"
trigger1 = command != "holdback"
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 250
trigger1 = command = "x+y"
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 400
trigger1 = command = "a"
trigger1 = command = "holddown"
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 300
trigger1 = command = "b"
trigger1 = command = "holddown"
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 420
trigger1 = command = "x"
trigger1 = command = "holddown"
ignorehitpause = 1
[state -1]
type = varset
v = 29
value = 440
trigger1 = command = "y"
trigger1 = command = "holddown"
ignorehitpause = 1
;前転
[state -1]
type = varset
v = 29
value = 795
trigger1 = command = "zenten"
trigger1 = command != "holdback"
ignorehitpause = 1
;前転
[state -1]
type = varset
v = 29
value = 796
trigger1 = command = "zenten"
trigger1 = command = "holdback"
ignorehitpause = 1
;*******************************************************:
;必殺技
;カウンターLV２大蛇
[state -1]
type = varset
v = 29
value = 310499
trigger1 = var(41) > 0
trigger1 = command = "oroti2"
ignorehitpause = 1
;カウンターLV1大蛇
[state -1]
type = varset
v = 29
value = 39999
trigger1 = var(41) > 0
trigger1 = command = "oroti1"
ignorehitpause = 1
;カウンター182shiki
[state -1]
type = varset
v = 29
value =315999
triggerall = command = "182"
trigger1 = var(41) > 0
ignorehitpause = 1
;カウンターmusiki
[state -1]
type = varset
v = 29
value =317999
triggerall = command = "musiki"
trigger1 = var(41) > 0
ignorehitpause = 1


;LV３大蛇
[state -1]
type = varset
v = 29
triggerall=power>=2000
trigger1 = command = "oroti3"
value = 10999
ignorehitpause = 1
;LV２大蛇
[state -1]
type = varset
v = 29
value = 10499
triggerall=power>=1000
trigger1 = command = "oroti2"
ignorehitpause = 1
;LV1大蛇
[state -1]
type = varset
v = 29
value = 9999
triggerall=power>=1000
trigger1 = command = "oroti1"
ignorehitpause = 1
;182shiki
[state -1]
type = varset
v = 29
value =15999
triggerall = command = "182"
trigger1=power>=1000
ignorehitpause = 1
;musiki
[state 1]
type = varset
v = 29
value =17999
triggerall = command = "musiki"
trigger1=power>=1000
ignorehitpause = 1
[state 2]
type = varset
triggerall = var(45) = 0
trigger1 = command = "oke"
v = 29
value = 1000
ignorehitpause = 1

[state -1]
type = varset
v = 29
value = 20099
triggerall = command = "exoni"
trigger1=power>=1000
ignorehitpause = 1

[state -1]
type = varset
v = 29
value = 2100
triggerall = var(45) = 0
trigger1 = command = "jk"
ignorehitpause = 1
;oni_y
[state -1]
type = varset
v = 29
value = 2000
triggerall = var(45) = 0
trigger1 = command = "jy"
ignorehitpause = 1
;kotoduki
[state -1]
type = varset
v = 29
value = 6199
trigger1 = command = "exk"
ignorehitpause = 1
;red_y
[state -1]
type = varset
v = 29
value = 3999
trigger1 = command = "redy"
ignorehitpause = 1
;red_k
[state -1]
type = varset
v = 29
value = 4050
trigger1 = command = "redk"
ignorehitpause = 1

;hiki_j
[state -1]
type = varset
v = 29
value =4270
trigger1 = command = "hiki_j"
ignorehitpause = 1

;dok
[state -1]
type = varset
v = 29
value = 1500
triggerall = var(45) = 0
trigger1 = command = "oke2"
ignorehitpause = 1
;75y
[state -1]
type = varset
v = 29
value = 3000
triggerall = var(45) = 0
trigger1 = command = "by"
ignorehitpause = 1
;75k
[state -1]
type = varset
v = 29
value = 3005
triggerall = var(45) = 0
trigger1 = command = "bk"
ignorehitpause = 1

[state -1]
type = varset
v = 29
value = 7000
trigger1 = command = "nuey"
ignorehitpause = 1

[state -1]
type = varset
v = 29
value = 7100
trigger1 = command = "nuek"
ignorehitpause = 1

;押しっぱなし外すと解除
[state -1]
type = varset
trigger1 =  command != "hold_x"
trigger1 = var(46) > 5
v = 29
value = 0

;先行入力時カウント
[state -1]
type = varadd
trigger1 = var(29) != 0
v = 46
value = 1

;先行入力カウント一定以上で先行入力消去
[state -1]
type = varset
trigger1 = var(46) > 25
v = 29
value = 0

;カウントも振り出しへ
[state -1]
type = varset
trigger1 = var(29) = 0
v = 46
value = 0

[state -1]
type = null
trigger1 = statetype != A
trigger1 = ctrl = 1
trigger1 = var(29) != 0
value = var(29)

;空波動入力時フラグON
[state -1]
type = varset
trigger1 = Command = "hadou"
v = 45
value = 1

;空波動入力時カウント
[state -1]
type = varadd
trigger1 = var(45) = 1
v = 47
value = 1

;空波動入力カウント一定以上で先行入力消去
[state -1]
type = varset
trigger1 = var(47) > 25
v = 45
value = 0

;open ai
[state -1, end]
type = null
trigger1 = AILevel
v = 41
value = 1

;カウントも振り出しへ
[state 1, end]
type = varset
trigger1 = var(47) > 25
v = 47
value = 0



