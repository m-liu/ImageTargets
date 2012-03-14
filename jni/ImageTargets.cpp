/*==============================================================================
            Copyright (c) 2010-2011 RICKROLLD
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
            
@file 
    ImageTargets.cpp

@brief
    Werk Werk Werk

==============================================================================*/

#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

#ifdef USE_OPENGL_ES_1_1
#include <GLES/gl.h>
#include <GLES/glext.h>
#else
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

#include <QCAR/QCAR.h>
#include <QCAR/CameraDevice.h>
#include <QCAR/Renderer.h>
#include <QCAR/VideoBackgroundConfig.h>
#include <QCAR/Trackable.h>
#include <QCAR/Tool.h>
#include <QCAR/Tracker.h>
#include <QCAR/CameraCalibration.h>
#include <QCAR/Marker.h>

#include "Texture.h"
#include "CubeShaders.h"
#include "graphics_arrays.h"

#include "SampleUtils.h"
#include "LevelSystem.h"
#include "UnitMethods.h"
#include "GlobalDefs.h"
#include "SampleMath.h"


// Textures:
int textureCount                = 0;
Texture** textures              = 0;

//Global units and unit types
EnemyUnit enemy[MAX_NUM_ENEMIES];
EnemyUnit enemy_type[NUM_ENEMY_TYPES];
MissileUnit missile[MAX_NUM_TOWERS];
MissileUnit missile_type[NUM_MISSILE_TYPES];
TowerUnit tower[MAX_NUM_TOWERS];
TowerUnit tower_type[NUM_TOWER_TYPES];

//java objects
JNIEnv* javaEnv;
jobject javaObj;
jclass javaClass;

JNIEnv* javaEnv2;
jobject javaObj2;
jclass javaClass2;

//Global Level struct
Level level[NUM_LEVELS];
int currentLevel = 0;
int currentLives = 20;

int currentScore = 0;
int currentZen = 5;

int stageType = 1;

bool displayedMessage = false;

//board properties
#define MARKER_SIZE 50
#define BOARD_SIZE 8  //8x8 markers

static int startGame = 0;
static int seeTargets = 0;
static int pauseGame = 0;

//screen tap globals
bool tap=false;
float tapX = 0;
float tapY = 0;
bool tap_in_target = true;
int selMarkerID = -1;


// OpenGL ES 2.0 specific:
#ifdef USE_OPENGL_ES_2_0
unsigned int shaderProgramID    = 0;
GLint vertexHandle              = 0;
GLint normalHandle              = 0;
GLint textureCoordHandle        = 0;
GLint mvpMatrixHandle           = 0;
#endif

// Screen dimensions:
unsigned int screenWidth        = 0;
unsigned int screenHeight       = 0;

static int missileFrameCounter = 1;
static int enemyFrameCounter = 1;
static double counterprevTime;


// Indicates whether screen is in portrait (true) or landscape (false) mode
bool isActivityInPortraitMode   = false;

// The projection matrix used for rendering virtual objects:
QCAR::Matrix44F projectionMatrix;

//the inverse projection matrix for converting screen to world coordinates
QCAR::Matrix44F inverseProjMatrix;

void DrawEnemy (QCAR::Matrix44F EnemyMatrix, QCAR::Matrix44F EnemyProjection, int type);
void DrawTower (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int type);
void DrawMissile (QCAR::Matrix44F MissileMatrix, QCAR::Matrix44F MissileProjection, int type);
void DrawSelRing (QCAR::Matrix44F selMatrix, QCAR::Matrix44F selProjection);


void getMarkerOffset(int trackedCornerID, int &x_offset, int &y_offset);
void convert2BoardCoord (int cornerID, QCAR::Matrix44F cornerMVM, QCAR::Matrix44F targetMVM, float &x, float &y);

//for tap event computations

bool checkTapMarker (const QCAR::Marker* marker, QCAR::Matrix44F markerMVM);
bool
linePlaneIntersection(QCAR::Vec3F lineStart, QCAR::Vec3F lineEnd,
                      QCAR::Vec3F pointOnPlane, QCAR::Vec3F planeNormal,
                      QCAR::Vec3F &intersection);
void
projectScreenPointToPlane(QCAR::Vec2F point, QCAR::Vec3F planeCenter, QCAR::Vec3F planeNormal,
                          QCAR::Vec3F &intersection, QCAR::Vec3F &lineStart, QCAR::Vec3F &lineEnd,
                          QCAR::Matrix44F modelViewMatrix);


