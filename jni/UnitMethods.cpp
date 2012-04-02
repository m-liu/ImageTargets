/*==============================================================================
            Copyright (c) 2012 Team Rickroll'd
            
@file 
    UnitDB.cpp

@brief
    Unit initialization methods

==============================================================================*/

#include "UnitMethods.h"

/******************
 * Get current time
 ******************/
double getCurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    double t = tv.tv_sec + tv.tv_usec/1000000.0;
    return t;
}


/********************
 * Creates a new enemy unit
 ********************/
void makeEnemy(int enemyType, int enemyNumber, int delay)
{
	enemy[enemyNumber].type = enemy_type[enemyType].type;
	enemy[enemyNumber].texture = enemy_type[enemyType].texture;
	//strcpy(enemy[enemyNumber].name, enemy_type[enemyType].name);
	enemy[enemyNumber].X = enemy_type[enemyType].X;
	enemy[enemyNumber].Y = enemy_type[enemyType].Y;
	enemy[enemyNumber].direction = 90.0f;
	enemy[enemyNumber].max_HP = enemy_type[enemyType].max_HP;
	enemy[enemyNumber].HP = enemy_type[enemyType].max_HP;
	enemy[enemyNumber].speed = enemy_type[enemyType].speed;
	enemy[enemyNumber].defense = enemy_type[enemyType].defense;
	enemy[enemyNumber].score = enemy_type[enemyType].score;
	enemy[enemyNumber].deploydelay = delay;
	enemy[enemyNumber].deployed = false;
	enemy[enemyNumber].dead = false;
    enemy[enemyNumber].prevTime = getCurrentTime();
	enemy[enemyNumber].section = 0;
}

/********************
 * Initiate a new missile based on its type and location
 ********************/
void makeMissile(int missileType, int missileNumber, float lx, float ly)
{
    missile[missileNumber].initialized = true;
	missile[missileNumber].type = missile_type[missileType].type;
	missile[missileNumber].texture = missile_type[missileType].texture;
	missile[missileNumber].defaultX = lx;
	missile[missileNumber].defaultY = ly;
	missile[missileNumber].X = lx;
	missile[missileNumber].Y = ly;	
	missile[missileNumber].angle = 0.0f;
	missile[missileNumber].speed = missile_type[missileType].speed;
	missile[missileNumber].currentTarget = -1;
	missile[missileNumber].currentTargetDistance = -1;
	missile[missileNumber].scale = missile_type[missileType].scale;
	missile[missileNumber].cost = missile_type[missileType].cost;
	missile[missileNumber].attack = missile_type[missileType].attack;
	missile[missileNumber].stunrate = missile_type[missileType].stunrate;
	missile[missileNumber].prevTime = getCurrentTime();
	missile[missileNumber].prevShotTime = getCurrentTime();
	missile[missileNumber].waitShotTime = missile_type[missileType].waitShotTime;
	missile[missileNumber].updatedShotTime = false;
}

void makeTower(int towerType, int towerNumber)
{
	tower[towerNumber].type = tower_type[towerType].type;
	tower[towerNumber].texture = tower_type[towerType].texture;
	tower[towerNumber].missiletype = tower_type[towerType].missiletype;
    tower[towerNumber].lift = tower_type[towerType].lift;
    tower[towerNumber].scale = tower_type[towerType].scale;
    tower[towerNumber].rotate = tower_type[towerType].rotate;
	tower[towerNumber].upgradeCost = missile_type[towerType%3].cost + 1;
	tower[towerNumber].initialized = true;
	tower[towerNumber].upgradeLevel = 1;
	tower[towerNumber].boardX = -100000;
	tower[towerNumber].boardY = -100000;
};

