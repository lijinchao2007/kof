-------------------------------------------------------------------------------------------------
          =======================================================================
                  --------------------| SANDER 71113 |-------------------
                                   sander71113@gmail.com
                                  http://go.to/sander71113 

===========================
 IORI YAGAMI X VERSION .99
===========================

DATE: May 5, 2002

----------------------------------------------------------------------------------------------

 *** CHARACTER ***
   
 Iori Yagami X is taken from the KOF SERIES (95-2001). This version is based mostly on KOF2K1.
 Definitely a worthy rival of Kyo Kusanagi, Iori has it all: style, attitude, very effective 
 moves and not to mention crazy antics. He has a lot of combos, so either research a bit, or 
 watch his AI beat the crap out of you (assisting suicide? :P). Please take the time to read 
 the accompanying documentations to enjoy him better. 

 Mugenized by Sander71113(sander71113@gmail.com).
 
 *- MODE:
    1. KOF2001 + KOF98/99
   
 *- Artificial Intelligence: 
    1. Hard level   - iori.cmd
    2. Medium level - iorimedai.cmd
    3. Low Level    - iorinoai.cmd

 *- REQUIREMENTS:
    1. M.U.G.E.N. engine - found at http://www.elecbyte.com
    2. Faster than 300 mhz processor. 
    3. 64MB or higher Ram.

