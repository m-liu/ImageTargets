/*==============================================================================
            Copyright (c) 2010-2011 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
            
@file 
    ImageTargetsRenderer.java

@brief
    Sample for ImageTargets

==============================================================================*/


package com.qualcomm.QCARSamples.ImageTargets;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;
import android.os.Message;
import android.util.Log;

import com.qualcomm.QCAR.QCAR;
import com.qualcomm.QCARSamples.ImageTargets.GUIManager;


/** The renderer class for the ImageTargets sample. */
public class ImageTargetsRenderer implements GLSurfaceView.Renderer
{
	public SoundManager mSoundManager;
	
    public boolean mIsActive = false;
    private GUIManager mGUIManager;
    
    /** Native function for initializing the renderer. */
    public native void initRendering();
    
    public native void resetSoundFlag();
    public native int getSoundFlag(int type);
    public native int getCurrentLevel();
    
    public int EOLState = 0;
    public int currentLevel;
    public boolean playSoundEffects = true;
    
    /** Native function to update the renderer. */
    public native void updateRendering(int width, int height);

    /** Native function to store Java environment information for callbacks. */
    public native void initNativeCallback();

    
    /** Called when the surface is created or recreated. */
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {
        DebugLog.LOGD("GLRenderer::onSurfaceCreated");

        // Call native function to initialize rendering:
        initRendering();
        
        // Call QCAR function to (re)initialize rendering after first use
        // or after OpenGL ES context was lost (e.g. after onPause/onResume):
        QCAR.onSurfaceCreated();
        
        // Call native function to store information about the Java environment
        // It is important that we make this call from this thread (the rendering thread)
        // as the native code will want to make callbacks from this thread
        initNativeCallback();
    }
    
    
    /** Called when the surface changed size. */
    public void onSurfaceChanged(GL10 gl, int width, int height)
    {
        DebugLog.LOGD("GLRenderer::onSurfaceChanged");
        
        // Call native function to update rendering when render surface parameters have changed:
        updateRendering(width, height);

        // Call QCAR function to handle render surface size changes:
        QCAR.onSurfaceChanged(width, height);
    }    
    
    
    /** The native render function. */    
    public native void renderFrame();
    
    
    /** Called to draw the current frame. */
    public void onDrawFrame(GL10 gl)
    {
        if (!mIsActive)
            return;

        // Call our native function to render content
        //renderFrame();
        if (playSoundEffects) {
        	Log.e("TEST", "play");
        }
        else {
        	Log.e("TEST"," not play");
        	
        }
        
        
        if (getSoundFlag(0) == 1 && playSoundEffects){
        	Log.e("TEST", "getSoundFlag(0) == 1");
        	mSoundManager.playSound(0,1);
        }
        if (getSoundFlag(1) == 1 && playSoundEffects){
        	Log.e("TEST", "getSoundFlag(1) == 1");
        	mSoundManager.playSound(1,1);
        }
        if (getSoundFlag(2) == 1 && playSoundEffects){
        	Log.e("TEST", "getSoundFlag(2) == 1");
        	mSoundManager.playSound(2,1);
        }
        if (getSoundFlag(3) == 1){
        	Log.e("TEST", "getSoundFlag(3) == 1");
        	if (playSoundEffects){
        		mSoundManager.playSound(3,1);
        	}
        	currentLevel =  getCurrentLevel();
        	EOLState = 1;
        	
        	if (currentLevel == 11) {
        		EOLState = 2;
        		mGUIManager.newLevel("GAME OVER! Press End Game to continue!");
        		mGUIManager.newContinue("End Game");
            	}
        	
        	else if (currentLevel != 10) {
        	
    		mGUIManager.newLevel("End of Level "+currentLevel + "! Press Next Level to continue!");
    		mGUIManager.newContinue("Next Level");
        	}
        	else {
        		EOLState = 2;
        		mGUIManager.newLevel("End of Level "+currentLevel + " and you beat the game! Press End Game to continue!");
        		mGUIManager.newContinue("End Game");	
        	}
        		
    		hidePauseButton();
        	showUnpauseButton();

        }
        if (getSoundFlag(4) == 1 && playSoundEffects){ 
        	Log.e("TEST", "getSoundFlag(4) == 1");
        	mSoundManager.playSound(4,1);
        }
        
        resetSoundFlag();
        
        
        renderFrame();
    }
    
    /** Called from native to show the delete button. */
    public void showDeleteButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_DELETE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
        
    }
    
    /** Called from native to hide the delete button. */
    public void hideDeleteButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_DELETE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the pause button. */
    public void togglePauseButton()
    {
        Message message = new Message();
        message.what = GUIManager.TOGGLE_PAUSE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void showPauseButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_PAUSE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void hidePauseButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_PAUSE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void showUnpauseButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_UNPAUSE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void hideUnpauseButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_UNPAUSE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    
    /** Called from native to toggle the pause button. */
    public void toggleStoreButton()
    {
        Message message = new Message();
        message.what = GUIManager.TOGGLE_STORE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void showStoreButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_STORE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void hideStoreButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_STORE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void showUpgradeButton(String cost)
    {
    	mGUIManager.newCost("Upgrade Tower " + cost + " ZP");
        Message message = new Message();
        message.what = GUIManager.SHOW_UPGRADE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void hideUpgradeButton2(String cost)
    {
    	mGUIManager.newCost("Upgrade Tower " + cost + " ZP");
        Message message = new Message();
        message.what = GUIManager.HIDE_UPGRADE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void hideUpgradeButton()
    {
    	mGUIManager.newCost("Upgrade Tower");
        Message message = new Message();
        message.what = GUIManager.HIDE_UPGRADE_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void showStatsButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_STATS_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void hideStatsButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_STATS_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void showCreditsButton()
    {
        Message message = new Message();
        message.what = GUIManager.SHOW_CREDITS_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to toggle the start button. */
    public void hideCreditsButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_CREDITS_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }	
    
    /** Called from native to toggle the start button. */
    public void hideStartButton()
    {
        Message message = new Message();
        message.what = GUIManager.HIDE_START_BUTTON;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    /** Called from native to display a message. */
    public void displayMessage(String text)
    {
        Message message = new Message();
        message.what = GUIManager.DISPLAY_INFO_TOAST;
        message.obj = text;
        mGUIManager.sendThreadSafeGUIMessage(message);
    }
    
    public void displayScore(String score)
    {
        mGUIManager.newScore(score);
    }
    
    public void displayZen(String zen)
    {
    	mGUIManager.newZen(zen);
    }
    
    public void displayLives(String lives)
    {
        mGUIManager.newLives(lives);
    }
    
    /** Setter for the gui manager. */
    public void setGUIManager(GUIManager guiManager)
    {
        mGUIManager = guiManager;
    }
    
    /** Called from native to play a sound effect. */
    public void playSound(int soundIndex, float volume)
    {
        mSoundManager.playSound(soundIndex, volume);
    	//mSoundManager.setSoundFlag(soundIndex, volume);
    }
    public void setSoundManager(SoundManager soundManager)
    {
        mSoundManager = soundManager;
    }
    
    public void resetEOLState(){
    	EOLState = 0;
    }
    
}
