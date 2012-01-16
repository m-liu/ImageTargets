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

#include "SampleUtils.h"
#include "Texture.h"
#include "CubeShaders.h"
//#include "Teapot.h"
#include "tower.h"
#include "snowball.h"
//#include "Arrow.h"
#include "igloo.h"
#include "graphics_arrays.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Textures:
int textureCount                = 0;
Texture** textures              = 0;

struct Enemy_unit
{
    int type;
//	char name[20];
    float X;
    float Y;
	float HP;
	float max_HP;
	float speed;
	float defense;
	float count;
    double prevTime;
};

struct Missile_unit
{
	bool initialized;
    int type;
//	char name[20];
    float X;
    float Y;
	float defaultX;
	float defaultY;
	float speed;
	float attack;
	float cost;
	int currentTarget;
	float currentTargetDistance;
	double prevTime;
};

struct Starting_position
{
float X;
float Y;
};

struct Level
{
float start;
float end;
int killCount;
};

JNIEnv* javaEnv;
jobject javaObj;
jclass javaClass;
bool displayedMessage = false;

//enemy properties
#define MAX_NUM_ENEMIES 10
#define NUM_ENEMY_TYPES 2
#define ENEMY_NUM_FRAMES 48

//tower/missile properties
#define NUM_MISSILE_TYPES 2
#define MAX_NUM_TOWERS 4
#define MISSILE_NUM_FRAMES 24

//board properties
#define MARKER_SIZE 50
#define BOARD_SIZE 8  //8x8 markers

//game properties
#define NUM_LEVELS 3


static int lives = 5;
static int startGame = 1;
static int currentLevel = 0;
static int numEnemies = MAX_NUM_ENEMIES; //TODO: What's this var for? Nothing, apparently.

static class Enemy_unit enemy[MAX_NUM_ENEMIES];
static class Missile_unit missile[MAX_NUM_TOWERS];
static class Enemy_unit enemy_type[NUM_ENEMY_TYPES];
static class Missile_unit missile_type[NUM_MISSILE_TYPES];
static class Level level[NUM_LEVELS];


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

// Constants:
static const float towerScale = 75.0f;
static const float enemyScale = 50.0f;
static const float missileScale = 75.0f;
static const float snowballScale = 25.0f;

void animateMissile(QCAR::Matrix44F& missileMatrix, int missileNumber);
void animateTower(QCAR::Matrix44F& towerMatrix);
void animateEnemy(QCAR::Matrix44F& enemyMatrix, int enemyNumber);
void makeMissile(int missileType, int missileNumber, float lx, float ly);
void updateMissileDefaultPos(int missileNumber, float lx, float ly);
void makeEnemy(int enemyType, int enemyNumber, int Delay);
void startLevel(int leveldone);
double getCurrentTime();
void DrawEnemy (QCAR::Matrix44F EnemyMatrix, QCAR::Matrix44F EnemyProjection, int x_offset, int y_offset);
void DrawTower (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int type);
void DrawArrow (QCAR::Matrix44F MissileMatrix, QCAR::Matrix44F MissileProjection, int x_offset, int y_offset, int type);
//TODO: fix tower/igloo & snowball/arrow into 1 function
void DrawIgloo (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int x_offset, int y_offset);
void DrawSnowball (QCAR::Matrix44F ArrowMatrix, QCAR::Matrix44F ArrowProjection, int x_offset, int y_offset);
void deinitAllMissiles ();
void getMarkerOffset(int trackedCornerID, int &x_offset, int &y_offset);
void convert2BoardCoord (int cornerID, QCAR::Matrix44F cornerMVM, QCAR::Matrix44F targetMVM, float &x, float &y);



