/*==============================================================================
            Copyright (c) 2010-2011 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
==============================================================================*/

package com.qualcomm.QCARSamples.ImageTargets;

import android.content.Context;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.ToggleButton;

public class GUIManager {

    // Custom views
    private View overlayView;
    private ToggleButton pauseButton;
    private Button startButton;
    private Button deleteButton;
    private ToggleButton storeButton;
    
    // The main application context
    private Context applicationContext;
    
    // A Handler for working with the gui from other threads
    private Handler mainActivityHandler;
    
    // Flags for our Handler
    public static final int SHOW_DELETE_BUTTON = 0;
    public static final int HIDE_DELETE_BUTTON = 1;
    public static final int TOGGLE_PAUSE_BUTTON = 2;
    public static final int DISPLAY_INFO_TOAST = 3;
    public static final int SHOW_PAUSE_BUTTON = 4;
    public static final int HIDE_START_BUTTON = 5;
    public static final int TOGGLE_STORE_BUTTON = 6;
    public static final int SHOW_STORE_BUTTON = 7;
    public static final int HIDE_PAUSE_BUTTON = 8;
    public static final int HIDE_STORE_BUTTON = 9;
    // Native methods to handle button clicks
    public native void nativePause();
    public native void nativeStart();
    public native void nativeStore();
    public native void nativeLeave();
    public native void nativeUnpause();
    public native void nativeDelete();
    
    
    /** Initialize the GUIManager. */
    public GUIManager(Context context)
    {
        // Load our overlay view
        // This view will add content on top of the camera / opengl view
        overlayView = View.inflate(context, R.layout.interface_overlay, null);
        
        // Store the application context
        applicationContext = context;
        
        // Create a Handler from the current thread
        // This is the only thread that can make changes to the GUI,
        // so we require a handler for other threads to make changes
        mainActivityHandler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                switch (msg.what) {
                    case SHOW_DELETE_BUTTON:
                        if (deleteButton != null) {
                            deleteButton.setVisibility(View.VISIBLE);
                        }
                        break;
                    case HIDE_DELETE_BUTTON:
                        if (deleteButton != null) {
                            deleteButton.setVisibility(View.INVISIBLE);
                        }
                        break;
                    case TOGGLE_PAUSE_BUTTON:
                        if (pauseButton != null) {
                            pauseButton.setChecked(true);
                        }
                        break;
                    case DISPLAY_INFO_TOAST:
                        String text = (String) msg.obj;
                        int duration = Toast.LENGTH_LONG;
                        Toast toast = Toast.makeText(applicationContext, text, duration);
                        toast.show();
                        break;
                    case SHOW_PAUSE_BUTTON:
                        if (pauseButton != null) {
                            pauseButton.setVisibility(View.VISIBLE);
                        }
                        break;
                    case HIDE_START_BUTTON:
                        if (startButton != null) {
                            startButton.setVisibility(View.INVISIBLE);
                        }
                        break;
                    case TOGGLE_STORE_BUTTON:
                        if (storeButton != null) {
                            storeButton.setChecked(true);
                        }
                        break;
                    case SHOW_STORE_BUTTON:
                        if (storeButton != null) {
                            storeButton.setVisibility(View.VISIBLE);
                        }
                        break;
                    case HIDE_PAUSE_BUTTON:
                        if (pauseButton != null) {
                            pauseButton.setVisibility(View.INVISIBLE);
                        }
                        break;
                    case HIDE_STORE_BUTTON:
                        if (storeButton != null) {
                            storeButton.setVisibility(View.INVISIBLE);
                        }
                        break;
                }
            }
        };
    }
    
    
    /** Button clicks should call corresponding native functions. */
    public void initButtons()
    {
        if (overlayView == null)
            return;

        pauseButton = (ToggleButton) overlayView.findViewById(R.id.pause_button);
    	pauseButton.setVisibility(View.INVISIBLE);
        pauseButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (((ToggleButton) v).isChecked()) {
                    nativePause();
                } else {
                    nativeUnpause();
                }
            }
        });
        
        
        storeButton = (ToggleButton) overlayView.findViewById(R.id.store_button);
    	storeButton.setVisibility(View.INVISIBLE);
        
    	storeButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                if (((ToggleButton) v).isChecked()) {
                    nativeStore();
                } else {
                    nativeLeave();
                }
            }
        });
        
        startButton = (Button) overlayView.findViewById(R.id.start_button);
    	startButton.setVisibility(View.VISIBLE);
        startButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
            	nativeStart();
            }
        });
        
        deleteButton = (Button) overlayView.findViewById(R.id.delete_button);
        deleteButton.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                nativeDelete();
            }
        });
    }
    
    
    /** Clear the button listeners. */
    public void deinitButtons()
    {
        if (overlayView == null)
            return;
        
        pauseButton.setOnClickListener(null);
        startButton.setOnClickListener(null);
        deleteButton.setOnClickListener(null);
        storeButton.setOnClickListener(null);
        
        pauseButton = null;
        startButton = null;
        deleteButton = null;
        storeButton = null;
    }
    
    
    /** Send a message to our gui thread handler. */
    public void sendThreadSafeGUIMessage(Message message)
    {
        mainActivityHandler.sendMessage(message);
    }
    
    
    /** Getter for the overlay view. */
    public View getOverlayView()
    {
        return overlayView;
    }
}
