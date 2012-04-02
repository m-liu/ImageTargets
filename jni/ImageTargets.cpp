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
Level level[NUM_LEVELS+1];
int currentLevel = 0;
int currentLives = 20;

int currentScore = 0;
int currentZen = 20;

float currentDiff = 1;
int stageType = 1;

int buyType = -1;
int buyMarker = -1;

int upgMarker = -1;

int delMarker = -1;

bool displayedMessage = false;

int startGame = 0;
int seeTargets = 0;
static int pauseGame = 0;
int soundflag_arrow = 0;
int soundflag_snowball = 0;
int soundflag_cannon = 0;
int soundflag_level = 0;
int soundflag_coin = 0;

char level1path[BOARD_SIZE][BOARD_SIZE] = {
{'1', '1', '1', '1', '1', '1', '1', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'}
};

char level2path[BOARD_SIZE][BOARD_SIZE] = {
{'1', '0', '0', '0', '1', '1', '1', '1'},
{'1', '0', '0', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '1'},
{'1', '0', '0', '0', '1', '0', '0', '1'},
{'1', '1', '1', '1', '1', '0', '0', '1'}
};

char level3path[BOARD_SIZE][BOARD_SIZE] = {
{'1', '1', '1', '1', '1', '1', '1', '1'},
{'0', '0', '0', '0', '0', '0', '0', '1'},
{'0', '1', '1', '1', '1', '1', '0', '1'},
{'0', '1', '0', '0', '0', '1', '0', '1'},
{'0', '1', '0', '1', '1', '1', '0', '1'},
{'0', '1', '0', '0', '0', '0', '0', '1'},
{'0', '1', '0', '0', '0', '0', '0', '1'},
{'0', '1', '1', '1', '1', '1', '1', '1'}
};



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
void DrawHpBar (QCAR::Matrix44F EnemyMatrix, QCAR::Matrix44F EnemyProjection, int index);
void DrawTower (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int type);
void DrawMissile (QCAR::Matrix44F MissileMatrix, QCAR::Matrix44F MissileProjection, int type);
void DrawSelRing (QCAR::Matrix44F selMatrix, QCAR::Matrix44F selProjection, int ring_type);
void DrawPath (QCAR::Matrix44F trackerMVM, QCAR::Matrix44F pathProjection, int x_offset, int y_offset, int currentLevel);

void getMarkerOffset(int trackedCornerID, int &x_offset, int &y_offset);
void convert2BoardCoord (int cornerID, QCAR::Matrix44F cornerMVM, QCAR::Matrix44F targetMVM, float &x, float &y);
float snap2Grid (float x);

//for tap event computations

bool checkTapMarker (const QCAR::Marker* marker, QCAR::Matrix44F markerMVM);
bool hasPathCollision (int trackerID, QCAR::Matrix44F trackerMVM, QCAR::Matrix44F towerMatrix, int stageType);
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
showUpgradeButton(int cost)
{
	char scoreString[10];
	sprintf (scoreString, "%d", cost);
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
	jstring js = javaEnv->NewStringUTF(scoreString);
    jmethodID method = javaEnv->GetMethodID(javaClass, "showUpgradeButton", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}

void
hideUpgradeButton2(int cost)
{
	char scoreString[10];
	sprintf (scoreString, "%d", cost);
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that hides the delete button
	jstring js = javaEnv->NewStringUTF(scoreString);
    jmethodID method = javaEnv->GetMethodID(javaClass, "hideUpgradeButton2", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
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
			pauseGame = 1;
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeUnpause(JNIEnv*, jobject)
{
			for (int i=0; i<MAX_NUM_ENEMIES; i++){
				enemy[i].prevTime = getCurrentTime();  
            }
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
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeLeave(JNIEnv*, jobject)
{
			//update times
			for (int i=0; i<MAX_NUM_ENEMIES; i++){
				enemy[i].prevTime = getCurrentTime();  
            }
			if (startGame == 1) {
				showPauseButton();
			}
			pauseGame = 0;

}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeStart(JNIEnv*, jobject)
{
			if (seeTargets == 1)
			{
				startGame = 1;
				hideStartButton();
				showPauseButton();
				//hideStoreButton();
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

/*
JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_GUIManager_nativeCredits(JNIEnv*, jobject)
{
 			displayMessage("Credits!\n\n\nTeamRickroll'd\nMing Liu\n David Chou\n  Alton Chiu\n\n\nProfessor Enright Jerger\n\nECE496 2011-2012");
}*/

JNIEXPORT jint JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeBuy(JNIEnv *env, jobject thiz, jint type)
{

if (currentZen - missile_type[type].cost < 0)
{
	return (jint)(-1);
}

    //a purchase was made. Initialize the tower and deduct the cost
    LOG("nativeBuy called");

    
    //check that we have a selection
    if (selMarkerID < 0){
        LOG("ERROR nativeBuy: selMarkerID < 0");
        return (jint)(-2);
    }
    
	if (tower[selMarkerID].initialized == true)
	{
		LOG("can't upgrade, inited");
		return (jint)(-3);
	}

		
	buyType = (int)type;
	buyMarker = selMarkerID;
	
	return (jint)0;
}

JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeUpgrade(JNIEnv *env)
{
	//a purchase was made. Initialize the tower and deduct the cost
    LOG("nativeUpgrade called");

    //check that we have a selection
    if (selMarkerID < 0){
        LOG("ERROR nativeUpgrade: selMarkerID < 0");
        return(jint)(-2);
    }
	LOG("nativeUpgrade: currentZen=%d, tower[selMarkerID].upgradeCost=%d", currentZen, tower[selMarkerID].upgradeCost);
	if (currentZen - tower[selMarkerID].upgradeCost < 0)
	{
		LOG("can't upgrade, cost");
		return (jint)(-1);
	}
	
	if (tower[selMarkerID].type < 0 || tower[selMarkerID].type > 8)
	{
		LOG("can't upgrade, type");
		return (jint)(-3);
	}
		
	upgMarker = selMarkerID;
	
	return (jint)0;
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeDelete(JNIEnv*, jobject)
{
    //a purchase was made. Initialize the tower and deduct the cost
    LOG("nativeDelete called");

    //check that we have a selection
    if (selMarkerID < 0){
        LOG("ERROR nativeDelete: selMarkerID < 0");
        return;
    }
	
    LOG("nativeDelete: selMarkerID=%d", selMarkerID);
	
	  if (!tower[selMarkerID].initialized){
        LOG("ERROR nativeDelete: selMarkerID < 0");
        return;
    }
	
	delMarker = selMarkerID;
	
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeGameOver(JNIEnv*, jobject)
{
    gameOver();
}



JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargets_nativeSettings(JNIEnv *env, jobject thiz, jint level, jint difficulty, jint lives)//type?
{
stageType = (int)level;
currentLives = (int)lives;

int diff = (int)difficulty;
if (diff == 1)
	currentDiff = 1.0f;
else if (diff == 2)
	currentDiff = 1.2f;
else if (diff == 3)
	currentDiff = 1.4f;
else
	currentDiff = 1.0f;
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

    QCAR::setHint(QCAR::HINT_MAX_SIMULTANEOUS_IMAGE_TARGETS, 20);
    //QCAR::setHint(QCAR::HINT_IMAGE_TARGET_MULTI_FRAME_ENABLED, 1);
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


void renderBuyTower () {

	if (buyMarker != -1) {
		LOG("BuyTower: selMarkerID=%d, towerType=%d", buyMarker, buyType);
		//initialize the tower
		makeTower(buyType, buyMarker);

		//deduct cost
		currentZen = currentZen - missile_type[buyType].cost;
		LOG("nativeBuy: before deduct zen");
		displayZen(currentZen);
		LOG("nativeBuy: after deduct zen");
		
					
		hideStoreButton();
		showDeleteButton();
		if ((currentZen - tower_type[buyType].upgradeCost >= 0)
			)
			showUpgradeButton(tower_type[buyType].upgradeCost);
		else
			hideUpgradeButton2(tower_type[buyType].upgradeCost);

	
		
		buyMarker = -1;
		buyType = -1;
	}
}

void renderUpgradeTower () {

	if (upgMarker != -1) {
		LOG("nativeUpgrade: selMarkerID=%d", upgMarker);

		//deduct cost
		currentZen = currentZen - tower[upgMarker].upgradeCost;
		LOG("nativeUpgrade: before deduct zen");
		displayZen(currentZen);
		LOG("nativeUpgrade: after deduct zen");
		//initialize the tower
		upgradeTower(upgMarker);
		LOG("nativeUpgrade: after upgrade");
		
		hideStoreButton();
		showDeleteButton();
		if ((tower[upgMarker].type < 9) 
			&& (currentZen - tower[upgMarker].upgradeCost >= 0)
			)
			showUpgradeButton(tower[upgMarker].upgradeCost);
		else
			hideUpgradeButton2(tower[upgMarker].upgradeCost);

		
		upgMarker = -1;
	}
}

void renderDeleteTower () {
	if (delMarker != -1) {
		//initialize the tower
			
		currentZen = floor(currentZen + missile[delMarker].cost/2);
		LOG("nativeBuy: before deduct zen");
		displayZen(currentZen);
		
		deleteTower(selMarkerID);
		
		
		
		showStoreButton();
		hideUpgradeButton();
		hideDeleteButton();
		delMarker = -1;
	
	}
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
 //   glEnable(GL_CULL_FACE);
	
	
    //helper vars
    int x_offset;
    int y_offset;
    int testID = -1;
    int trackerID=-1; //the corner marker # used to render enemies
    QCAR::Matrix44F trackerMVM; //save the corner marker MVM


    //game updates - always do even if no tracker found
    if (startGame == 1 && pauseGame == 0) {
        for (int i=0; i<MAX_NUM_ENEMIES; i++){
            animateEnemy(i);
        }
        for (int i=0; i<MAX_NUM_TOWERS; i++){
            if (missile[i].initialized==true){
                animateMissile(i);
            }
        }

    }




    // Did we find any trackables this frame?
    // first loop through all trackables to find a reference "tracker" marker
    for(int tIdx = 0; tIdx < state.getNumActiveTrackables(); tIdx++)
    {
        //LOG("num tracked: %d", state.getNumActiveTrackables());
        // Get the trackable
        const QCAR::Trackable* trackable = state.getActiveTrackable(tIdx);

        // Check the type of the trackable:
        assert(trackable->getType() == QCAR::Trackable::MARKER);
        const QCAR::Marker* marker = static_cast<const QCAR::Marker*>(trackable);
        
        testID = marker->getMarkerId();
        trackerMVM = QCAR::Tool::convertPose2GLMatrix(trackable->getPose());
        
        //use corner markers OR initialized towers as trackers
        if ( (testID < 4) ||
                (tower[testID].initialized==true && 
                 tower[testID].boardX != -100000 && 
                 tower[testID].boardY != -100000 ) ) 
        {
            //get the modelview matrix of the corner marker
            trackerID=testID;
            getMarkerOffset(trackerID, x_offset, y_offset);
            /*
            if (testID >= 4){
                LOG("using TOWER marker #%d as tracker", testID);
                LOG("x_offset=%d, y_offset=%d", x_offset, y_offset);
            }
            */
            break;
        }
    }


    //if a tracker is found, then render the rest
    if (trackerID >= 0) {
        for(int tIdx = 0; tIdx < state.getNumActiveTrackables(); tIdx++)
        {
            // Get the trackable
            const QCAR::Trackable* trackable = state.getActiveTrackable(tIdx);

            // Check the type of the trackable:
            assert(trackable->getType() == QCAR::Trackable::MARKER);
            const QCAR::Marker* marker = static_cast<const QCAR::Marker*>(trackable);

            if (startGame == 1 && pauseGame == 0) {
                //animate and draw the enemy units in reference to the tracker position
                for (int i=0; i<MAX_NUM_ENEMIES; i++){
                    QCAR::Matrix44F HPMatrix = trackerMVM; 
					QCAR::Matrix44F enemyMatrix = trackerMVM;   
					//animateEnemy(i);
                    animateEnemyMatrix(enemyMatrix, HPMatrix, i, x_offset, y_offset); //animate the i-th enemy
                    QCAR::Matrix44F enemyProjection;
					QCAR::Matrix44F HPProjection;
                    if (enemy[i].deployed && !enemy[i].dead){ 
	                    DrawEnemy(enemyMatrix, enemyProjection, enemy[i].texture);
	                    DrawHpBar(HPMatrix, HPProjection,i);
                    }
                }
            }

            //render towers and missiles
            if (marker->getMarkerId() >= 4 && marker->getMarkerId() < MAX_NUM_MARKERS) {

                //get the marker id
                int mID = (marker->getMarkerId());
                QCAR::Matrix44F towerMatrix = QCAR::Tool::convertPose2GLMatrix(trackable->getPose());
                QCAR::Matrix44F towerProjection;


                //if marker is tapped, show store and upgrade buttons
                if ( checkTapMarker(marker, towerMatrix) 
                        && !hasPathCollision(trackerID, trackerMVM, towerMatrix, stageType) )
                {
                    if (!tower[mID].initialized){
						showStoreButton();
						hideUpgradeButton();
						hideDeleteButton();
					}
                    else if (tower[mID].initialized){
	                    hideStoreButton();
						showDeleteButton();
						if (/*tower[mID].upgradeLevel != 2 &&*/(tower[mID].type != 9 && tower[mID].type != 10 && tower[mID].type != 11) 
						&& (currentZen - tower[mID].upgradeCost >= 0)
						)
							showUpgradeButton(tower[mID].upgradeCost);
						else
							hideUpgradeButton2(tower[mID].upgradeCost);

					}
                    selMarkerID = mID;
                }
                    
                
                //draw selection ring
                if (selMarkerID >= 0 && selMarkerID == mID){
                    DrawSelRing(towerMatrix, towerProjection, 1); 
                }

                //draw the tower at the precise location of the marker if it's initialized
                if (tower[mID].initialized){
                    animateTower(towerMatrix, mID);
                    DrawTower(towerMatrix, towerProjection, tower[mID].texture); 

                    //find x, y board coordinates of the tower marker
                    if (mID != trackerID){
                        convert2BoardCoord (trackerID, trackerMVM, towerMatrix, tower[mID].boardX, tower[mID].boardY);
                    }

                    //initialize the missile if not init
                    if (!missile[mID].initialized){
                        makeMissile (tower[mID].type, mID, tower[mID].boardX, tower[mID].boardY);
                    }
                    //always update the original missile position (in case of glitches)
                    updateMissileDefaultPos (mID, tower[mID].boardX, tower[mID].boardY);

                    //animate missile with respect to corner marker
                    QCAR::Matrix44F missileMatrix = trackerMVM;    
                    getMarkerOffset(trackerID, x_offset, y_offset);
                    if (startGame == 1 && pauseGame == 0) {
						//animateMissile(mID);
                        animateMissileMatrix(missileMatrix, mID, x_offset, y_offset);
                        //checkMissileContact(mID);
                    }
#ifdef USE_OPENGL_ES_1_1
#else
                    QCAR::Matrix44F missileProjection;
                    if (missile[mID].currentTarget != -1 &&  missile[mID].updatedShotTime == true) {
                    	DrawMissile(missileMatrix, missileProjection, missile[mID].texture); 
                    }
#endif

                }
        
                //if tower is uninitialized & !selected, display a ring to indicate marker is recognized
                else if (selMarkerID != mID 
                        && !hasPathCollision(trackerID, trackerMVM, towerMatrix, stageType)) 
                {                                  
                    DrawSelRing(towerMatrix, towerProjection, 0); 
                }

            }//end tower drawing

            //render enemy path
            QCAR::Matrix44F pathProjection;
            DrawPath (trackerMVM, pathProjection, x_offset, y_offset, stageType);




            // If this is our first time seeing the target, display a tip
            if (!displayedMessage) {
                displayMessage("Press Start!");
                seeTargets = 1;
                counterprevTime = getCurrentTime();
                //TODO: move this at some point			
                displayedMessage = true;
            }

        }

    }

    //re-render every frame
    trackerID=-1;
    //if tap outside markers, unselect tower
    if (tap) { 
        hideStoreButton();
        hideUpgradeButton();
		hideDeleteButton();
        selMarkerID = -1;
    }
    //reset tap
    tap = false;
	
	renderBuyTower();
	renderUpgradeTower();
	renderDeleteTower();

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
	displayScore(currentScore);
	displayZen(currentZen);
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
    if (!QCAR::CameraDevice::getInstance().init()) {
		LOG("StartCamera: First Exit");
        return;
	}

    // Configure the video background
    configureVideoBackground();

    // Select the default mode:
    if (!QCAR::CameraDevice::getInstance().selectVideoMode(
                                QCAR::CameraDevice::MODE_DEFAULT))
		{						
			LOG("StartCamera: Second Exit");				
			return;
		}

    // Start the camera:
    if (!QCAR::CameraDevice::getInstance().start())
	{
		LOG("StartCamera: Third Exit");
        return;
	}
	LOG("StartCamera: No Exit");
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

JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_getSoundFlag(
                                                    JNIEnv* env, jobject obj,jint type)
{
    if (type == 0){
    	return soundflag_arrow;
    }
    else if (type == 1){
    	return soundflag_snowball;
    }
    else if (type == 2){
    	return soundflag_cannon;
    }
    else if (type == 3){
    	return soundflag_level;
    }
    else if (type == 4){
    	return soundflag_coin;
    }
    else 
    	return -1;
}

JNIEXPORT int JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_getCurrentLevel(
                                                    JNIEnv* env, jobject obj)
{
    return currentLevel;
}

JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_resetSoundFlag(
                                                    JNIEnv* env, jobject obj){
    soundflag_arrow = 0;
    soundflag_cannon = 0;
    soundflag_snowball = 0;
    soundflag_level = 0;
    soundflag_coin = 0;
}

#ifdef __cplusplus
}
#endif








/****************************************************
 * Draw functions
 * **************************************************/

void DrawHpBar (QCAR::Matrix44F EnemyMatrix, QCAR::Matrix44F EnemyProjection, int index) {
	SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
	glUseProgram(shaderProgramID);
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) hp_barVerts);
	glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) hp_barNormals);
	glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) hp_barTexCoords); 
	
	float hp_percent = enemy[index].HP/enemy[index].max_HP;
	Texture* thisTexture = textures[11];
	if ((hp_percent == 1)) {
		thisTexture = textures[11];
	} 
	else if ((hp_percent >= 0.9)) {
		thisTexture = textures[12];
	} 
	else if ((hp_percent >= 0.8) && (hp_percent < 0.9)) {
		thisTexture = textures[13];
	} 
	else if ((hp_percent >= 0.7) && (hp_percent < 0.8)) {
		thisTexture = textures[14];
	} 
	else if ((hp_percent >= 0.6) && (hp_percent < 0.7)) {
		thisTexture = textures[15];
	} 
	else if ((hp_percent >= 0.5) && (hp_percent < 0.6)) {
		thisTexture = textures[16];
	} 
	else if ((hp_percent >= 0.4) && (hp_percent < 0.5)) {
		thisTexture = textures[17];
	} 
	else if ((hp_percent >= 0.3) && (hp_percent < 0.4)) {
		thisTexture = textures[18];
	} 
	else if ((hp_percent >= 0.2) && (hp_percent < 0.3)) {
		thisTexture = textures[19];
	} 
	else if ((hp_percent >= 0.1) && (hp_percent < 0.2)) {
		thisTexture = textures[20];
	} 
	else if ((hp_percent >= 0) && (hp_percent < 0.1)) {
		thisTexture = textures[20];
	} 
	
    glEnableVertexAttribArray(vertexHandle);
    glEnableVertexAttribArray(normalHandle);
    glEnableVertexAttribArray(textureCoordHandle);      
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&EnemyProjection.data[0] );
    
    glDrawArrays(GL_TRIANGLES, 0, hp_barNumVerts);
    
    SampleUtils::checkGlError("ImageTargets renderFrame");
}

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
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) tank2Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) tank2Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) tank2TexCoords); 
	}
	else if (type == 7) {
		SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
		glUseProgram(shaderProgramID);
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) spaceship2Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) spaceship2Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) spaceship2TexCoords); 
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
		glDrawArrays(GL_TRIANGLES, 0, tank2NumVerts);
	}
	if (type == 7) {
		glDrawArrays(GL_TRIANGLES, 0, spaceship2NumVerts);
	}
    SampleUtils::checkGlError("ImageTargets renderFrame");
}