void upgradeTower(int towerNumber)
{
	int newTowerType = tower[towerNumber].type + 3; 
	tower[towerNumber].type = newTowerType;
	tower[towerNumber].texture = tower_type[newTowerType].texture;
	tower[towerNumber].missiletype = tower_type[newTowerType].missiletype;
    tower[towerNumber].lift = tower_type[newTowerType].lift;
    tower[towerNumber].scale = tower_type[newTowerType].scale;
	tower[towerNumber].rotate = tower_type[newTowerType].rotate;
	tower[towerNumber].upgradeLevel = 2;
	tower[towerNumber].upgradeCost = tower_type[newTowerType].upgradeCost;
	missile[towerNumber].type = missile_type[newTowerType].type;
	missile[towerNumber].texture = missile_type[newTowerType].texture;
	missile[towerNumber].angle = 0.0f;
	missile[towerNumber].speed = missile_type[newTowerType].speed;
	missile[towerNumber].currentTarget = -1;
	missile[towerNumber].currentTargetDistance = -1;
	missile[towerNumber].scale = missile_type[newTowerType].scale;
	missile[towerNumber].cost = missile_type[newTowerType].cost;
	missile[towerNumber].attack = missile_type[newTowerType].attack;
	missile[towerNumber].stunrate = missile_type[newTowerType].stunrate;
	missile[towerNumber].prevTime = getCurrentTime();
};

void deleteTower(int towerNumber)
{
	tower[towerNumber].initialized = false;
	missile[towerNumber].initialized = false;
}

/********************
 * Initializes the DB and the unit stats
 ********************/
void initEnemy (int type, int texture, float max_HP, float speed, float defense, float score) {
	enemy_type[type].type = type;
	enemy_type[type].texture = texture;
    enemy_type[type].max_HP = max_HP*currentDiff;
    enemy_type[type].speed = speed;
    enemy_type[type].defense = defense;
	enemy_type[type].score = score;
}

void initMissile (int type, int texture, float speed, int cost, float scale, float attack, float stunrate, float waitShotTime) {
	missile_type[type].type = type;
	missile_type[type].texture = texture;
    missile_type[type].speed = speed;
    missile_type[type].cost = cost;
    missile_type[type].attack = attack;
	missile_type[type].scale = scale;
	missile_type[type].stunrate = stunrate;
	missile_type[type].waitShotTime = waitShotTime;
}

void initTower (int type, int texture, int missiletype, float lift, float scale, float rotate, float upgradeCost) {
	tower_type[type].type = type;
	tower_type[type].texture = texture;
	tower_type[type].missiletype = missiletype;
    tower_type[type].lift = lift;
    tower_type[type].scale = scale;
    tower_type[type].rotate = rotate;
	tower_type[type].initialized = false;
	tower_type[type].upgradeLevel = 0;
	tower_type[type].boardX = 0;
	tower_type[type].boardY = 0;
	tower_type[type].upgradeCost = upgradeCost;
};
 
