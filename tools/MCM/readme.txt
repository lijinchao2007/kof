======================================
 MCM 2.0b dev3.56 (under development)
======================================


===========
 IMPORTANT
===========
	This is a "under development version" of M.C.M. 2.0 Final.
	It means BETA VERSION, ok?
    Because this:
        - Don't ask me how to use it, it is not finished yet."
        - Only report critical bugs, please.
        - Finally: Enjoy it and be patient, I hope finish it soon.

	This version is under development, so it may have some bugs. Take care.
Anyway, it should works better than MCM 1.5; I fixed a lot of bugs and add some
features.


============
 WHAT'S NEW
============

v2.0b dev3.54
--------------
* Added checkbox that shows/changes if the image uses the shared palette.

v2.0b dev3.50
--------------
* SND editor.
	- Load/Save SND's
	- Add/Change/Delete samples.
	- Save one or all samples to disk.

IMPORTANT: MCM lets you add (and play) OGG files, but these files
  DOESN'T WORK with MUGEN.

v2.0b dev2.98
-------------
* Added support for my file formats for SPRITES abd ANIMATIONS (used in "Fist PC").
* Now MCM "remember" last working directories.
* Changes in "mcm.ini":
	- RedrawAlways: Redraws contantly.
	- LastSFFDir, LastAIRDir, LastPCXDir, LastACTDir: ;)

v2.0b dev2.94
-------------
* GDI support. Use it if you have problems with DirectX (usually if MCM crashes
  when start or load a SFF). Just open MCM.INI and write: GDI=1
  But remember: DirectX is faster.

v2.0b dev2.93
-------------
* Onion skins: You can see the previous frames/sprites (up to three, but I
  think that one is enough).
* Fix one image: Fix/unfix any image (from SFF or AIR) and see it always. You
  can easily make your new Actions from the STAND position. Just fix that image.

v2.0b dev2.90
-------------
* Full AIR Editor!
* New commands in AIR tab:
	- Insert Action: Insert a new (blank) action.
	- Clone Action: Duplicates the current action.
	- Delete Action: Mmm... deletes the current action?

	- Insert Frame: Insert a new frame BEFORE the current one with the 
	  Group/Image from the Sprite selected in the SFF tab.
	- Add Frame: Same, but adding at the end of the action.
	- Change Frame: Chage the current frame with the Sprite from the SFF tab.
	- Delete Frame: Deletes the current frame.
	- Use previous Clsn's: Copy the Clsn's from the previous frame.
* New commands in the SFF tab:
	- Insert Frame, Add Frame, Change Frame: Equal to the command in the
	  AIR tab, but more usefull.

* NOTE: You can also change the frame from the Edit Boxes: 'Group' and 'Image'.

v2.0b dev2.73
-------------
* Yeah! Full Clsn's editing. There are three modes:
    - Hand: Move the frame.
    - Clsn1 button: Edit the Clsn1 boxes.
    - Clsn2 button: Edit the Clsn2 boxes.
  You can do some actions with the Clsn boxes:
    - Add: Just click and drag the mouse in the view window.
    - Delete: Select the Clsn (just put the mouse over a Clsn) and press SUPR.
    - Move: Click & drag an edge of the Clsn.
    - Resize: Click & drag a corner of the Clsn.

* Checkbox 'Loop' and EditBox 'LoopStart': If you know how the AIR files work you
  should know how use them.
* EditBox 'Flags': Write here all of the frame options that MCM does not
  support and you want to append to a frame.
* EditBox 'T': Frame time.

NOTE: YOU CANNOT ADD/DELETE ACTIONS/FRAMES AND YOU CANNOT CHANGE THE
      GROUP/IMAGE OF ANY FRAME. This will be in next release, sorry.

* Save palette option. Damn! I really forgot it ^_^.
* New version system. No more: "What's the latest version?".



============
 BUGS FIXED
============

v2.0b dev3.56
--------------
* Fixed another buf with SFF. Err... thanks, Ferenator (I hate you, did you know it?).

v2.0b dev3.55
--------------
* Fixed an error when loading some SFF. Thanks, Ferenator (We'll speak about those 10000).

v2.0b dev3.54
--------------
* Minor bug fixes with SND.

v2.0b dev3.53
--------------
* You lose clsn's when inserting a frame (not adding) and the program crashed :(
* MCM doesn't block your sound card, you can ear music again while MCM is opened.
  And, if it crashed because the sound, it must works now.

v2.0b dev3.52
--------------
* Error when loading some AIR files. Thanks to MUGREN.

v2.0b dev3.51
--------------
* Error when deleting some sprites from a SFF.

v2.0b dev3.50
--------------
* Something... I suppose.

v2.0b dev2.981
--------------
* Fixed a bug when two images was identical, but with different pallete; MCM
  deleted one of them. Fixed, thanks to "Kitsune Sniper".

v2.0b dev2.98
-------------
* Error when you click the checkboxes "Inv H" or "Inv V" if you don't have any
  animation loaded.

v2.0b dev2.95
-------------
* Fixed an error when adding new sprites.

v2.0b dev2.94
-------------
* 'Fix image' now with more bright.

v2.0b dev2.93
-------------
* The "lost sprites" bug REALLY fixed. It has a mistake in one line of code.
  Thanks again, DCelso.

v2.0b dev2.90
-------------
* Minor bugs fixed.

v2.0b dev2.73
-------------
* The "lost sprites" bug. At least I fixed the one I found. Thanks DCelso.



=========
 CONTACT
=========

http://ses.mgbr.net
ses@mgbr.net

http://perso.wanadoo.es/sesses
sesweb@wanadoo.es