void DrawTower (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int type) {


	const Texture* const thisTexture = textures[type];
	//Castle = 0, Igloo = 3

    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &TowerMatrix.data[0], &TowerProjection.data[0]);
    glUseProgram(shaderProgramID);
	if (type == 0 || type == 21 || type == 22 || type == 23) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, towerVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, towerNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, towerTexCoords);
	}
	else if (type == 3 || type == 24 || type == 25 || type == 26) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, iglooTexCoords);
	}
	else if (type == 9 || type == 27 || type == 28 || type == 29) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, cannonVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, cannonNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, cannonTexCoords);
	}
	else {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, towerVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, towerNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, towerTexCoords);
	}
    glEnableVertexAttribArray(vertexHandle);
	glEnableVertexAttribArray(normalHandle);
	glEnableVertexAttribArray(textureCoordHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&TowerProjection.data[0] );
	if (type == 0 || type == 21 || type == 22 || type == 23) {
		glDrawArrays(GL_TRIANGLES, 0, towerNumVerts);
	}
	else if (type == 3 || type == 24 || type == 25 || type == 26) {
		glDrawArrays(GL_TRIANGLES, 0, iglooNumVerts);
	}
	else if (type == 9 || type == 27 || type == 28 || type == 29) {
		glDrawArrays(GL_TRIANGLES, 0, cannonNumVerts);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, towerNumVerts);
	}
	SampleUtils::checkGlError("ImageTargets renderFrame");
}