void initUnitDB () {

/*********************************************************************************
 *  ______________________________________________________________________________
 * |                                                                             |
 * |                               TABLE OF ENEMIES                              |
 * |_____________________________________________________________________________|
 * |   |         |                    |        |           |           |         |
 * | # | Texture |        Name        | Max HP |   Speed   |  Defense  |  Score  |
 * |___|_________|____________________|________|___________|___________|_________|
 * | 0 |    1    | Cow                |   150  |    1.2    |    1.0    |    1    |
 * | 1 |    5    | Zombie             |   200  |    1.0    |    1.0    |    2    |
 * | 2 |    6    | Tank               |   250  |    1.5    |    1.0    |    3    |
 * | 3 |    7    | Spaceship          |   300  |    1.0    |    1.0    |    4    |
 * | 4 |    1    | Cow2               |   350  |    1.0    |    2.0    |    5    |
 * | 5 |    5    | Zombie2            |   400  |    1.0    |    1.0    |    6    |
 * | 6 |    6    | Tank2              |   500  |    2.0    |    1.0    |    7    |
 * | 7 |    7    | Spaceship2         |   350  |    1.0    |    2.0    |    5    |
 * | 8 |    1    | Cow3               |   400  |    1.0    |    1.0    |    6    |
 * | 9 |    5    | Zombie3            |   500  |    2.0    |    1.0    |    7    |
 * |___|_________|____________________|________|___________|___________|_________|
 *
 *********************************************************************************/
 
    //enemy initialization
    strcpy(enemy_type[0].name, "Cow");
	initEnemy(0, 1, 100.0f, 1.2f, 1.0f, 1.0f);
	strcpy(enemy_type[1].name, "Zombie");
	initEnemy(1, 5, 140.0f, 1.0f, 1.0f, 1.0f);
	strcpy(enemy_type[2].name, "Tank");
	initEnemy(2, 6, 180.0f, 1.2f, 1.5f, 1.0f);	
	strcpy(enemy_type[3].name, "Spaceship");
	initEnemy(3, 7, 220.0f, 1.7f, 1.0f, 1.0f);
	strcpy(enemy_type[4].name, "HeadlessCow3");
	initEnemy(4, 1, 260.0f, 1.2f, 1.0f, 2.0f);
	strcpy(enemy_type[5].name, "Zombie3");
	initEnemy(5, 5, 300.0f, 1.0f, 1.0f, 2.0f);
	strcpy(enemy_type[6].name, "HeadlessCow4");
	initEnemy(6, 6, 300.0f, 1.3f, 1.2f, 2.0f);
	strcpy(enemy_type[7].name, "HeadlessCow3");
	initEnemy(7, 7, 300.0f, 1.5f, 1.4f, 2.0f);
	strcpy(enemy_type[8].name, "Zombie3");
	initEnemy(8, 1, 800.0f, 0.5f, 1.0f, 3.0f);
	strcpy(enemy_type[9].name, "HeadlessCow4");
	initEnemy(9, 5, 1000.0f, 0.5f, 1.0f, 3.0f);

	for (int i = 0; i < NUM_ENEMY_TYPES; i++) {
		enemy_type[i].X = 10000.0f;
		enemy_type[i].Y = -10000.0f;
		enemy_type[i].HP = enemy_type[i].max_HP;
		enemy_type[i].deploydelay = 0.0f;
		enemy_type[i].direction = 0.0f;
		enemy_type[i].deployed = false;
		enemy_type[i].dead = false;
		enemy_type[i].section = 0;
	}
	
	//missile initializations
	strcpy(missile_type[0].name, "Arrow");
	initMissile (0, 2, 15, 7, 40.0f, 25.0f, 1.0f, 0.9f);
	strcpy(missile_type[1].name, "Snowball");
	initMissile (1, 4, 14, 9, 10.0f, 20.0f, 0.90f, 1.1f);
	strcpy(missile_type[2].name, "Cannonball");
	initMissile (2, 10, 25, 15, 7.0f, 75.0f, 1.0f, 1.5f);
	strcpy(missile_type[3].name, "Arrow2");
	initMissile (3, 2, 20, 14, 50.0f, 50.0f, 1.0f, 0.9f);
	strcpy(missile_type[4].name, "Snowball2");
	initMissile (4, 4, 20, 18, 12.0f, 40.0f, 0.85f, 1.05f);
	strcpy(missile_type[5].name, "Cannonball2");
	initMissile (5, 10, 35, 30, 10.0f, 150.0f, 1.0f, 1.4f);
	strcpy(missile_type[6].name, "Arrow3");
	initMissile (6, 2, 25, 24, 40.0f, 75.0f, 1.0f, 0.9f);
	strcpy(missile_type[7].name, "Snowball3");
	initMissile (7, 4, 25, 30, 10.0f, 60.0f, 0.80f, 1.0f);
	strcpy(missile_type[8].name, "Cannonball3");
	initMissile (8, 10, 45, 48, 7.0f, 225.0f, 1.0f, 1.3f);
	strcpy(missile_type[9].name, "Arrow4");
	initMissile (9, 2, 30, 36, 50.0f, 100.0f, 1.0f, 0.9f);
	strcpy(missile_type[10].name, "Snowball4");
	initMissile (10, 4, 30, 44, 12.0f, 80.0f, 0.75f, 0.95f);
	strcpy(missile_type[11].name, "Cannonball4");
	initMissile (11, 10, 50, 68, 10.0f, 300.0f, 1.0f, 1.2f);
	
	//tower initializations
	strcpy(tower_type[0].name, "Castle");
	initTower (0, 0, 0, 50.0f, 60.0f, 0.0f, 8.0f);
	strcpy(tower_type[1].name, "Igloo");
	initTower (1, 3, 1, 25.0f, 50.0f, 0.0f, 10.0f);
	strcpy(tower_type[2].name, "Cannon");
	initTower (2, 9, 2, 10.0f, 50.0f, 90.0f, 16.0f);
	strcpy(tower_type[3].name, "Castle2");
	initTower (3, 21, 3, 50.0f, 65.0f, 0.0f, 10.0f);
	strcpy(tower_type[4].name, "Igloo2");
	initTower (4, 24, 4, 25.0f, 55.0f, 0.0f, 12.0f);
	strcpy(tower_type[5].name, "Cannon2");
	initTower (5, 27, 5, 10.0f, 55.0f, 90.0f, 17.0f);
	strcpy(tower_type[6].name, "Castle3");
	initTower (6, 22, 6, 50.0f, 70.0f, 0.0f, 12.0f);
	strcpy(tower_type[7].name, "Igloo3");
	initTower (7, 25, 7, 25.0f, 60.0f, 0.0f, 14.0f);
	strcpy(tower_type[8].name, "Cannon3");
	initTower (8, 28, 8, 10.0f, 60.0f, 90.0f, 18.0f);
	strcpy(tower_type[9].name, "Castle4");
	initTower (9, 23, 9, 50.0f, 75.0f, 0.0f, 0.0f);
	strcpy(tower_type[10].name, "Igloo4");
	initTower (10, 26, 10, 25.0f, 65.0f, 0.0f, 0.0f);
	strcpy(tower_type[11].name, "Cannon4");
	initTower (11, 29, 11, 10.0f, 65.0f, 90.0f, 0.0f);
	
	for (int i = 0; i < NUM_MISSILE_TYPES; i++) {
		missile_type[i].initialized = false;
		missile_type[i].X = -10000.0f;
		missile_type[i].Y = -10000.0f;
		missile_type[i].defaultX = -10000.0f;
		missile_type[i].defaultY = -10000.0f;
		missile_type[i].angle = 0.0f;
		missile_type[i].currentTarget = -1;
		missile_type[i].currentTargetDistance = -1;
		missile_type[i].prevTime = -1;
		missile_type[i].prevShotTime = -1;
		missile_type[i].updatedShotTime = false;
	}

    //Set all missiles to deinitialized state
    for (int i=0; i<MAX_NUM_TOWERS; i++){
        missile[i].initialized=false;
    }
}


