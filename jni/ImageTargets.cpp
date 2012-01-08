/*==============================================================================
            Copyright (c) 2010-2011 QUALCOMM Incorporated.
            All Rights Reserved.
            Qualcomm Confidential and Proprietary
            
@file 
    ImageTargets.cpp

@brief
    Sample for ImageTargets

==============================================================================*/


#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

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

#include "SampleUtils.h"
#include "Texture.h"
#include "CubeShaders.h"
#include "Teapot.h"

#ifdef __cplusplus
extern "C"
{
#endif

// Textures:
int textureCount                = 0;
Texture** textures              = 0;

// OpenGL ES 2.0 specific:
#ifdef USE_OPENGL_ES_2_0
unsigned int shaderProgramID    = 0;
GLint vertexHandle              = 0;
GLint normalHandle              = 0;
GLint textureCoordHandle        = 0;
GLint mvpMatrixHandle           = 0;
#endif

//**TEST**
typedef struct {
    GLfloat x;
    GLfloat y;
    GLfloat z;
} Vertex3D;


static inline Vertex3D Vertex3DMake(float inX, float inY, float inZ)
{
    Vertex3D ret;
    ret.x = inX;
    ret.y = inY;
    ret.z = inZ;
    return ret;
}


typedef struct {
    Vertex3D v1;
    Vertex3D v2;
    Vertex3D v3;
} Triangle3D;

static inline Triangle3D Triangle3DMake(Vertex3D inV1, Vertex3D inV2, Vertex3D inV3)
{
    Triangle3D ret;
    ret.v1 = inV1;
    ret.v2 = inV2;
    ret.v3 = inV3;
    return ret;
}
   Vertex3D    vertex1 = Vertex3DMake(0.0, 0.1, 0.0);
    Vertex3D    vertex2 = Vertex3DMake(0.5, 0.0, 0.0);
    Vertex3D    vertex3 = Vertex3DMake(0.0, 0.0, 0.5);
    Triangle3D  triangle = Triangle3DMake(vertex1, vertex2, vertex3);
    GLfloat aline[] = {0.0, 1.0, 0.0, 0.8, 0.0, 0.0};


// Screen dimensions:
unsigned int screenWidth        = 0;
unsigned int screenHeight       = 0;

// Indicates whether screen is in portrait (true) or landscape (false) mode
bool isActivityInPortraitMode   = false;

// The projection matrix used for rendering virtual objects:
QCAR::Matrix44F projectionMatrix;

// Constants:
static const float kObjectScale = 3.f;


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
    // Comment in to enable tracking of up to 2 targets simultaneously and
    // split the work over multiple frames:
    QCAR::setHint(QCAR::HINT_MAX_SIMULTANEOUS_IMAGE_TARGETS, 9);
    QCAR::setHint(QCAR::HINT_IMAGE_TARGET_MULTI_FRAME_ENABLED,2);
    QCAR::setHint(QCAR::HINT_IMAGE_TARGET_MILLISECONDS_PER_MULTI_FRAME, 5000);
}


JNIEXPORT void JNICALL
Java_com_qualcomm_QCARSamples_ImageTargets_ImageTargetsRenderer_renderFrame(JNIEnv *, jobject)
{
    //LOG("Java_com_qualcomm_QCARSamples_ImageTargets_GLRenderer_renderFrame");

    static GLfloat rotation = 1.0;
    glLoadIdentity();
    glRotatef(rotation, 0.0, 1.0, 0.0);
    // Define clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    // Clear color and depth buffer 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//LOG("rotation=%f", rotation);
    // Render video background:
    //QCAR::State state = QCAR::Renderer::getInstance().begin();
        
#ifdef USE_OPENGL_ES_1_1
    // Set GL11 flags:
    glEnableClientState(GL_VERTEX_ARRAY);
    //glEnableClientState(GL_NORMAL_ARRAY);
    //glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    //glEnable(GL_TEXTURE_2D);
    //glDisable(GL_LIGHTING);
        
#endif

    
    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);
    //LOG("&&& numtrack = %d", state.getNumTrackables () );
    //if (state.getNumActiveTrackables()>3){
    //    LOG("><><>< #trackables = %d", state.getNumActiveTrackables()); 
    //}
    //while (state.getNumActiveTrackables()!=4){return;};
    
    glColor4f(1.0, 0.0, 0.0, 1.0);
    glVertexPointer(3, GL_FLOAT, 0, &triangle);
    glDrawArrays(GL_TRIANGLES, 0, 9);
        
/*
    // Did we find any trackables this frame?
    for(int tIdx = 0; tIdx < state.getNumActiveTrackables(); tIdx++)
    {
        
        // Get the trackable:
        const QCAR::Trackable* trackable = state.getActiveTrackable(tIdx);
        QCAR::Matrix44F modelViewMatrix =
            QCAR::Tool::convertPose2GLMatrix(trackable->getPose());        
        


        // Choose the texture based on the target name:
        int textureIndex = (!strcmp(trackable->getName(), "qr4")) ? 0 : 1;
        const Texture* const thisTexture = textures[textureIndex];

#ifdef USE_OPENGL_ES_1_1
        // Load projection matrix:
        glMatrixMode(GL_PROJECTION);
        glLoadMatrixf(projectionMatrix.data);

        // Load model view matrix:
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(modelViewMatrix.data);
        glTranslatef(0.f, 0.f, kObjectScale);
        glScalef(kObjectScale, kObjectScale, kObjectScale);

        // Draw object:
        glBindTexture(GL_TEXTURE_2D, thisTexture->mTextureID);
        glTexCoordPointer(2, GL_FLOAT, 0, (const GLvoid*) &teapotTexCoords[0]);
        glVertexPointer(3, GL_FLOAT, 0, (const GLvoid*) &teapotVertices[0]);
        glNormalPointer(GL_FLOAT, 0,  (const GLvoid*) &teapotNormals[0]);
        glDrawElements(GL_TRIANGLES, NUM_TEAPOT_OBJECT_INDEX, GL_UNSIGNED_SHORT,
                       (const GLvoid*) &teapotIndices[0]);
#else
#endif


    }
    */
    //git test
   // glDisable(GL_DEPTH_TEST);

#ifdef USE_OPENGL_ES_1_1        
   // glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_VERTEX_ARRAY);
    //glDisableClientState(GL_NORMAL_ARRAY);
    //glDisableClientState(GL_TEXTURE_COORD_ARRAY);
#else
#endif
    //rotation+= 0.005;

    //QCAR::Renderer::getInstance().end();
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

    //glLoadIdentity();
    // Define clear color
    //glClearColor(0.0f, 0.0f, 0.0f, QCAR::requiresAlpha() ? 0.0f : 1.0f);
    //glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    /*
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
    */


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