void DrawMissile (QCAR::Matrix44F MissileMatrix, QCAR::Matrix44F MissileProjection, int type) {
	//Arrow = 2, Snowball =  4, Cannonball = 10
	
	struct graphics_arrays arrow_animate_array = get_graphics_stats (missileFrameCounter, 0);
	const Texture* const thisTexture = textures[type];

    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &MissileMatrix.data[0], &MissileProjection.data[0]);
    glUseProgram(shaderProgramID);
	if (type == 2) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.TexCoords);
	}
	else if (type == 4 || type == 10) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, snowballVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, snowballNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, snowballTexCoords);
	}
	else {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.Verts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.Normals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, arrow_animate_array.TexCoords);
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
	else if (type == 4|| type == 10) {
		glDrawArrays(GL_TRIANGLES, 0, snowballNumVerts);
	}
	else {
		glDrawArrays(GL_TRIANGLES, 0, (int)*arrow_animate_array.NumVerts);
	}
	SampleUtils::checkGlError("ImageTargets renderFrame");
}


//draws a selection ring around recognized markers without towers
void DrawSelRing (QCAR::Matrix44F selMatrix, QCAR::Matrix44F selProjection, int ring_type) {

    Texture* thisTexture;
	SampleUtils::translatePoseMatrix(0, 0, 5, &selMatrix.data[0]);
    //sel ring texture is 30
    if (ring_type==1){ //selected ring
        SampleUtils::scalePoseMatrix(35,35,0, &selMatrix.data[0]);
        thisTexture = textures[30];
    }
    else { //recognized marker ring
        SampleUtils::scalePoseMatrix(20,20,0, &selMatrix.data[0]);
        thisTexture = textures[31];
        //const Texture* const thisTexture = textures[31];
    }

    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &selMatrix.data[0], &selProjection.data[0]);
    glUseProgram(shaderProgramID);
    glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeVertices[0]);
    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeNormals[0]);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &cubeTexCoords[0]);
    glEnableVertexAttribArray(vertexHandle);
    glEnableVertexAttribArray(normalHandle);
    glEnableVertexAttribArray(textureCoordHandle);
    //blending of graphics?
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&selProjection.data[0] );

    //glDrawArrays(GL_TRIANGLES, 0, towerNumVerts);
    glDrawElements(GL_TRIANGLES, NUM_CUBE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &cubeIndices[0]);
    glDisable(GL_BLEND);
    SampleUtils::checkGlError("ImageTargets renderFrame");

}