//*****************************************************************
// Button native functions
// ****************************************************************
void
togglePauseButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that toggles the store button
    jmethodID method = javaEnv->GetMethodID(javaClass, "togglePauseButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
toggleStoreButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that toggles the pause button
    jmethodID method = javaEnv->GetMethodID(javaClass, "toggleStoreButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
showDeleteButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that shows the delete button
    jmethodID method = javaEnv->GetMethodID(javaClass, "showDeleteButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}


void
hideDeleteButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the delete button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideDeleteButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
showPauseButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that shows the pause button
    jmethodID method = javaEnv->GetMethodID(javaClass, "showPauseButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
hidePauseButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the start button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hidePauseButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
showStoreButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that shows the store button
    jmethodID method = javaEnv->GetMethodID(javaClass, "showStoreButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
hideStoreButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the start button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideStoreButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}


void
showUpgradeButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that shows the delete button
    jmethodID method = javaEnv->GetMethodID(javaClass, "showUpgradeButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}


void
hideUpgradeButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the delete button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideUpgradeButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}


void
showStatsButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that shows the stats button
    jmethodID method = javaEnv->GetMethodID(javaClass, "showStatsButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}


void
hideStatsButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the delete button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideStatsButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
showCreditsButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that shows the stats button
    jmethodID method = javaEnv->GetMethodID(javaClass, "showCreditsButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}


void
hideCreditsButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the delete button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideCreditsButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

void
hideStartButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the start button
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideStartButton", "()V");
    javaEnv->CallVoidMethod(javaObj, method);
}

#ifdef __cplusplus
extern "C"
{
#endif

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeNext(JNIEnv*, jobject)
{
	startLevel(currentLevel);
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativePause(JNIEnv*, jobject)
{
			hideStoreButton();
			pauseGame = 1;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeUnpause(JNIEnv*, jobject)
{
			for (int i=0; i<MAX_NUM_ENEMIES; i++){
				enemy[i].prevTime = getCurrentTime();  
            }
			showStoreButton();
			pauseGame = 0;

}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeStore(JNIEnv*, jobject)
{
			hidePauseButton();
			hideStatsButton();
			pauseGame = 1;
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeStats(JNIEnv*, jobject)
{
			displayMessage("Stats!");
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeUpgrade(JNIEnv*, jobject)
{
			displayMessage("Upgrade!");
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeLeave(JNIEnv*, jobject)
{
			//update times
			for (int i=0; i<MAX_NUM_ENEMIES; i++){
				enemy[i].prevTime = getCurrentTime();  
            }
			showPauseButton();
			showStatsButton();
			pauseGame = 0;

}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeStart(JNIEnv*, jobject)
{
			if (seeTargets == 1)
			{
				startGame = 1;
				hideStartButton();
				hideCreditsButton();
				showPauseButton();
				showStatsButton();
				hideStoreButton();
				startLevel(0);
				for (int enemyNumber = 0; enemyNumber < MAX_NUM_ENEMIES; enemyNumber++) {
					enemy[enemyNumber].prevTime = getCurrentTime();
				}	
			}
			else
			{
				displayMessage("Find the targets first!");
			}
			
}
JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeDelete(JNIEnv*, jobject)
{
 			displayMessage("D4");
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeCredits(JNIEnv*, jobject)
{
 			displayMessage("Credits!\n\n\nTeamRickroll'd\nMing Liu\n David Chou\n  Alton Chiu\n\n\nProfessor Enright Jerger\n\nECE496 2011-2012");
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeBuy(JNIEnv *env, jobject thiz, jint cost)//type?
{
    //a purchase was made. Initialize the tower and deduct the cost
    LOG("nativeBuy called");
    //FIXME tower type is cost-1
    int towerType = (int)cost -1;
    
    //check that we have a selection
    if (selMarkerID < 0){
        LOG("ERROR nativeBuy: selMarkerID < 0");
        return;
    }
    
    LOG("nativeBuy: selMarkerID=%d", selMarkerID);
    //initialize the tower
	makeTower(towerType, selMarkerID);

    //deduct cost
	currentZen = currentZen - (int)cost;
	char zenString[20];
	sprintf (zenString, "%d", currentZen);
	displayZen(zenString);
}


//********************************************************
// Tap event handler (tower selection)
// *******************************************************
JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeTapEvent(JNIEnv* , jobject, jfloat x, jfloat y)
{
    tapX = x;
    tapY = y;
    tap = true;
}

//********************************************************
// QCAR Native calls
// *******************************************************

JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_getOpenGlEsVersionNative(JNIEnv *, jobject)
{
#ifdef USE_OPENGL_ES_1_1        
    return 1;
#else
    return 2;
#endif
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_setActivityPortraitMode(JNIEnv *, jobject, jboolean isPortrait)
{
    isActivityInPortraitMode = isPortrait;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_onQCARInitializedNative(JNIEnv *, jobject)
{

    QCAR::setHint(QCAR::HINT_MAX_SIMULTANEOUS_IMAGE_TARGETS, 100);
    QCAR::setHint(QCAR::HINT_IMAGE_TARGET_MULTI_FRAME_ENABLED, 1);
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_initNativeCallback(JNIEnv* env, jobject obj)
{
    // Store the java environment for later use
    // Note that this environment is only safe for use in this thread
    javaEnv = env;
    
    // Store the calling object for later use
    // Make a global reference to keep it valid beyond the scope of this function
    javaObj = env->NewGlobalRef(obj);
    
    // Store the class of the calling object for later use
    jclass objClass = env->GetObjectClass(obj);
    javaClass = (jclass) env->NewGlobalRef(objClass);
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_initNativeCallback(JNIEnv* env, jobject obj)
{
    // Store the java environment for later use
    // Note that this environment is only safe for use in this thread
    javaEnv2 = env;
    
    // Store the calling object for later use
    // Make a global reference to keep it valid beyond the scope of this function
    javaObj2 = env->NewGlobalRef(obj);
    
    // Store the class of the calling object for later use
    jclass objClass2 = env->GetObjectClass(obj);
    javaClass2 = (jclass) env->NewGlobalRef(objClass2);
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_renderFrame(JNIEnv *, jobject)
{
    //LOG("Java_com_qualcomm_QCARSamples_ImageTargets_GLRenderer_renderFrame");

    // Clear color and depth buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render video background:
    QCAR::State state = QCAR::Renderer::getInstance().begin();
		
#ifdef USE_OPENGL_ES_1_1
    // Set GL11 flags:
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
        
#endif

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
	
	
    //helper vars
    int x_offset;
    int y_offset;
    int trackedCornerID=-1; //the corner marker # used to render enemies
    QCAR::Matrix44F cornerMarkerModelViewMatrix; //save the corner marker MVM

    // Did we find any trackables this frame?
    for(int tIdx = 0; tIdx < state.getNumActiveTrackables(); tIdx++)
    {
        //LOG("num tracked: %d", state.getNumActiveTrackables());
        // Get the trackable
        const QCAR::Trackable* trackable = state.getActiveTrackable(tIdx);

        // Check the type of the trackable:
        assert(trackable->getType() == QCAR::Trackable::MARKER);
        const QCAR::Marker* marker = static_cast<const QCAR::Marker*>(trackable);

        //if a corner marker is seen, render the enemies relative to that marker
        if (trackedCornerID<0 && marker->getMarkerId()<4 ){
            //get the modelview matrix of the corner marker
            cornerMarkerModelViewMatrix = QCAR::Tool::convertPose2GLMatrix(trackable->getPose());
            trackedCornerID=marker->getMarkerId();

            getMarkerOffset(trackedCornerID, x_offset, y_offset);


            if (startGame == 1 && pauseGame == 0) {
                //animate and draw the enemy units in reference to the marker position
                for (int i=0; i<MAX_NUM_ENEMIES; i++){
                    QCAR::Matrix44F enemyMatrix = cornerMarkerModelViewMatrix;        
                    animateEnemy(enemyMatrix, i, x_offset, y_offset); //animate the i-th enemy
                    QCAR::Matrix44F enemyProjection;
                    DrawEnemy(enemyMatrix, enemyProjection,enemy[i].texture);
					
					//char scoreString[20];
					//sprintf (scoreString, "%d", enemy[i].texture);
					//displayMessage(scoreString);
                }
            }




        } //end enemy rendering
        
        //render towers and missiles
        //Note: do not draw the towers if a corner marker is not seen
        else if (trackedCornerID>=0 && marker->getMarkerId() >= 4 && marker->getMarkerId() < 4+MAX_NUM_TOWERS) {

            //get the marker id
            int mID = (marker->getMarkerId()) - 4;
            QCAR::Matrix44F towerMatrix = QCAR::Tool::convertPose2GLMatrix(trackable->getPose());
            QCAR::Matrix44F towerProjection;
 
 
            //if marker is tapped, show store and upgrade buttons
            if ( checkTapMarker(marker, towerMatrix) ){
                showStoreButton();
                showUpgradeButton();
                selMarkerID = mID;
                //tower[mID].initialized=1;
                //tower[mID].type=0;
                //end remove
            }


            //draw the tower at the precise location of the marker if it's initialized
            if (tower[mID].initialized){
                animateTower(towerMatrix, mID);
                DrawTower(towerMatrix, towerProjection, tower[mID].texture); 

                //render the missile relative to the corner marker
                //1) find x, y board coordinates of the tower marker
                convert2BoardCoord (trackedCornerID, cornerMarkerModelViewMatrix, towerMatrix, tower[mID].boardX, tower[mID].boardY);

                //initialize the missile if not init
                if (!missile[mID].initialized){
                    makeMissile (tower[mID].type, mID, tower[mID].boardX, tower[mID].boardY);
                }
                //always update the original missile position (in case of glitches)
                updateMissileDefaultPos (mID, tower[mID].boardX, tower[mID].boardY);

                //animate missile with respect to corner marker
                QCAR::Matrix44F missileMatrix = cornerMarkerModelViewMatrix;    
                getMarkerOffset(trackedCornerID, x_offset, y_offset);
                if (startGame == 1 && pauseGame == 0) {
                    animateMissile(missileMatrix, mID, x_offset, y_offset);
                    checkMissileContact(mID);
                }
#ifdef USE_OPENGL_ES_1_1
#else
                QCAR::Matrix44F missileProjection;
				//TODO: should technically use the texture from the missile database
                DrawMissile(missileMatrix, missileProjection, missile[mID].texture); 
#endif

            }

            else { //if tower is uninitialized, display a ring to indicate marker is recognized
                //TODO
                DrawSelRing(towerMatrix, towerProjection); 
            }

        }//end tower drawing

        // If this is our first time seeing the target, display a tip
        if (!displayedMessage) {
			
			char levelString[20];
			sprintf (levelString, "%d", currentLevel);
			//TODO: Uncomment this to test menu
			//updateApplicationStatusEOL(levelString);
			displayMessage("Press Start!");
			seeTargets = 1;
			counterprevTime = getCurrentTime();
			//TODO: move this at some point			
            displayedMessage = true;
        }

    }

    //re-render every frame
    trackedCornerID=-1;
    //if tap outside markers, unselect tower
    if (tap) { 
        hideStoreButton();
        hideUpgradeButton();
        selMarkerID = -1;
    }
    //reset tap
    tap = false;

    glDisable(GL_DEPTH_TEST);

#ifdef USE_OPENGL_ES_1_1        
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
    glDisableVertexAttribArray(vertexHandle);
    glDisableVertexAttribArray(normalHandle);
    glDisableVertexAttribArray(textureCoordHandle);
#endif

    QCAR::Renderer::getInstance().end();
	

    //FIXME: using 24 fps for enemies too. Adjust for speed?
	//counter++;
	double time4 = getCurrentTime();  
	float dt4 = (float)(time4-counterprevTime);          // from frame to frame
	counterprevTime = time4;
	missileFrameCounter = ((int)floor(missileFrameCounter - 1 + dt4*25.0f) % MISSILE_NUM_FRAMES) + 1;
	enemyFrameCounter = ((int)floor(enemyFrameCounter - 1 + dt4*50.0f) % ENEMY_NUM_FRAMES) + 1;
	
	/* 
	if (missileFrameCounter == 5) {
	currentScore = currentScore + 1;
	currentZen = currentZen + 1;
	char scoreString[20];
	sprintf (scoreString, "%d", currentScore);
	displayScore(scoreString);
	char zenString[20];
	sprintf (zenString, "%d", currentZen);
	displayZen(zenString);
	}
	*/
}



void
configureVideoBackground()
{
    // Get the default video mode:
    QCAR::CameraDevice& cameraDevice = QCAR::CameraDevice::getInstance();
    QCAR::VideoMode videoMode = cameraDevice.
                                getVideoMode(QCAR::CameraDevice::MODE_DEFAULT);


    // Configure the video background
    QCAR::VideoBackgroundConfig config;
    config.mEnabled = true;
    config.mSynchronous = true;
    config.mPosition.data[0] = 0.0f;
    config.mPosition.data[1] = 0.0f;
    
    if (isActivityInPortraitMode)
    {
        //LOG("configureVideoBackground PORTRAIT");
        config.mSize.data[0] = videoMode.mHeight
                                * (screenHeight / (float)videoMode.mWidth);
        config.mSize.data[1] = screenHeight;
    }
    else
    {
        //LOG("configureVideoBackground LANDSCAPE");
        config.mSize.data[0] = screenWidth;
        config.mSize.data[1] = videoMode.mHeight
                            * (screenWidth / (float)videoMode.mWidth);
    }

    // Set the config:
    QCAR::Renderer::getInstance().setVideoBackgroundConfig(config);
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_initApplicationNative(
                            JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_initApplicationNative");
    
    // Store screen dimensions
    screenWidth = width;
    screenHeight = height;
        
    // Handle to the activity class:
    jclass activityClass = env->GetObjectClass(obj);

    jmethodID getTextureCountMethodID = env->GetMethodID(activityClass,
                                                    "getTextureCount", "()I");
    if (getTextureCountMethodID == 0)
    {
        LOG("Function getTextureCount() not found.");
        return;
    }

    textureCount = env->CallIntMethod(obj, getTextureCountMethodID);    
    if (!textureCount)
    {
        LOG("getTextureCount() returned zero.");
        return;
    }

    textures = new Texture*[textureCount];

    jmethodID getTextureMethodID = env->GetMethodID(activityClass,
        "getTexture", "(I)Lcom/qualcomm/QCARSamples/ImageTargets/Texture;");

    if (getTextureMethodID == 0)
    {
        LOG("Function getTexture() not found.");
        return;
    }

    // Register the textures
    for (int i = 0; i < textureCount; ++i)
    {

        jobject textureObject = env->CallObjectMethod(obj, getTextureMethodID, i); 
        if (textureObject == NULL)
        {
            LOG("GetTexture() returned zero pointer");
            return;
        }

        textures[i] = Texture::create(env, textureObject);
    }
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_deinitApplicationNative(
                                                        JNIEnv* env, jobject obj)
{
    LOG("Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_deinitApplicationNative");

    // Release texture resources
    if (textures != 0)
    {    
        for (int i = 0; i < textureCount; ++i)
        {
            delete textures[i];
            textures[i] = NULL;
        }
    
        delete[]textures;
        textures = NULL;
        
        textureCount = 0;
    }
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_startCamera(JNIEnv *,
                                                                         jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_startCamera");


		
    // Initialize the camera:
    if (!QCAR::CameraDevice::getInstance().init())
        return;

    // Configure the video background
    configureVideoBackground();

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(
                                QCAR::CameraDevice::MODE_DEFAULT))
        return;

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start())
        return;

    // Uncomment to enable flash
    //if(QCAR::CameraDevice::getInstance().setFlashTorchMode(true))
    //	LOG("IMAGE TARGETS : enabled torch");

    // Uncomment to enable infinity focus mode, or any other supported focus mode
    // See CameraDevice.h for supported focus modes
    //if(QCAR::CameraDevice::getInstance().setFocusMode(QCAR::CameraDevice::FOCUS_MODE_INFINITY))
    //	LOG("IMAGE TARGETS : enabled infinity focus");

    // Start the tracker:
    QCAR::Tracker::getInstance().start();
 
    // Cache the projection matrix:
    const QCAR::Tracker& tracker = QCAR::Tracker::getInstance();
    const QCAR::CameraCalibration& cameraCalibration =
                                    tracker.getCameraCalibration();
    projectionMatrix = QCAR::Tool::getProjectionGL(cameraCalibration, 2.0f,
                                            2000.0f);

    // Cache the inverse projection matrix:
    inverseProjMatrix = SampleMath::Matrix44FInverse(projectionMatrix);

}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_stopCamera(JNIEnv *,
                                                                   jobject)
{
    LOG("Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_stopCamera");

    QCAR::Tracker::getInstance().stop();

    QCAR::CameraDevice::getInstance().stop();
    QCAR::CameraDevice::getInstance().deinit();
}

JNIEXPORT jboolean JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_toggleFlash(JNIEnv*, jobject, jboolean flash)
{
    return QCAR::CameraDevice::getInstance().setFlashTorchMode((flash==JNI_TRUE)) ? JNI_TRUE : JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_autofocus(JNIEnv*, jobject)
{
    return QCAR::CameraDevice::getInstance().startAutoFocus()?JNI_TRUE:JNI_FALSE;
}

JNIEXPORT jboolean JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_setFocusMode(JNIEnv*, jobject, jint mode)
{
    return QCAR::CameraDevice::getInstance().setFocusMode(mode)?JNI_TRUE:JNI_FALSE;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_initRendering(
                                                    JNIEnv* env, jobject obj)
{
    LOG("Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_initRendering");

    // Define clear color
    glClearColor(0.0f, 0.0f, 0.0f, QCAR::requiresAlpha() ? 0.0f : 1.0f);
    
    // Now generate the OpenGL texture objects and add settings
    for (int i = 0; i < textureCount; ++i)
    {
        glGenTextures(1, &(textures[i]->mTextureID));
        glBindTexture(GL_TEXTURE_2D, textures[i]->mTextureID);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textures[i]->mWidth,
                textures[i]->mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                (GLvoid*)  textures[i]->mData);
    }
#ifndef USE_OPENGL_ES_1_1
  
    shaderProgramID     = SampleUtils::createProgramFromBuffer(cubeMeshVertexShader,
                                                            cubeFragmentShader);

    vertexHandle        = glGetAttribLocation(shaderProgramID,
                                                "vertexPosition");
    normalHandle        = glGetAttribLocation(shaderProgramID,
                                                "vertexNormal");
    textureCoordHandle  = glGetAttribLocation(shaderProgramID,
                                                "vertexTexCoord");
    mvpMatrixHandle     = glGetUniformLocation(shaderProgramID,
                                                "modelViewProjectionMatrix");

#endif

    //Game specific initialization
    //initialize unit database
    initUnitDB ();
    initLevels();

}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_updateRendering(
                        JNIEnv* env, jobject obj, jint width, jint height)
{
    LOG("Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_updateRendering");
    
    // Update screen dimensions
    screenWidth = width;
    screenHeight = height;

    // Reconfigure the video background
    configureVideoBackground();
}

#ifdef __cplusplus
}
#endif




void DrawEnemy (QCAR::Matrix44F EnemyMatrix, QCAR::Matrix44F EnemyProjection, int type) {
	//Horse = 1, Zombie = 5
	struct graphics_arrays horse_animate_array = get_graphics_stats (enemyFrameCounter, 1);
	struct graphics_arrays zombie_animate_array = get_graphics_stats (enemyFrameCounter, 2);
	if (type == 1) {
		
		SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
		glUseProgram(shaderProgramID);
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) horse_animate_array.Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) horse_animate_array.Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) horse_animate_array.TexCoords); 
	}
	else if (type == 5) {

		SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
		glUseProgram(shaderProgramID);
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) zombie_animate_array.Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) zombie_animate_array.Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) zombie_animate_array.TexCoords); 
	}
	
	else if (type == 6) {
		SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
		glUseProgram(shaderProgramID);
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) tankVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) tankNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) tankTexCoords); 
	}
	else if (type == 7) {
		SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
		glUseProgram(shaderProgramID);
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) spaceshipVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) spaceshipNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) spaceshipTexCoords); 
	}
	
	const Texture* const thisTexture = textures[type];
	
    glEnableVertexAttribArray(vertexHandle);
    glEnableVertexAttribArray(normalHandle);
    glEnableVertexAttribArray(textureCoordHandle);      
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&EnemyProjection.data[0] );
	if (type == 1) {
		glDrawArrays(GL_TRIANGLES, 0, (int)*horse_animate_array.NumVerts);
	}
	if (type == 5) {
		glDrawArrays(GL_TRIANGLES, 0, (int)*zombie_animate_array.NumVerts);
	}
	if (type == 6) {
		glDrawArrays(GL_TRIANGLES, 0, tankNumVerts);
	}
	if (type == 7) {
		glDrawArrays(GL_TRIANGLES, 0, spaceshipNumVerts);
	}
    SampleUtils::checkGlError("ImageTargets renderFrame");
}

void DrawTower (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int type) {


	const Texture* const thisTexture = textures[type];
	//Castle = 0, Igloo = 3

    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &TowerMatrix.data[0], &TowerProjection.data[0]);
    glUseProgram(shaderProgramID);
	if (type == 0) {
	 LOG("type0");
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, towerVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, towerNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, towerTexCoords);
	}
	else if (type == 3) {
	LOG("type3");
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, iglooTexCoords);
	}
	else if (type == 9) {
		LOG("type9");
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, cannonVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, cannonNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, cannonTexCoords);
	}
    glEnableVertexAttribArray(vertexHandle);
	glEnableVertexAttribArray(normalHandle);
	glEnableVertexAttribArray(textureCoordHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&TowerProjection.data[0] );
	if (type == 0) {
		glDrawArrays(GL_TRIANGLES, 0, towerNumVerts);
	}
	else if (type == 3) {
		glDrawArrays(GL_TRIANGLES, 0, iglooNumVerts);
	}
	else if (type == 9) {
		glDrawArrays(GL_TRIANGLES, 0, cannonNumVerts);
	}
	SampleUtils::checkGlError("ImageTargets renderFrame");
}




