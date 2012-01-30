/*==============================================================================
            Copyright (c) 2012 Team Rickroll'd
            
@file 
    LevelSystem.cpp

@brief
    Level system methods

==============================================================================*/

#include "LevelSystem.h"

//display a message    
void displayMessage(char* message)
{
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
    jstring js = javaEnv->NewStringUTF(message);
    jmethodID method = javaEnv->GetMethodID(javaClass, "displayMessage", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}



//initialize the levels
void initLevels (){

    for (int i=0; i<NUM_LEVELS; i++){
    level[i].start = 0;
    level[i].end = 0;
    level[i].killCount = 0;
    }
}



//start the level
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
		displayMessage("LEVEL 1 START!");
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

		displayMessage("You beat the game!");
	}
}