//draw the enemy path terrain, tile by tile
void 
DrawPath (QCAR::Matrix44F trackerMVM, QCAR::Matrix44F pathProjection, int x_offset, int y_offset, int stageType){
    Texture* thisTexture;

    char (*path_ptr)[BOARD_SIZE];
    if (stageType==1){
        path_ptr = level1path;
    }
    else if (stageType==2){
        path_ptr = level2path;
    }
    else if (stageType==3){
        path_ptr = level3path;
    }
    else {
        LOG("ERROR bad stageType");
    }

    //save the projection and MVM each loop
    QCAR::Matrix44F tmpMVM;
    QCAR::Matrix44F tmpProjection;

    for (int j=0; j<BOARD_SIZE; j++){
        for (int i=0; i<BOARD_SIZE; i++){
            if (path_ptr[j][i] == '1'){
                //reset the matrices
                tmpMVM = trackerMVM;
                tmpProjection = pathProjection;
                //calculate tile position
                int tileX = i * TILE_SIZE;
                int tileY = -j * TILE_SIZE;
                //render the tile at that position
                SampleUtils::translatePoseMatrix(tileX + x_offset, tileY + y_offset, 0, &tmpMVM.data[0]);
                SampleUtils::rotatePoseMatrix(90, 1.0f, 0.0f, 0.0f, &tmpMVM.data[0]);
                SampleUtils::rotatePoseMatrix(180, 0.0f, 0.0f, 1.0f, &tmpMVM.data[0]);
                SampleUtils::scalePoseMatrix(TILE_SIZE, TILE_SIZE, TILE_SIZE, &tmpMVM.data[0]);

                thisTexture = textures[32];

                SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &tmpMVM.data[0], &tmpProjection.data[0]);
                glUseProgram(shaderProgramID);
                glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &groundVerts[0]);
                glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &groundNormals[0]);
                glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) &groundTexCoords[0]);
                glEnableVertexAttribArray(vertexHandle);
                glEnableVertexAttribArray(normalHandle);
                glEnableVertexAttribArray(textureCoordHandle);
                //blending of graphics?
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
                glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&tmpProjection.data[0] );

                glDrawArrays(GL_TRIANGLES, 0, groundNumVerts);
                //glDrawElements(GL_TRIANGLES, NUM_CUBE_INDEX, GL_UNSIGNED_SHORT, (const GLvoid*) &cubeIndices[0]);
                glDisable(GL_BLEND);
                SampleUtils::checkGlError("ImageTargets renderFrame");
    

            }
        }
    }
}