void DrawMissile (QCAR::Matrix44F MissileMatrix, QCAR::Matrix44F MissileProjection, int type) {
	//Arrow = 2, Snowball =  4
	
	struct graphics_arrays arrow_animate_array = get_graphics_stats (missileFrameCounter, 0);
	const Texture* const thisTexture = textures[type];

    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &MissileMatrix.data[0], &MissileProjection.data[0]);
    glUseProgram(shaderProgramID);
	if (type == 2) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.TexCoords);
	}
	else if (type == 4) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, snowballVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, snowballNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, snowballTexCoords);
	}
	
    glEnableVertexAttribArray(vertexHandle);
    glEnableVertexAttribArray(normalHandle);
    glEnableVertexAttribArray(textureCoordHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&MissileProjection.data[0] );
	if (type == 2) {
		glDrawArrays(GL_TRIANGLES, 0, (int)*arrow_animate_array.NumVerts);
	}
	else if (type == 4) {
		glDrawArrays(GL_TRIANGLES, 0, snowballNumVerts);
	}
	SampleUtils::checkGlError("ImageTargets renderFrame");
}


//draws a selection ring around recognized markers without towers
void DrawSelRing (QCAR::Matrix44F selMatrix, QCAR::Matrix44F selProjection) {
    //TODO: no textures here or real model yet
    //const Texture* const thisTexture = textures[0];
    //Castle = 0, Igloo = 3

    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &selMatrix.data[0], &selProjection.data[0]);
    glUseProgram(shaderProgramID);
    glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, towerVerts);
    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, towerNormals);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, towerTexCoords);
    glEnableVertexAttribArray(vertexHandle);
    glEnableVertexAttribArray(normalHandle);
    glEnableVertexAttribArray(textureCoordHandle);
    glActiveTexture(GL_TEXTURE0);
    //glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&selProjection.data[0] );
    glDrawArrays(GL_TRIANGLES, 0, iglooNumVerts);
}




