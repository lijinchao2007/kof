================
 SFEditor v0.5b
================


==================
 WHAT'S SFEditor?
==================
	SFE Editor.

====================
 AND... WHAT'S SFE?
====================
	Simple Fighting Engine. Just an engine like MUGEN, but much more easy for
developers. This also means more limited, of course.
	You'll be able to make chars in a very easy way, making all from menus.

	I stop here. More imformation when SFE and SFEditor are more completed.
This is only a preview, you can modify the char from "Fist PC" and check it. If
you want more information about it ask me by mail or wait next release of the
"real" SFE+SFEditor.


======================
 HOW TO USE SFEditor?
======================
	First you'll need SPRITES, ANIMATIONS and SOUNDS (optional), and you can
import them from MUGEN (SFF & AIR) or make them.
	Go to AIR tab and press the SFEditor button.
	You'll see "Animation" and "Frame". You can change their options from here.

	* Animation: Only two options from now.
		- Initial state: State from animation can start.
		- Move: Move for execute this animation. A combination of the directions
		  (U,D,L,R) and buttons (only A for now). You can't make moves like
		  "dragon punch" or so, wait next versions.
	* Frame: Options for each frame.
		- State: State to change in this frame.
		- Control: Player has control in this frame.
		- Play sound: Sound to play in this frame.
		/ ON HIT /
			- Type: Type of hit. Used for falling down animations (and guarding).
			- Sound: Sound to play if hit the opponent.
		- Flags: Miscelaneous flags. Only for programmers... for now.

====================
 ID's OF ANIMATIONS
====================
	I need make more, but I only need these for "Fist PC".

	STAND			0

	WALK FORWARD	1
	WALK BACK		2
	STARTING		3

	CROUCH			11

	JUMP UP			20
	JUMP RIGTH		21
	JUMP LEFT		22

	GUARD HIGH		30
	GUARD MEDIUM	31

	FALLING FROM HIGH HIT		100
	FALLING FROM MEDIUM HIT		101
	FALLING LOW HIGH HIT		100
	FALLING FROM GROUND HIT		103

	FALLING FROM HIGH HIT (BACK)	104
	FALLING FROM MEDIUM HIT	(BACK)	104
	FALLING FROM LOW HIT (BACK)		104
	FALLING FROM GROUND HIT (BACK)	104



=========
 CONTACT
=========

http://ses.mgbr.net
ses@mgbr.net
