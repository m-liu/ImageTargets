/*==============================================================================
            Copyright (c) 2012 Team Rickroll'd
            
@file 
     LevelSystem.h

@brief
    Level system methods

==============================================================================*/

#ifndef _LEVELSYSTEM_H_
#define _LEVELSYSTEM_H_

#include "SampleUtils.h"
#include "GlobalDefs.h"
#include "UnitMethods.h"

//Global Level struct
extern Level level[NUM_LEVELS+1];
extern int currentLevel;
extern int currentLives;
//java objects
extern JNIEnv* javaEnv;
extern jobject javaObj;
extern jclass javaClass;

extern JNIEnv* javaEnv2;
extern jobject javaObj2;
extern jclass javaClass2;


//display a message
void displayMessage(char* message);
void displayScore(int score);
void displayZen(int zen);
void displayLives(int lives);

void updateApplicationStatusEOL(char* level);
void updateApplicationStatusGameOver();
void updateApplicationStatusWin();

//initislize the levels
void initLevels ();

//start the level
void startLevel(int nextLevel);


#endif