void
displayMessage(char* message)
{
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
    jstring js = javaEnv->NewStringUTF(message);
    jmethodID method = javaEnv->GetMethodID(javaClass, "displayMessage", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}

void
toggleStartButton()
{
    // For this application, buttons are handled by the Android SDK
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that toggles the start button
    jmethodID method = javaEnv->GetMethodID(javaClass, "toggleStartButton", "()V");
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

            //1 Life Teapot
            /*
            QCAR::Matrix44F LifeMatrix1 = markerModelViewMatrix;
            QCAR::Matrix44F LifeProjection1;
            SampleUtils::translatePoseMatrix(-100.0f, 100.0f, 60.0f, &LifeMatrix1.data[0]);			
    		DrawEnemy(LifeMatrix1, LifeProjection1, x_offset, y_offset);
		    */

            //animate and draw the enemy units in reference to the marker position
            for (int i=0; i<MAX_NUM_ENEMIES; i++){
                QCAR::Matrix44F enemyMatrix = cornerMarkerModelViewMatrix;        
                animateEnemy(enemyMatrix, i); //animate the i-th enemy
                QCAR::Matrix44F enemyProjection;
                DrawEnemy(enemyMatrix, enemyProjection, x_offset, y_offset);
            }
        } //end enemy rendering
        
        //render towers and missiles
        //Note: do not draw the towers if a corner marker is not seen
        else if (trackedCornerID>=0 && marker->getMarkerId() >= 4 && marker->getMarkerId() < 4+MAX_NUM_TOWERS) {

            //get the tower number from the markers;
            int towerID = (marker->getMarkerId()) - 4;
            QCAR::Matrix44F towerMatrix = QCAR::Tool::convertPose2GLMatrix(trackable->getPose());
            QCAR::Matrix44F towerProjection;
            //draw the tower at the precise location of the marker
            
			//TODO: uncooment and take out the rest: Alton trying something out
			//DrawTower(towerMatrix, towerProjection, 0); 
            if (towerID < 2){
			    DrawTower(towerMatrix, towerProjection, 0); 
            }
            else{
                DrawTower(towerMatrix, towerProjection, 3); 
            }
			//end TODO
            
            //render the missile relative to the corner marker
            //1) find x, y board coordinates of the tower marker
            float x_board, y_board;
            convert2BoardCoord (trackedCornerID, cornerMarkerModelViewMatrix, towerMatrix, x_board,  y_board);

		    //initialize the missile if not init
            if (!missile[towerID].initialized){
    		    makeMissile (0, towerID, x_board, y_board);
            }
            //always update the original missile position (in case of glitches)
            updateMissileDefaultPos (towerID, x_board, y_board);

            //animate missile with respect to corner marker
            QCAR::Matrix44F missileMatrix = cornerMarkerModelViewMatrix;    
            getMarkerOffset(trackedCornerID, x_offset, y_offset);
            animateMissile(missileMatrix, towerID);
#ifdef USE_OPENGL_ES_1_1
#else
            QCAR::Matrix44F missileProjection;
            if (towerID < 2){
                DrawArrow(missileMatrix, missileProjection, x_offset, y_offset, 2); 
            }
            else{
                DrawArrow(missileMatrix, missileProjection, x_offset, y_offset, 4); 
            }

#endif

        }//end tower drawing

        // If this is our first time seeing the target, display a tip
        if (!displayedMessage) {
		    //showDeleteButton();
			counterprevTime = getCurrentTime();
			//TODO: move this at some point	
			for (int enemyNumber = 0; enemyNumber < numEnemies; enemyNumber++) {
			enemy[enemyNumber].prevTime = getCurrentTime();
			}
			if (startGame == 1)
			{
				startLevel(0);
			}
			displayMessage("LEVEL 1 START!");
            displayedMessage = true;
        }

    }

    //re-render every frame
    trackedCornerID=-1;


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

    //enemy initialization
//		strcpy("Zergling", enemy_type[0].name);
		enemy_type[0].type = 1;
		enemy_type[0].max_HP = 10.0f;
		enemy_type[0].X = 10000.0f;
		enemy_type[0].Y = -10000.0f;
		enemy_type[0].HP = enemy_type[0].max_HP;
		enemy_type[0].speed = 1.0f;
		enemy_type[0].defense = 1.0f;
	
//		strcpy("Speedy Gonzalez", enemy_type[0].name);
		enemy_type[1].type = 2;
		enemy_type[1].max_HP = 12.0f;
		enemy_type[1].X = 10000.0f;
		enemy_type[1].Y = -10000.0f;
		enemy_type[1].HP = enemy_type[1].max_HP;
		enemy_type[1].speed = 1.3f;
		enemy_type[1].defense = 1.0f;
		

    //missile initializations
//		strcpy("The Hulk", missile_type[0].name);
		missile_type[0].type = 1;
		missile_type[0].speed = 14;
		missile_type[0].cost = 3;
		missile_type[0].attack = 2.0f;
		
//		strcpy("Fast N' Weak", missile_type[1].name);
		missile_type[1].type = 2;
		missile_type[1].speed = 22;
		missile_type[1].cost = 2;
		missile_type[1].attack = 1.0f;
        
        //deinitialize all missiles
        deinitAllMissiles ();
		
		level[0].start = 0;
		level[0].end = 0;
		level[0].killCount = 0;
		level[1].start = 0;
		level[1].end = 0;
		level[1].killCount = 0;
		level[2].start = 0;
		level[2].end = 0;
		level[2].killCount = 0;

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

double getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double t = tv.tv_sec + tv.tv_usec/1000000.0;
    return t;
}

void animateMissile(QCAR::Matrix44F& missileMatrix, int missileNumber)
{
    float xdiff;
	float ydiff;
	float angle;
	float slope;
	int possibleTarget = 0;
	int possibleTargetDistance = 0;
	double time4 = getCurrentTime();  
	float dt4 = (float)(time4-missile[missileNumber].prevTime);          // from frame to frame
	missile[missileNumber].prevTime = time4;
			
	//find target if there is no target
	if (missile[missileNumber].currentTarget == -1 && numEnemies > 0) {
		missile[missileNumber].currentTarget = 0;
		xdiff = enemy[0].X-missile[missileNumber].defaultX;
		ydiff = enemy[0].Y-missile[missileNumber].defaultY;
		missile[missileNumber].currentTargetDistance = sqrt((xdiff*xdiff) + (ydiff*ydiff));
		for (possibleTarget = 1; possibleTarget < numEnemies; possibleTarget++) {
			xdiff = enemy[possibleTarget].X-missile[missileNumber].defaultX;
			ydiff = enemy[possibleTarget].Y-missile[missileNumber].defaultY;
			possibleTargetDistance = sqrt((xdiff*xdiff) + (ydiff*ydiff));
			if (possibleTargetDistance < missile[missileNumber].currentTargetDistance) {
				missile[missileNumber].currentTarget = possibleTarget;
				missile[missileNumber].currentTargetDistance = possibleTargetDistance;
			}
		}
	}
	
	//if there is a target
	if (missile[missileNumber].currentTarget != -1) {
		xdiff = enemy[missile[missileNumber].currentTarget].X-missile[missileNumber].X;
		ydiff = enemy[missile[missileNumber].currentTarget].Y-missile[missileNumber].Y;
		slope = ydiff/xdiff;
		angle = atan2(ydiff, xdiff) * 180 / 3.14159265;
		//x2 + y2 = 196 (move 14 units each second)
		//y/x = slope (move along slope)
		float xdist = sqrt(missile[missileNumber].speed*missile[missileNumber].speed/(1+(slope*slope)));
		float ydist = sqrt(missile[missileNumber].speed*missile[missileNumber].speed-(xdist*xdist));
		xdist = dt4*10.0f*xdist;
		ydist = dt4*10.0f*ydist;
		if (enemy[missile[missileNumber].currentTarget].X > missile[missileNumber].X)
			missile[missileNumber].X = missile[missileNumber].X + xdist;
		else
			missile[missileNumber].X = missile[missileNumber].X - xdist;
		if (enemy[missile[missileNumber].currentTarget].Y > missile[missileNumber].Y)
			missile[missileNumber].Y = missile[missileNumber].Y + ydist;
		else
			missile[missileNumber].Y = missile[missileNumber].Y - ydist;

		//if there is a hit
		if (missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X < 15 && missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X > -15 
		&& missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y < 15 && missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y > -15 ) {
			missile[missileNumber].X = missile[missileNumber].defaultX;
			missile[missileNumber].Y = missile[missileNumber].defaultY;
			enemy[missile[missileNumber].currentTarget].HP = enemy[missile[missileNumber].currentTarget].HP - ((missile[missileNumber].attack)/(enemy[missile[missileNumber].currentTarget].defense));

			//if hit kills enemy
			if (enemy[missile[missileNumber].currentTarget].HP <= 0.0f) {
				int temp = missile[missileNumber].currentTarget;
				enemy[missile[missileNumber].currentTarget].X = 10000.0f;
				enemy[missile[missileNumber].currentTarget].Y = -10000.0f;
				enemy[missile[missileNumber].currentTarget].HP = 0.0f;
				enemy[missile[missileNumber].currentTarget].count = -1;
				level[currentLevel].killCount = level[currentLevel].killCount + 1;
				if (level[currentLevel].killCount >=10) {
					level[currentLevel].end = 1;
					currentLevel++;
					startLevel(currentLevel);
				}
				for (int i = 0; i < 2; i++) { //FIXME: why is 2 here?
					if (missile[i].currentTarget == temp) {
						missile[i].X = missile[i].defaultX;
						missile[i].Y = missile[i].defaultY;
						missile[i].currentTarget = -1;
						missile[i].currentTargetDistance = 0;
					}
				}
			}
			//This makes it home to nearest. Without it, it "locks on" to an enemy
			// If (always attack nearest), reset the target after hit;
			//missile[missileNumber].currentTarget = -1;
		}
	
		//if target is too far away
		else if (missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X > 150 || missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X < -150 
		|| missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y > 150 || missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y < -150 ) {
			missile[missileNumber].X = missile[missileNumber].defaultX;
			missile[missileNumber].Y = missile[missileNumber].defaultY;
			missile[missileNumber].currentTarget = -1;
		}
	}
	SampleUtils::translatePoseMatrix(missile[missileNumber].X, missile[missileNumber].Y, 20.0f, &missileMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(angle, 0.0f, 0.0f, 1.0f, &missileMatrix.data[0]);
}

void animateTower(QCAR::Matrix44F& towerMatrix)
{
    static float rotateBowlAngle2 = 0.0f;
    static double prevTime2 = getCurrentTime();
    double time2 = getCurrentTime();             // Get real time difference
    float dt2 = (float)(time2-prevTime2);          // from frame to frame
    rotateBowlAngle2 += dt2 * 360.0f;     // Animate angle based on time
    SampleUtils::rotatePoseMatrix(rotateBowlAngle2, 0.0f, 0.0f, 1.0f, &towerMatrix.data[0]);
    prevTime2 = time2;
}

void animateEnemy(QCAR::Matrix44F& enemyMatrix, int enemyNumber)
{
float direction = 0.0f;	
	if (enemy[enemyNumber].count != -1) {
		double time4 = getCurrentTime();  
		float dt4 = (float)(time4-enemy[enemyNumber].prevTime);          // from frame to 
	
		if (enemy[enemyNumber].count > 950)
		{
			enemy[enemyNumber].count -= dt4*10.0f;
		}
		else if (enemy[enemyNumber].count <= 950 && enemy[enemyNumber].count >= 800 )
		{
			enemy[enemyNumber].count = 0;
			enemy[enemyNumber].X = 150.0f; //arbitrary initial positions
			enemy[enemyNumber].Y = -350.0f;
			enemy[enemyNumber].HP = enemy[enemyNumber].max_HP;
		}
		else {
			//enemy[enemyNumber].count += 1;
			if (enemy[enemyNumber].Y < 0.0f) {
				enemy[enemyNumber].Y += dt4 * 50.0f * enemy[enemyNumber].speed;
				direction = 90.0f;
			}
			else 
			{
				enemy[enemyNumber].X -= dt4 * 50.0f * enemy[enemyNumber].speed;
				direction = 180.0f;
			}
			if (enemy[enemyNumber].X < 0.0f) {
				lives = lives - 1;
				if (lives == 0 ) {
					for (int enemyNumber2 = 0; enemyNumber2 < numEnemies; enemyNumber2++) {
						enemy[enemyNumber2].X = 10000.0f;
						enemy[enemyNumber2].Y = -10000.0f;
						enemy[enemyNumber2].HP = 0.0f;
						enemy[enemyNumber2].count = -1;
					}
				}
				level[currentLevel].killCount = level[currentLevel].killCount + 1;
				if (level[currentLevel].killCount >=10) {
					level[currentLevel].end = 1;
					currentLevel++;
					startLevel(currentLevel);
				}
				enemy[enemyNumber].X = 10000.0f;
			}
        }
		enemy[enemyNumber].prevTime = time4;	
	}	
	SampleUtils::translatePoseMatrix(enemy[enemyNumber].X, enemy[enemyNumber].Y, 20.0f, &enemyMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(direction, 0.0f, 0.0f, 1.0f, &enemyMatrix.data[0]);

}

/********************
 * Initiate a new missile based on its type and location
 ********************/
void makeMissile(int missileType, int missileNumber, float lx, float ly)
{
    missile[missileNumber].initialized=true;
	missile[missileNumber].type = missile_type[missileType].type;
	missile[missileNumber].defaultX = lx;
	missile[missileNumber].defaultY = ly;
	missile[missileNumber].X = lx;
	missile[missileNumber].Y = ly;	
	missile[missileNumber].speed = missile_type[missileType].speed;
	missile[missileNumber].currentTarget = -1;
	missile[missileNumber].currentTargetDistance = -1;
	missile[missileNumber].cost = missile_type[missileType].cost;
	missile[missileNumber].attack = missile_type[missileType].attack;
	missile[missileNumber].prevTime = getCurrentTime();
}

void updateMissileDefaultPos(int missileNumber, float lx, float ly)
{
	missile[missileNumber].defaultX = lx;
	missile[missileNumber].defaultY = ly;
}


void makeEnemy(int enemyType, int enemyNumber, int delay)
{
	enemy[enemyNumber].type = enemy_type[enemyType].type;
	enemy[enemyNumber].X = enemy_type[enemyType].X;
	enemy[enemyNumber].Y = enemy_type[enemyType].Y;
	enemy[enemyNumber].max_HP = enemy_type[enemyType].max_HP;
	enemy[enemyNumber].HP = enemy_type[enemyType].max_HP;
	enemy[enemyNumber].speed = enemy_type[enemyType].speed;
	enemy[enemyNumber].defense = enemy_type[enemyType].defense;
	enemy[enemyNumber].count = delay;
    enemy[enemyNumber].prevTime = getCurrentTime();
}

void startLevel(int nextLevel)
{
if (nextLevel == 0)
	{
		makeEnemy (0, 0, 1000);
		makeEnemy (0, 1, 1020);
		makeEnemy (0, 2, 1040);
		makeEnemy (0, 3, 1060);
		makeEnemy (0, 4, 1080);
		makeEnemy (0, 5, 1100);
		makeEnemy (0, 6, 1120);
		makeEnemy (0, 7, 1140);
		makeEnemy (0, 8, 1160);
		makeEnemy (0, 9, 1180);
		//stuff isnt initiated at this point
		//displayMessage("LEVEL 1 START!");
		level[0].start = 1;
	}

//TODO: loop this lulz
	if (nextLevel == 1)
	{
		makeEnemy (1, 0, 1000);
		makeEnemy (1, 1, 1015);
		makeEnemy (1, 2, 1030);
		makeEnemy (1, 3, 1045);
		makeEnemy (1, 4, 1060);
		makeEnemy (1, 5, 1075);
		makeEnemy (1, 6, 1090);
		makeEnemy (1, 7, 1105);
		makeEnemy (1, 8, 1120);
		makeEnemy (1, 9, 1135);
		displayMessage("LEVEL 2 START!");
		level[1].start = 1;
	}
	
	if (nextLevel == 2)
	{
		makeEnemy (1, 0, 1000);
		makeEnemy (1, 1, 1010);
		makeEnemy (1, 2, 1020);
		makeEnemy (1, 3, 1030);
		makeEnemy (1, 4, 1040);
		makeEnemy (1, 5, 1100);
		makeEnemy (1, 6, 1105);
		makeEnemy (1, 7, 1110);
		makeEnemy (1, 8, 1115);
		makeEnemy (1, 9, 1120);
		displayMessage("LEVEL 3 START!");
		level[2].start = 1;
	}
		if (nextLevel == 3)
	{
		/*makeEnemy (1, 0, 1000);
		makeEnemy (1, 1, 1010);
		makeEnemy (1, 2, 1020);
		makeEnemy (1, 3, 1030);
		makeEnemy (1, 4, 1040);
		makeEnemy (1, 5, 1050);
		makeEnemy (1, 6, 1060);
		makeEnemy (1, 7, 1070);
		makeEnemy (1, 8, 1080);
		makeEnemy (1, 9, 1090);*/
		displayMessage("You beat the game!");
		//level[2].start = 1;
	}
}

void DrawEnemy (QCAR::Matrix44F EnemyMatrix, QCAR::Matrix44F EnemyProjection, int x_offset, int y_offset) {
	struct graphics_arrays horse_animate_array = get_graphics_stats (enemyFrameCounter, 1);
	const Texture* const thisTexture = textures[1];
	
    //offset the object based on corner marker in view
    SampleUtils::translatePoseMatrix(x_offset, y_offset, 0, &EnemyMatrix.data[0]);			


	SampleUtils::scalePoseMatrix(enemyScale, enemyScale, enemyScale, &EnemyMatrix.data[0]);
    SampleUtils::multiplyMatrix(&projectionMatrix.data[0],&EnemyMatrix.data[0], &EnemyProjection.data[0]);
    glUseProgram(shaderProgramID);
    glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) horse_animate_array.Verts);
    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) horse_animate_array.Normals);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, (const GLvoid*) horse_animate_array.TexCoords); 
    glEnableVertexAttribArray(vertexHandle);
    glEnableVertexAttribArray(normalHandle);
    glEnableVertexAttribArray(textureCoordHandle);      
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&EnemyProjection.data[0] );
    glDrawArrays(GL_TRIANGLES, 0, (int)*horse_animate_array.NumVerts);
    SampleUtils::checkGlError("ImageTargets renderFrame");
}

