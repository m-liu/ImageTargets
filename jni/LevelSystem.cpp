/*==============================================================================
            Copyright (c) 2012 Team Rickroll'd
            
@file 
    LevelSystem.cpp

@brief
    Level system methods

==============================================================================*/

#include "LevelSystem.h"

void
updateApplicationStatusEOL(char* level)
{
	//jstring js = javaEnv2->NewStringUTF(level);
    //jmethodID method = javaEnv2->GetMethodID(javaClass2, "updateEOL", "(Ljava/lang/String;)V");
    //javaEnv2->CallVoidMethod(javaObj2, method, js);
    //startLevel(currentLevel);
}

void
updateApplicationStatusGameOver()
{
    //jmethodID method = javaEnv2->GetMethodID(javaClass2, "updateGameOver", "()V");
    //javaEnv2->CallVoidMethod(javaObj2, method);
}

void
updateApplicationStatusWin()
{
   //jmethodID method = javaEnv2->GetMethodID(javaClass2, "updateWin", "()V");
   //javaEnv2->CallVoidMethod(javaObj2, method);
}

//display a message    
void displayMessage(char* message)
{
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
    jstring js = javaEnv->NewStringUTF(message);
    jmethodID method = javaEnv->GetMethodID(javaClass, "displayMessage", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}

//display a message    
void displayScore(int score)
{
	char scoreString[10];
	sprintf (scoreString, "%d", score);
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
	jstring js = javaEnv->NewStringUTF(scoreString);
    jmethodID method = javaEnv->GetMethodID(javaClass, "displayScore", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}

//display a message    
void displayZen(int zen)
{
	char zenString[10];
	sprintf (zenString, "%d", zen);
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
	jstring js = javaEnv->NewStringUTF(zenString);
    jmethodID method = javaEnv->GetMethodID(javaClass, "displayZen", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}

//display a message    
void displayLives(int lives)
{
	char livesString[10];
	sprintf (livesString, "%d", lives);
    // Use the environment and class stored in initNativeCallback
    // to call a Java method that displays a message via a toast
	jstring js = javaEnv->NewStringUTF(livesString);
    jmethodID method = javaEnv->GetMethodID(javaClass, "displayLives", "(Ljava/lang/String;)V");
    javaEnv->CallVoidMethod(javaObj, method, js);
}

//initialize the levels
void initLevels (){

    for (int i=0; i<NUM_LEVELS+1; i++){
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
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (0, i, (i+2)*30);
		}
		//stuff isnt initiated at this point
		displayMessage("LEVEL 1 START!");
		level[0].start = 1;
	}

	if (nextLevel == 1)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (1, i, (i+2)*25);
		}
		displayMessage("LEVEL 2 START!");
		level[1].start = 1;
	}
	
	if (nextLevel == 2)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (2, i, (i+2)*20);
		}
		displayMessage("LEVEL 3 START!");
		level[2].start = 1;
	}
	
	if (nextLevel == 3)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (3, i, (i+2)*20);
		}
		displayMessage("LEVEL 4 START!");
		level[3].start = 1;
	}
	
	if (nextLevel == 4)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (4, i, (i+2)*15);
		}
		displayMessage("LEVEL 5 START!");
		level[4].start = 1;
	}
	
	
	if (nextLevel == 5)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (5, i, (i+2)*15);
		}
		displayMessage("LEVEL 6 START!");
		level[5].start = 1;
	}
	
	if (nextLevel == 6)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (6, i, (i+2)*10);
		}
		displayMessage("LEVEL 7 START!");
		level[6].start = 1;
	}
	
	if (nextLevel == 7)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (7, i, (i+2)*10);
		}
	/*
		for (int i = 0; i < 5; i++) {
			makeEnemy (i, i, (i+2)*5);
		}
		for (int i = 5; i < 10; i++) {
			makeEnemy (i-5, i, (i+2)*5);
		}*/
		displayMessage("LEVEL 8 START!");
		level[7].start = 1;
	}
	
	if (nextLevel == 8)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (8, i, (i+2)*10);
		}
		displayMessage("LEVEL 9 START!");
		level[8].start = 1;
	}
	
	if (nextLevel == 9)
	{
		for (int i = 0; i < NUM_ENEMY_PER_ROUND; i++) {
			makeEnemy (9, i, (i+2)*10);
		}
		displayMessage("LEVEL 10 START!");
		level[9].start = 1;
	}
	
	if (nextLevel == 10)
	{

		displayMessage("You win bro.");
		
	}
}