----------------------------------------------------------------------------------------------

 *** M.U.G.E.N. ***
 
 To use Iori Yagami X, you need the latest build of "M.U.G.E.N." engine 
 which can found at http://www.elecbyte.com. 


 ----------------------------------------------------------------------------------------------

 ----------------------------------------------------------------------------------------------

 *** IORIX's FILES AND USE ***

 Upon unzipping the Zip file(s), You should now have these:
 
 DOCUMENTATIONS:
 readme.txt
 history.txt
 
 CODES:
 iorix.def        
 iori.cns
 ioria.cns
 iorib.cns
 ioric.cns
 iorid.cns

 COMMANDS AND AI:
 iori.cmd
 iorimedai.cmd
 iorinoai.cmd

 ANIMATION:        
 iori.air 

 SPRITES:
 iori.sff   

 SOUNDS:
 yagami.snd 
 
 PALETTES:
 pal1.act
 pal2.act
 pal3.act 
 pal4.act
 pal5.act
 pal6.act
 pal7.act
 pal8.act
 pal9.act 
 pal10.act
 pal11.act
 pal12.act

 Unzip or Put all the files into a folder named ioriX and insert this ioriX folder 
 into the chars folder of your M.U.G.E.N. You can add ioriX to your Select Screen by simply 
 adding the line "iorix" to your "select.cfg" under the [Characters] section.

 ----------------------------------------------------------------------------------------------

 *** SPECIAL SYSTEMS ***

   * COUNTER HIT  - Allows for another free hit. This is most obvious when using knockdown 
                    attacks. Some moves are not affected by counter hit (ex. Sweep). Use it
                    to your advantage.

   * GUARD CRUSH  - IoriX can be Guard Crushed. So don't block too much :P. My Guard Crush 
                    System is not KOF accurate since it is still not built into the M.U.G.E.N.
                    engine itself. This is just a "work around". It works much like SFA3. 
                    You can see the guard crush points in debug display.

   * DIZZY        - IoriX Can be dizzied. Again this is not KOF accurate. You can also check
                    the dizzy points in Debug Display.                     

   * THROW CANCEL - Tired of being thrown around? You cancel IoriX's BASIC throws by pressing                      
                    any punch button during the first few frames of his throw, KOF98 style. 

   * WIRE DAMAGE  - Some of IoriX's attacks have wire damage capabilities. This will cause the
                    enemy to bounce off a wall, which allows for further juggling :). 
                    -KOF2001 STYLE-

 ----------------------------------------------------------------------------------------------

  *** M.U.G.E.N. JOYSTICK CONFIGURATION ***

 (Player 1)

 *- DIRECTION KEYS

		     (U)           U = up        DF = downforward
    
 		 (B)  x  (F)       B = back      DB = downback
  
  		     (D)           F = Forward   UF = upforward

		                   D = down      UB = upback

 *- BUTTONS

		 (x) (y) (z)       x = light punch    y = hard punch   z = No Use 
                   
		 (a) (b) (c)       a = light kick     b = hard kick    c = No Use

		     (s)                              s = start

 --------------------------------------------------------------------------------------------
 *** ARTIFICIAL INTELLIGENCE SYSTEM ***
 
 IoriX has a 3 level AI. All you have to do is edit iorix.def using notepad.

 ;cmd   = iori.cmd           ;Hard Ai
 ;cmd   = iorimedai.cmd      ;Medium level Ai    
 cmd    = iorinoai.cmd       ;Low level Ai
 
 Just remove the semicolon AT THE START OF THE LINE before the ai level of your choice and make   
 sure the unwanted levels have semicolon before them. In the example above, it is setup to use    
 low level AI.

 --------------------------------------------------------------------------------------------

 --------------------------------------------------------------------------------------------

 *** DM/SDM SHORTCUTS ***
 
 -* I used the idle buttons (z,c) as DM shortcuts. YOU CAN REMOVE THESE SHORTCUTS!!!
    You'll just have to delete the shortcut cmd portion in the .cmd file you are using.
    You can also set it to "roll" for dodge.

 --------------------------------------------------------------------------------------------
 *** MOVELIST AND PROFILE ***

 Taken from: "THE KING OF FIGHTERS 2001 FAQ v0.2" by Orochi Yamazaki
 _________________________________________________________________________

 IORI YAGAMI 
 _________________________________________________________________________

 Looks like: A man with red hair dressed in a black jacket and a white
             collared shirt with red pants.

 =PROFILE=

 Fighting Style:        Ancient Yagami Style Martial Arts
 Birthday:              June 25th 1975
 Age:                   26
 Nationality:           Japan
 Blood Type:            O
 Height:                183cm
 Weight:                76kg
 Hobby:                 His band
 Favorite Food:         Meat
 Best Sport:            Any
 Most Important:        His girlfriend
 Dislikes:              Violence


 Critical Wire Attack : Unknown
 Counter Wire Attack  : Unknown
 Super Cancel Move(s) : Yamibarai
                        Oniyaki
                        Aoi Hana



 ==============================COMMAND LIST================================

 Name:        Sakahagi
 Movement:    When in close, b / f + C
 Description: Iori claws his opponent in the mid section.
 Comment:     n/a

 Name:        Saka Sakahagi
 Movement:    When in close, b / f + D
 Description: Iori slides behind his opponent and claws them in the
              back.
 Comment:     Switches sides.

 Name:        Ge Shiki: Yumebiki
 Movement:    f + A,A
 Description: Iori claw swipes from side to side.
 Comment:     Cancelable on either hit.

 Name:        Ge Shiki: Goufu In "Shinigame"
 Movement:    f + B
 Description: Iori performs an axe kick.
 Comment:     Cancelable on either hit.

 Name:        Ge Shiki: Yuri Ori
 Movement:    in air, b + B
 Description: Iori extends his leg behind him.
 Comment:     If used correctly, this move should cross-up the opponent.

 ===============================MOVES LIST=================================

 Name:        108 Shiki: Yami Barai
 Movement:    qcf + P
 Description: Iori motions in front of him as a purple fireball
              strolls forward.
 Comment:     A version makes the projectile slower.

 Name:        100 Shiki: Oniyaki
 Movement:    f,d,df + P
 Description: Iori leaps upwards, performing a two handed uppercut,
              surrounded in flames.
 Comment:     n/a

 Name:        127 Shiki: Aoi Hana
 Movement:    qcb + P, qcb + P, qcb + P
 Description: Iori slides forward with two standing uppercuts then
              leaps forward with a diving double handed smash.
 Comment:     Second hit is supercancelable and cancelable.

 Name:        212 Shiki: Kototsuki In
 Movement:    hcb + K
 Description: Iori runs forward. If it connects, he elbows his opponent
              and slams them into the ground whilst setting them ablaze.
 Comment:     n/a

 Name:        Kuzukaze
 Movement:    close, hcb, f + P
 Description: Iori grabs his opponent and swings them over to the other
              side.
 Comment:     The opponent is momentarily stunned after this move. This
              move also switches sides.

 Name:        ........
 Movement:    f,d,df + K
 Description: Iori leaps and then lands a flaming whack.
 Comment:     Can cancel into Aoi Hana.

 ============================DESPERATIONS LIST=============================

 Name:        Kin 1211 Shiki: Ya Otome
 Movement:    qcf, hcb + P
 Description: Iori powers up and slide forward. If it connects, he claws
              at his opponent then sets off an explosion of purple mist.
 Comment:     Can cancel into Yami Sugi.


 =========================SUPER DESPERATIONS LIST==========================

 Name:        Ura 327 Shiki: Yami Sugi
 Movement:    after Ya Otome, qcf, qcf, qcf, qcf + AC
 Description: Iori slashes twice, creating two purple clouds, as the
              opponent rises into the air, Iori sets off a flame explosion
              from the ground.
 Comment:     Timing is crucial. Try to get it off immediately after the
              explosion.

 

 --------------------------------------------------------------------------------------------

 *** Disclaimer ***
 
 Mugen and all related stuff is free as far as I know so if you bought this....
 You've been spoofed!! All the files included in the zip file(s) are mine... 
 All the sprites and sounds are from SNK, I only ripped and programmed it for mugen..  
 I will not be held responsible for any damage these files can do to your computer 
 or to your life. These files are not considered roms, emulator, warez etc.
 You can modify this, BUT LET ME KNOW IF YOU ARE TO RELEASE IT PUBLICLY.
 If you think some of my codings, ideas, rips etc. helped you...
 Don't Forget to credit me :)

 --------------------------------------------------------------------------------------------

 *** CREDITS *** 

 SNK NEOGEO     - For making my all time favorite game, The King Of Fighters Series.

 ELECBYTE       - For making M.U.G.E.N... which made all this possible.

 NEORAGEX       - For the best Neogeo emulator :) 

 Ses'MCM        - For making mugen life a bit more bearable    

 Rag's MEE      - For making mugen life a lot more bearable.

 [E], sorrowedge, Yongming - For a lot of help while I was starting.

 Shin_Dio, Tenshin - For the KOF2K1 and CVS2 sound rips respectively.

 People at the Mugen Boards - For some help and a lot of reading fun :P

 People at #Mugen - For being fun, idle and of some help... XD

 People that helped me while I was starting - Thank you guys. 

 Zyke and Paula - For always being there :D

 SANDER71113    - For wasting his time in completing this project.    

 JESUS          - Whom everything is of and for...

 And to everyone who enjoys mugen....

 If you think you deserve to be acknowledged email me..
              

 ---------------------------------------------------------------------------------------------
 *** ABOUT ***
 
 For bugs and comments suggestions whatever email me at:
 
 EMAIL   :   sander71113@gmail.com

 WEB PAGE:   http://go.to/sander71113
             http://sander71113.mgbr.net
             http://www.angelfire.com/jazz/sander71113
                             
 TRY MY OTHER WORKS:
 --------------------------------------------------------------------------------------------- 
                             
===================================== END OF README.TXT ========================================= 