void DrawTower (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int type) {
	const Texture* const thisTexture = textures[type];
	//Castle = 0, Igloo = 3

    //FIXME: Model base not at Z=0?
     SampleUtils::translatePoseMatrix(0 ,0, 50.0f, &TowerMatrix.data[0]);


    SampleUtils::scalePoseMatrix(towerScale, towerScale, towerScale, &TowerMatrix.data[0]);
    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &TowerMatrix.data[0], &TowerProjection.data[0]);
    glUseProgram(shaderProgramID);
	if (type == 0) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, towerVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, towerNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, towerTexCoords);
	}
	else if (type == 3) {
		glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooVerts);
		glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooNormals);
		glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, iglooTexCoords);
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
	SampleUtils::checkGlError("ImageTargets renderFrame");
}
/*
void DrawIgloo (QCAR::Matrix44F TowerMatrix, QCAR::Matrix44F TowerProjection, int x_offset, int y_offset) {
	const Texture* const thisTexture = textures[3];
    //FIXME: Model base not at Z=0?
     SampleUtils::translatePoseMatrix(0 ,0, 50.0f, &TowerMatrix.data[0]);
    SampleUtils::scalePoseMatrix(towerScale, towerScale, towerScale, &TowerMatrix.data[0]);
    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &TowerMatrix.data[0], &TowerProjection.data[0]);
    glUseProgram(shaderProgramID);
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooVerts);
    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, iglooNormals);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, iglooTexCoords);
    glEnableVertexAttribArray(vertexHandle);
	glEnableVertexAttribArray(normalHandle);
	glEnableVertexAttribArray(textureCoordHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&TowerProjection.data[0] );
    glDrawArrays(GL_TRIANGLES, 0, iglooNumVerts);
	SampleUtils::checkGlError("ImageTargets renderFrame");
}
*/