void getMarkerOffset(int trackedCornerID, int &x_offset, int &y_offset){
    if (trackedCornerID == 0) //top left marker
    {
        x_offset = 0;
        y_offset = 0;
    }
    else if (trackedCornerID ==1) //top right marker
    {
        x_offset = (-1) * (MARKER_SIZE * (BOARD_SIZE-1));
        y_offset = 0;
    }
    else if (trackedCornerID==2) //bottom left marker
    {
        x_offset = 0;
        y_offset = (MARKER_SIZE * (BOARD_SIZE-1));
    }
    else if (trackedCornerID==3) //bottom right marker
    {
        x_offset = (-1) * (MARKER_SIZE * (BOARD_SIZE-1));
        y_offset = (MARKER_SIZE * (BOARD_SIZE-1));
    } 
    else
    {
        LOG ("ERROR getMarkerOffset");
    }
}

/**********************
 * Find the BOARD x, y coordinates of a marker placed inside the board
 * Input: corner marker, tower modelviewmatrices, corner ID; output: dx, dy (by reference)
 **********************/
void convert2BoardCoord (int cornerID, QCAR::Matrix44F cornerMVM, QCAR::Matrix44F targetMVM, float &x, float &y){
    //first translate corner markers to top left (0,0) position
    int x_offset, y_offset;
    getMarkerOffset(cornerID, x_offset, y_offset);
    //translate the cornerMVM according to offset
    SampleUtils::translatePoseMatrix(x_offset, y_offset, 0, &cornerMVM.data[0]);
    //compute the board coordinates    
    x = ( cornerMVM.data[5] * targetMVM.data[12] - cornerMVM.data[4] * targetMVM.data[13] 
            - cornerMVM.data[5] * cornerMVM.data[12] + cornerMVM.data[4] * cornerMVM.data[13] )
        / ( cornerMVM.data[0] * cornerMVM.data[5] - cornerMVM.data[4] * cornerMVM.data[1] );
    y = ( cornerMVM.data[1] * targetMVM.data[12] - cornerMVM.data[0] * targetMVM.data[13] 
            - cornerMVM.data[1] * cornerMVM.data[12] + cornerMVM.data[0] * cornerMVM.data[13] )
        / ( cornerMVM.data[1] * cornerMVM.data[4] - cornerMVM.data[0] * cornerMVM.data[5] );
    //LOG ("Board (x,y)=(%f, %f)", x, y);
}



