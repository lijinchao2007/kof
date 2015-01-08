package com.etron.kof;

import org.libsdl.app.SDLActivity; 

/* 
 * A sample wrapper class that just calls SDLActivity 
 */ 

public class KOF extends SDLActivity { 

    // Load the .so
    static {
        System.loadLibrary("SDL2_shared");
        System.loadLibrary("SDL2_image");
        System.loadLibrary("SDL2_mixer");
        //System.loadLibrary("SDL2_net");
        System.loadLibrary("SDL2_ttf");
        System.loadLibrary("kof_shared");
    }
    
}