void DrawArrow (QCAR::Matrix44F MissileMatrix, QCAR::Matrix44F MissileProjection, int x_offset, int y_offset, int type) {
	struct graphics_arrays arrow_animate_array = get_graphics_stats (missileFrameCounter, 0);
	const Texture* const thisTexture = textures[type];
    
    //offset the object based on corner marker in view
    SampleUtils::translatePoseMatrix(x_offset, y_offset, 0, &MissileMatrix.data[0]);
	if (type == 2) {
        SampleUtils::scalePoseMatrix(missileScale, missileScale, missileScale, &MissileMatrix.data[0]);
	}
	else if (type == 4) {
        SampleUtils::scalePoseMatrix(snowballScale, snowballScale, snowballScale, &MissileMatrix.data[0]);
    }
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
/*
void DrawSnowball (QCAR::Matrix44F ArrowMatrix, QCAR::Matrix44F ArrowProjection, int x_offset, int y_offset) {
	const Texture* const thisTexture = textures[4];
    

    //offset the object based on corner marker in view
    SampleUtils::translatePoseMatrix(x_offset, y_offset, 0, &ArrowMatrix.data[0]);

	SampleUtils::scalePoseMatrix(missileScale, missileScale, missileScale, &ArrowMatrix.data[0]);
    SampleUtils::multiplyMatrix(&projectionMatrix.data[0], &ArrowMatrix.data[0], &ArrowProjection.data[0]);
    glUseProgram(shaderProgramID);
	glVertexAttribPointer(vertexHandle, 3, GL_FLOAT, GL_FALSE, 0, snowballVerts);
    glVertexAttribPointer(normalHandle, 3, GL_FLOAT, GL_FALSE, 0, snowballNormals);
    glVertexAttribPointer(textureCoordHandle, 2, GL_FLOAT, GL_FALSE, 0, snowballTexCoords);
    glEnableVertexAttribArray(vertexHandle);
	glEnableVertexAttribArray(normalHandle);
	glEnableVertexAttribArray(textureCoordHandle);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
    glUniformMatrix4fv(mvpMatrixHandle, 1, GL_FALSE, (GLfloat*)&ArrowProjection.data[0] );
    glDrawArrays(GL_TRIANGLES, 0, snowballNumVerts);
	SampleUtils::checkGlError("ImageTargets renderFrame");
}
*/

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

//de-initislize all missiles
void deinitAllMissiles (){
    for (int i=0; i<MAX_NUM_TOWERS; i++){
        missile[i].initialized=false;
    }
}

#ifdef __cplusplus
}
#endif