//animate the missile, returns how many enemies killed
int animateMissile(int missileNumber)
{
    float xdiff;
	float ydiff;
	float slope;

	int possibleTarget = 0;
	int possibleTargetDistance = 0;
	double currentTime = getCurrentTime();  
	float timeDiff = (float)(currentTime-missile[missileNumber].prevTime);          // from frame to frame
	missile[missileNumber].prevTime = currentTime;

	//find target if there is no target by cycling through enemies
	if (missile[missileNumber].currentTarget == -1
		&& currentTime >= missile[missileNumber].prevShotTime + missile[missileNumber].waitShotTime) 
	{	
		missile[missileNumber].currentTarget = 0;
		xdiff = enemy[0].X-missile[missileNumber].defaultX;
		ydiff = enemy[0].Y-missile[missileNumber].defaultY;
		missile[missileNumber].currentTargetDistance = sqrt((xdiff*xdiff) + (ydiff*ydiff));
		for (possibleTarget = 1; possibleTarget < MAX_NUM_ENEMIES; possibleTarget++) {
			xdiff = enemy[possibleTarget].X-missile[missileNumber].defaultX;
			ydiff = enemy[possibleTarget].Y-missile[missileNumber].defaultY;
			possibleTargetDistance = sqrt((xdiff*xdiff) + (ydiff*ydiff));
			if (possibleTargetDistance < missile[missileNumber].currentTargetDistance) {
				missile[missileNumber].currentTarget = possibleTarget;
				missile[missileNumber].currentTargetDistance = possibleTargetDistance;
			}
		}
		if (missile[missileNumber].currentTargetDistance > MISSILE_RANGE) {
			missile[missileNumber].currentTarget = -1;
		}
	}
	
	//if there is a target, calculate distance and angle
	if (missile[missileNumber].currentTarget != -1 
		//Already attacking something
		&& (missile[missileNumber].updatedShotTime == true 
			//Missile shot delay
			|| currentTime >= missile[missileNumber].prevShotTime + missile[missileNumber].waitShotTime)) {

		xdiff = enemy[missile[missileNumber].currentTarget].X-missile[missileNumber].X;
		ydiff = enemy[missile[missileNumber].currentTarget].Y-missile[missileNumber].Y;
		missile[missileNumber].currentTargetDistance = sqrt((xdiff*xdiff) + (ydiff*ydiff));
		if (missile[missileNumber].currentTargetDistance > MISSILE_RANGE) {
			missile[missileNumber].X = missile[missileNumber].defaultX;
			missile[missileNumber].Y = missile[missileNumber].defaultY;
			missile[missileNumber].currentTarget = -1;
			missile[missileNumber].updatedShotTime = false;
		}
		else {
			if 	(missile[missileNumber].updatedShotTime == false) {
				
				if (missile[missileNumber].texture == 2) {
					soundflag_arrow = 1;
				}
				else if (missile[missileNumber].texture == 4) {
					soundflag_snowball = 1;
				}
				else if (missile[missileNumber].texture == 10) {
					soundflag_cannon = 1;
				}
				
				missile[missileNumber].updatedShotTime = true;
				missile[missileNumber].prevShotTime = currentTime;
			}
			
			slope = ydiff/xdiff;
			missile[missileNumber].angle = atan2(ydiff, xdiff) * 180 / 3.14159265;
			//x2 + y2 = 196 (move 14 units each second)
			//y/x = slope (move along slope)
			float xdist = sqrt(missile[missileNumber].speed*missile[missileNumber].speed/(1+(slope*slope)));
			float ydist = sqrt(missile[missileNumber].speed*missile[missileNumber].speed-(xdist*xdist));
			xdist = timeDiff*10.0f*xdist;
			ydist = timeDiff*10.0f*ydist;
			
			//move missile towards target
			if (enemy[missile[missileNumber].currentTarget].X > missile[missileNumber].X)
				missile[missileNumber].X = missile[missileNumber].X + xdist;
			else
				missile[missileNumber].X = missile[missileNumber].X - xdist;
			if (enemy[missile[missileNumber].currentTarget].Y > missile[missileNumber].Y)
				missile[missileNumber].Y = missile[missileNumber].Y + ydist;
			else
				missile[missileNumber].Y = missile[missileNumber].Y - ydist;
		
			//if target is too far away, reset the target
			xdiff = enemy[missile[missileNumber].currentTarget].X-missile[missileNumber].X;
			ydiff = enemy[missile[missileNumber].currentTarget].Y-missile[missileNumber].Y;
			missile[missileNumber].currentTargetDistance = sqrt((xdiff*xdiff) + (ydiff*ydiff));
					
			checkMissileContact(missileNumber);
		}
	}

    return 1;
}

