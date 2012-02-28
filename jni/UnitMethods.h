/*==============================================================================
            Copyright (c) 2012 Team Rickroll'd
            
@file 
    UnitDB.h

@brief
    Unit database and structs

==============================================================================*/

#ifndef _UNITMETHODS_H_
#define _UNITMETHODS_H_

// Includes:

//Includes
#include <jni.h>
#include <android/log.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <sys/time.h>
#include <math.h>

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
#include "GlobalDefs.h"
#include "LevelSystem.h"

extern EnemyUnit enemy[MAX_NUM_ENEMIES];
extern EnemyUnit enemy_type[NUM_ENEMY_TYPES];
extern MissileUnit missile[MAX_NUM_TOWERS];
extern MissileUnit missile_type[NUM_MISSILE_TYPES];
//Global Level struct
extern Level level[NUM_LEVELS];
extern int currentLevel;
extern int currentScore;
extern int currentZen;
extern int currentLives;
extern int stageType;


double getCurrentTime();
//Set all missiles to deinitialized state
void deinitAllMissiles ();

//Creates a new enemy unit
void makeEnemy(int enemyType, int enemyNumber, int Delay);

void initUnitDB () ;

//Initiate a new missile based on its type and location
void makeMissile(int missileType, int missileNumber, float lx, float ly);

int animateMissile(QCAR::Matrix44F& missileMatrix, int missileNumber, int x_offset, int y_offset);
int checkMissileContact(int missileNumber);
void animateTower(QCAR::Matrix44F& towerMatrix);
void animateEnemy(QCAR::Matrix44F& enemyMatrix, int enemyNumber, int x_offset, int y_offset);
void updateMissileDefaultPos(int missileNumber, float lx, float ly);
void removeEnemy (int enemyNumber);
void gameOver ();
void moveEnemy (int &x, int &y, int &direction, int speed, float timeDiff);

#endif // _UNITDB_H_