void getMarkerOffset(int trackerID, int &x_offset, int &y_offset){
    if (trackerID == 0) //top left marker
    {
        x_offset = 0;
        y_offset = 0;
    }
    else if (trackerID ==1) //top right marker
    {
        x_offset = (-1) * (TILE_SIZE * (BOARD_SIZE-1));
        y_offset = 0;
    }
    else if (trackerID==2) //bottom left marker
    {
        x_offset = 0;
        y_offset = (TILE_SIZE * (BOARD_SIZE-1));
    }
    else if (trackerID==3) //bottom right marker
    {
        x_offset = (-1) * (TILE_SIZE * (BOARD_SIZE-1));
        y_offset = (TILE_SIZE * (BOARD_SIZE-1));
    }
    else if (trackerID > 3 && trackerID < MAX_NUM_MARKERS) //using towers as tracker
    {   
        //FIXME: may not be correct?
        x_offset = tower[trackerID].boardX * (-1); //may need to -1 boardX
        y_offset = tower[trackerID].boardY * (-1);
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
    //compute the board coordinates by finding translation between the two MVMs
    // T = CornerMVM ^-1 * TargetMVM

    //inverse the cornerMVM
    QCAR::Matrix44F invCornerMVM;
    invCornerMVM = SampleMath::Matrix44FInverse(cornerMVM);
    

    QCAR::Vec4F transVec, targetVec;
    //extract the translation components of the targetMVM
    targetVec.data[0] = targetMVM.data[12]; 
    targetVec.data[1] = targetMVM.data[13]; 
    targetVec.data[2] = targetMVM.data[14]; 
    targetVec.data[3] = targetMVM.data[15]; 
    //multiply this target vec with inverse cornerMVM
    transVec = SampleMath::Vec4FTransform(targetVec, invCornerMVM);

    //extract the x,y translations only
    x = transVec.data[0];
    y = transVec.data[1];
    //LOG ("NEW: marker has board coordinates: (%f, %f)", x, y);
    
    /*
    // BAD BAD BAD!!! 
    x = ( cornerMVM.data[5] * targetMVM.data[12] - cornerMVM.data[4] * targetMVM.data[13] 
            - cornerMVM.data[5] * cornerMVM.data[12] + cornerMVM.data[4] * cornerMVM.data[13] )
        / ( cornerMVM.data[0] * cornerMVM.data[5] - cornerMVM.data[4] * cornerMVM.data[1] );
    y = ( cornerMVM.data[1] * targetMVM.data[12] - cornerMVM.data[0] * targetMVM.data[13] 
            - cornerMVM.data[1] * cornerMVM.data[12] + cornerMVM.data[0] * cornerMVM.data[13] )
        / ( cornerMVM.data[1] * cornerMVM.data[4] - cornerMVM.data[0] * cornerMVM.data[5] );
    //LOG ("Board (x,y)=(%f, %f)", x, y);
    */

    //TODO: enable this?
    //Assume snapping to an 8x8 grid.
    x = snap2Grid(x);
    y = (-1) * snap2Grid(-y);
    //LOG ("marker snapped to coordinates: (%f, %f)", x, y);
    
}

//provide an estimate if the markers snaps to the board grid
float snap2Grid (float x){

    for (int i=0; i< BOARD_SIZE; i++){
        if ( (x > i*TILE_SIZE - TILE_SIZE/2 ) && (x <= i*TILE_SIZE + TILE_SIZE/2) ) {
            return (i*TILE_SIZE);
        }
    }

    //If no match found, return the original value
    LOG("BAD ESTIMATE FOR BOARD COORDINATES x=%f", x);
    return x;
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


bool hasPathCollision (int trackerID, QCAR::Matrix44F trackerMVM, QCAR::Matrix44F towerMatrix, int stageType){
    float xBoard, yBoard;
    convert2BoardCoord (trackerID, trackerMVM, towerMatrix, xBoard, yBoard);

    char (*path_ptr)[BOARD_SIZE];
    if (stageType==1){
        path_ptr = level1path;
    }
    else if (stageType==2){
        path_ptr = level2path;
    }
    else if (stageType==3){
        path_ptr = level3path;
    }
    else {
        LOG("ERROR bad stageType");
    }


    //determine the tile index the xBoard and yBoard coresponds to
    int xTile = xBoard/TILE_SIZE;
    int yTile = -yBoard/TILE_SIZE;

    //boundary check!
    if (xTile >= 0 && xTile <BOARD_SIZE && yTile >= 0 && yTile <BOARD_SIZE){
        if (path_ptr[yTile][xTile] == '1'){
            //LOG("path collision detected for (%d, %d)", xTile, yTile);
            return true;
        }
        else{
            return false;
        }
    }
    else {
        LOG ("hasPathCollision: xTile or yTile out of bounds (%d, %d) and are ignored", xTile, yTile);
    }
    return true;
}



    