void animateMissileMatrix(QCAR::Matrix44F& missileMatrix, int missileNumber, int x_offset, int y_offset) {
//offset the object based on corner marker in view and position
	SampleUtils::translatePoseMatrix(missile[missileNumber].X + x_offset, missile[missileNumber].Y + y_offset, 0.0f, &missileMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(missile[missileNumber].angle, 0.0f, 0.0f, 1.0f, &missileMatrix.data[0]);
	SampleUtils::scalePoseMatrix(missile[missileNumber].scale, missile[missileNumber].scale, missile[missileNumber].scale, &missileMatrix.data[0]);
}

int checkMissileContact(int missileNumber)
{

	    int enemiesKilled=0;
		//if missile is close, there may be a hit and missile is used up
		if (missile[missileNumber].currentTargetDistance < missile[missileNumber].speed*1.5) {
		LOG("HIT!");
			missile[missileNumber].updatedShotTime = false;
			missile[missileNumber].X = missile[missileNumber].defaultX;
			missile[missileNumber].Y = missile[missileNumber].defaultY;
			enemy[missile[missileNumber].currentTarget].HP = enemy[missile[missileNumber].currentTarget].HP - ((missile[missileNumber].attack)/(enemy[missile[missileNumber].currentTarget].defense));
			enemy[missile[missileNumber].currentTarget].speed *= missile[missileNumber].stunrate;
			
			//if hit damages enemy enough, enemy is killed and and kill count is increased
			if (enemy[missile[missileNumber].currentTarget].HP <= 0.0f) {
				soundflag_coin = 1;
				int temp = missile[missileNumber].currentTarget;
				enemy[missile[missileNumber].currentTarget].X = 10000.0f;
				enemy[missile[missileNumber].currentTarget].Y = -10000.0f;
				enemy[missile[missileNumber].currentTarget].HP = 0.0f;
				enemy[missile[missileNumber].currentTarget].dead = true;
				
				currentScore += enemy[missile[missileNumber].currentTarget].score*100;
				currentZen += enemy[missile[missileNumber].currentTarget].score;

				displayScore(currentScore);
				displayZen(currentZen);
				level[currentLevel].killCount = level[currentLevel].killCount + 1;

				//if other missiles are aiming at this enemy, reset their target
				for (int i = 0; i < MAX_NUM_TOWERS; i++) {
					if (missile[i].currentTarget == temp) {
						missile[i].X = missile[i].defaultX;
						missile[i].Y = missile[i].defaultY;
						missile[i].updatedShotTime = false;
						missile[i].currentTarget = -1;
						missile[i].currentTargetDistance = 0;
					}
				}
				
				//if enough enemies are killed, new level is started
				if (level[currentLevel].killCount >=NUM_ENEMY_PER_ROUND) {
					
					//soundeffect when level is complete
					soundflag_level = 1;
					
					level[currentLevel].end = 1;
					currentLevel++;
					char levelString[20];
					sprintf (levelString, "%d", currentLevel);
					char emessage[80];
					if (currentLevel != NUM_LEVELS) {
					currentZen = currentZen + currentLevel*3;
					displayZen(currentZen);
						sprintf (emessage, "Reached End of level %d! Press Next Level to continue!", currentLevel);
						displayMessage(emessage);
						//updateApplicationStatusEOL(levelString);
					}
					else {
						sprintf (emessage, "Reached the end of the game! Press End Game to continue!");
						displayMessage(emessage);
						//updateApplicationStatusWin();
					}
				}
				
				
				

                enemiesKilled++;

			}
			//This makes it home to nearest. Without it, it "locks on" to an enemy
			// If (always attack nearest), reset the target after hit;
			//missile[missileNumber].currentTarget = -1;
		}
return enemiesKilled;
}


//animate the tower
void animateTower(QCAR::Matrix44F& towerMatrix,  int mID)
{
    SampleUtils::translatePoseMatrix(0 ,0, tower[mID].lift, &towerMatrix.data[0]);
	if (tower[mID].rotate != 0.0f) {
		SampleUtils::rotatePoseMatrix(missile[mID].angle + tower[mID].rotate, 0.0f, 0.0f, 1.0f, &towerMatrix.data[0]);
	}
    SampleUtils::scalePoseMatrix(tower[mID].scale, tower[mID].scale, tower[mID].scale, &towerMatrix.data[0]);
}



//animate the enemy
void animateEnemy(int enemyNumber)
{	
	if (enemy[enemyNumber].dead == false) {
		double currentTime = getCurrentTime();  
		float timeDiff = (float)(currentTime-enemy[enemyNumber].prevTime);          // from frame to 
	
		if (!enemy[enemyNumber].deployed && enemy[enemyNumber].deploydelay > 0)
		{
			enemy[enemyNumber].deploydelay -= timeDiff*10.0f;
		}
		else if (!enemy[enemyNumber].deployed)
		{
			enemy[enemyNumber].deploydelay = 0;
			if (stageType != 3) {
				enemy[enemyNumber].X = 7*TILE_SIZE; //initial positions
				enemy[enemyNumber].Y = -7*TILE_SIZE;
			}
			else if (stageType == 3) {
				enemy[enemyNumber].X = 3*TILE_SIZE; //initial positions
				enemy[enemyNumber].Y = -4*TILE_SIZE;
			}
			enemy[enemyNumber].direction = 90.0f;
			enemy[enemyNumber].HP = enemy[enemyNumber].max_HP;
			enemy[enemyNumber].deployed = true;
		}
		else {
			moveEnemy(enemyNumber, timeDiff);
			
			bool endpath = false;
			if (stageType == 1) {
				endpath = enemy[enemyNumber].X < 0.0f;
			}
			if (stageType == 2) {
				endpath = enemy[enemyNumber].X == 0.0f && enemy[enemyNumber].Y > 0.0f;
			}
			if (stageType == 3) {
				endpath = enemy[enemyNumber].X < 0.0f;
			}
			if (endpath) {
				currentLives = currentLives - 1;
				displayLives(currentLives);
				if (currentLives <= 0 ) {
					gameOver();
				}
				else {
				level[currentLevel].killCount = level[currentLevel].killCount + 1;
				removeEnemy(enemyNumber);
				if (level[currentLevel].killCount >= NUM_ENEMY_PER_ROUND) {
					soundflag_level = 1;
					level[currentLevel].end = 1;
					currentLevel++;
					char levelString[20];
					sprintf (levelString, "%d", currentLevel);
					char emessage[80];
					if (currentLevel != NUM_LEVELS) {
						sprintf (emessage, "Reached End of level %d! Press Next Level to continue!", currentLevel);
						displayMessage(emessage);
						//updateApplicationStatusEOL(levelString);
					}
					else {
						sprintf (emessage, "Reached the end of the game! Press End Game to continue!");
						displayMessage(emessage);
						//updateApplicationStatusWin();
					}
				}
				}
			}
        }
		enemy[enemyNumber].prevTime = currentTime;	
	}		

}


void animateEnemyMatrix(QCAR::Matrix44F& enemyMatrix, QCAR::Matrix44F& HPMatrix, int enemyNumber, int x_offset, int y_offset) {
    //offset the object based on corner marker in view
	SampleUtils::translatePoseMatrix(enemy[enemyNumber].X + x_offset, enemy[enemyNumber].Y + y_offset, ENEMY_LIFT, &enemyMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(enemy[enemyNumber].direction, 0.0f, 0.0f, 1.0f, &enemyMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(90.0f, 1.0f, 0.0f, 0.0f, &enemyMatrix.data[0]);
	SampleUtils::scalePoseMatrix(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE, &enemyMatrix.data[0]);
	SampleUtils::translatePoseMatrix(enemy[enemyNumber].X + x_offset, enemy[enemyNumber].Y + y_offset, HP_LIFT, &HPMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(enemy[enemyNumber].direction, 0.0f, 0.0f, 1.0f, &HPMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(270.0f, 1.0f, 0.0f, 0.0f, &HPMatrix.data[0]);
	SampleUtils::scalePoseMatrix(HP_SCALE, HP_SCALE, HP_SCALE, &HPMatrix.data[0]);
}

//update missile positions
void updateMissileDefaultPos(int missileNumber, float lx, float ly)
{
	missile[missileNumber].defaultX = lx;
	missile[missileNumber].defaultY = ly;
}

void removeEnemy (int enemyNumber)
{
	enemy[enemyNumber].X = 10000.0f;
	enemy[enemyNumber].Y = -10000.0f;
	enemy[enemyNumber].HP = 0.0f;
	enemy[enemyNumber].deploydelay = -1;
	enemy[enemyNumber].dead = true;
}

void removeTower (int towerNumber)
{
	tower[towerNumber].initialized = false;
	missile[towerNumber].initialized = false;
}


void gameOver ()
{
	currentLevel = 0;
	currentLives = 20;

	currentScore = 0;
	currentZen = 20;

	currentDiff = 1;
	stageType = 1;
	startGame=0;
	seeTargets=0;
	for (int towerNumber2 = 0; towerNumber2 < MAX_NUM_TOWERS; towerNumber2++) {
		removeTower(towerNumber2);
	}
	for (int enemyNumber2 = 0; enemyNumber2 < MAX_NUM_ENEMIES; enemyNumber2++) {
		removeEnemy(enemyNumber2);
	}
	currentLevel = 11;
	soundflag_level = 1;
	char emessage[80];
	sprintf (emessage, "GAME OVER! Press End Game to continue!");
	displayMessage(emessage);
	//updateApplicationStatusGameOver();
}

void moveEnemy (int enemyNumber, float timeDiff)
{
	//Level1: basic
	if (stageType == 1) {
		if (enemy[enemyNumber].Y < 0 * TILE_SIZE) {
			enemy[enemyNumber].X = 7 * TILE_SIZE;
			enemy[enemyNumber].Y += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 90.0f; //up
		}
		else
		{
			enemy[enemyNumber].Y = 0 * TILE_SIZE;
			enemy[enemyNumber].X -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 180.0f; //left
		}
	}
	
	//Level2: S-shaped
	else if (stageType == 2) {
		if (enemy[enemyNumber].section == 0 && enemy[enemyNumber].X == 7 * TILE_SIZE && enemy[enemyNumber].Y < 0 * TILE_SIZE) {
			enemy[enemyNumber].Y += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 90.0f; //up
		}
		else if ((enemy[enemyNumber].section == 0 || enemy[enemyNumber].section == 1) && enemy[enemyNumber].X > 4 * TILE_SIZE){
			enemy[enemyNumber].section = 1;
			enemy[enemyNumber].Y = 0 * TILE_SIZE;
			enemy[enemyNumber].X -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 180.0f; //left
		}
		else if ((enemy[enemyNumber].section == 1 || enemy[enemyNumber].section == 2) && enemy[enemyNumber].Y > -7 * TILE_SIZE){
			enemy[enemyNumber].section = 2;
			enemy[enemyNumber].X = 4 * TILE_SIZE;
			enemy[enemyNumber].Y -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 270.0f; //down
		}
		else if ((enemy[enemyNumber].section == 2 || enemy[enemyNumber].section == 3) && enemy[enemyNumber].X > 0 * TILE_SIZE){
			enemy[enemyNumber].section = 3;
			enemy[enemyNumber].Y = -7 * TILE_SIZE;
			enemy[enemyNumber].X -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 180.0f; //left
		}
		else
		{
			enemy[enemyNumber].section = 4;
			enemy[enemyNumber].X = 0 * TILE_SIZE;
			enemy[enemyNumber].Y += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 90.0f; //up
		}
	}
	
	//Level3: spiral
	else if (stageType == 3) {
		if (enemy[enemyNumber].section == 0 && enemy[enemyNumber].X <= 5 * TILE_SIZE) {
			enemy[enemyNumber].Y = -4 * TILE_SIZE;
			enemy[enemyNumber].X += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 0.0f; //right
		}
		else if ((enemy[enemyNumber].section == 0 || enemy[enemyNumber].section == 1) && enemy[enemyNumber].Y < -2 * TILE_SIZE){
			enemy[enemyNumber].section = 1;
			enemy[enemyNumber].Y += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].X = 5 * TILE_SIZE;
			enemy[enemyNumber].direction = 90.0f; //up
		}
		else if ((enemy[enemyNumber].section == 1 || enemy[enemyNumber].section == 2) && enemy[enemyNumber].X > 1 * TILE_SIZE){
			enemy[enemyNumber].section = 2;
			enemy[enemyNumber].Y = -2 * TILE_SIZE;
			enemy[enemyNumber].X -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 180.0f; //left
		}
		else if ((enemy[enemyNumber].section == 2 || enemy[enemyNumber].section == 3) && enemy[enemyNumber].Y > -7 * TILE_SIZE){
			enemy[enemyNumber].section = 3;
			enemy[enemyNumber].X = 1 * TILE_SIZE;
			enemy[enemyNumber].Y -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 270.0f; //down
		}
		else if ((enemy[enemyNumber].section == 3 || enemy[enemyNumber].section == 4) && enemy[enemyNumber].X < 7 * TILE_SIZE){
			enemy[enemyNumber].section = 4;
			enemy[enemyNumber].Y = -7 * TILE_SIZE;
			enemy[enemyNumber].X += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 0.0f; //right
		}
		else if ((enemy[enemyNumber].section == 4 || enemy[enemyNumber].section == 5) && enemy[enemyNumber].Y < 0 * TILE_SIZE){
			enemy[enemyNumber].section = 5;
			enemy[enemyNumber].X = 7 * TILE_SIZE;
			enemy[enemyNumber].Y += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 90.0f; //up
		}
		else
		{
			enemy[enemyNumber].section = 6;
			enemy[enemyNumber].Y = 0 * TILE_SIZE;
			enemy[enemyNumber].X -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 180.0f; //left
		}
	}
	
	//default to basic
	else
	{
		if (enemy[enemyNumber].Y < 0 * TILE_SIZE) {
			enemy[enemyNumber].Y += timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 90.0f; //up
		}
		else
		{
			enemy[enemyNumber].Y = 0 * TILE_SIZE;
			enemy[enemyNumber].X -= timeDiff * ENEMY_MOVEMENT_SPEED * enemy[enemyNumber].speed;
			enemy[enemyNumber].direction = 180.0f; //left
		}
	}
}