//********************************************************
// Tap event helpers
// *******************************************************

void
projectScreenPointToPlane(QCAR::Vec2F point, QCAR::Vec3F planeCenter, QCAR::Vec3F planeNormal,
                          QCAR::Vec3F &intersection, QCAR::Vec3F &lineStart, QCAR::Vec3F &lineEnd,
                          QCAR::Matrix44F modelViewMatrix)
{
    // Window Coordinates to Normalized Device Coordinates
    QCAR::VideoBackgroundConfig config = QCAR::Renderer::getInstance().getVideoBackgroundConfig();
    
    float halfScreenWidth = screenWidth / 2.0f;
    float halfScreenHeight = screenHeight / 2.0f;
    
    float halfViewportWidth = config.mSize.data[0] / 2.0f;
    float halfViewportHeight = config.mSize.data[1] / 2.0f;
    
    float x = (point.data[0] - halfScreenWidth) / halfViewportWidth;
    float y = (point.data[1] - halfScreenHeight) / halfViewportHeight * -1;
    
    QCAR::Vec4F ndcNear(x, y, -1, 1);
    QCAR::Vec4F ndcFar(x, y, 1, 1);
    
    // Normalized Device Coordinates to Eye Coordinates
    QCAR::Vec4F pointOnNearPlane = SampleMath::Vec4FTransform(ndcNear, inverseProjMatrix);
    QCAR::Vec4F pointOnFarPlane = SampleMath::Vec4FTransform(ndcFar, inverseProjMatrix);
    pointOnNearPlane = SampleMath::Vec3FDiv(pointOnNearPlane, pointOnNearPlane.data[3]);
    pointOnFarPlane = SampleMath::Vec3FDiv(pointOnFarPlane, pointOnFarPlane.data[3]);
    
    // Eye Coordinates to Object Coordinates
    QCAR::Matrix44F inverseModelViewMatrix = SampleMath::Matrix44FInverse(modelViewMatrix);
    
    QCAR::Vec4F nearWorld = SampleMath::Vec4FTransform(pointOnNearPlane, inverseModelViewMatrix);
    QCAR::Vec4F farWorld = SampleMath::Vec4FTransform(pointOnFarPlane, inverseModelViewMatrix);
    
    lineStart = QCAR::Vec3F(nearWorld.data[0], nearWorld.data[1], nearWorld.data[2]);
    lineEnd = QCAR::Vec3F(farWorld.data[0], farWorld.data[1], farWorld.data[2]);
    linePlaneIntersection(lineStart, lineEnd, planeCenter, planeNormal, intersection);
}


bool
linePlaneIntersection(QCAR::Vec3F lineStart, QCAR::Vec3F lineEnd,
                      QCAR::Vec3F pointOnPlane, QCAR::Vec3F planeNormal,
                      QCAR::Vec3F &intersection)
{
    QCAR::Vec3F lineDir = SampleMath::Vec3FSub(lineEnd, lineStart);
    lineDir = SampleMath::Vec3FNormalize(lineDir);
    
    QCAR::Vec3F planeDir = SampleMath::Vec3FSub(pointOnPlane, lineStart);
    
    float n = SampleMath::Vec3FDot(planeNormal, planeDir);
    float d = SampleMath::Vec3FDot(planeNormal, lineDir);
    
    if (fabs(d) < 0.00001) {
        // Line is parallel to plane
        return false;
    }
    
    float dist = n / d;
    
    QCAR::Vec3F offset = SampleMath::Vec3FScale(lineDir, dist);
    intersection = SampleMath::Vec3FAdd(lineStart, offset);
	//TODO NOTE by ALTON: added this don't know if its correct
	return true;
}


//given a marker, check if the tap is inside the marker
bool checkTapMarker (const QCAR::Marker* marker, QCAR::Matrix44F markerMVM){

    if(tap){
        LOG("tap true");


        QCAR::Vec3F intersection, lineStart, lineEnd;
        projectScreenPointToPlane(QCAR::Vec2F(tapX, tapY), QCAR::Vec3F(0, 0, 0), QCAR::Vec3F(0, 0, 1), intersection, lineStart, lineEnd, markerMVM);

        QCAR::Vec2F trackableSize = marker->getSize();

        LOG("tap coordinates (screen space): %.2f, %.2f", tapX, tapY);
        LOG("tap coordinates (target space): %.2f, %.2f", intersection.data[0], intersection.data[1]);

        if (fabs(intersection.data[0]) < (trackableSize.data[0] / 2) &&
                fabs(intersection.data[1]) < (trackableSize.data[1] / 2))
        {
            LOG("tapped inside the target!");
            tap = false;
            return true;
        }
    }
    return false;
}


