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
    missile[missileNumber].initialized=true;
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
	missile[missileNumber].prevTime = getCurrentTime();
}

void makeTower(int towerType, int towerNumber)
{
	tower[towerNumber].type = tower_type[towerType].type;
	tower[towerNumber].texture = tower_type[towerType].texture;
	tower[towerNumber].missiletype = tower_type[towerType].missiletype;
    tower[towerNumber].lift = tower_type[towerType].lift;
    tower[towerNumber].scale = tower_type[towerType].scale;
    tower[towerNumber].rotate = tower_type[towerType].rotate;
	tower[towerNumber].initialized = true;
	tower[towerNumber].upgradeLevel = 1;
	//tower[towerNumber].boardX = 0.0f;
	//tower[towerNumber].boardY = 0.0f;
};

/********************
 * Initializes the DB and the unit stats
 ********************/
void initEnemy (int type, int texture, float max_HP, float speed, float defense, float score) {
	enemy_type[type].type = type;
	enemy_type[type].texture = texture;
    enemy_type[type].max_HP = max_HP;
    enemy_type[type].speed = speed;
    enemy_type[type].defense = defense;
	enemy_type[type].score = score;
}

void initMissile (int type, int texture, float speed, float cost, float scale, float attack) {
	missile_type[type].type = type;
	missile_type[type].texture = texture;
    missile_type[type].speed = speed;
    missile_type[type].cost = cost;
    missile_type[type].attack = attack;
	missile_type[type].scale = scale;
}

void initTower (int type, int texture, int missiletype, float lift, float scale, float rotate) {
	tower_type[type].type = type;
	tower_type[type].texture = texture;
	tower_type[type].missiletype = missiletype;
    tower_type[type].lift = lift;
    tower_type[type].scale = scale;
    tower_type[type].rotate = rotate;
	tower_type[type].initialized = 0;
	tower_type[type].upgradeLevel = 0;
	tower_type[type].boardX = 0.0f;
	tower_type[type].boardY = 0.0f;
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
	initEnemy(0, 1, 150.0f, 1.2f, 1.0f, 1.0f);
	strcpy(enemy_type[1].name, "Zombie");
	initEnemy(1, 5, 200.0f, 1.0f, 1.0f, 2.0f);
	strcpy(enemy_type[2].name, "Tank");
	initEnemy(2, 6, 250.0f, 1.5f, 1.0f, 3.0f);	
	strcpy(enemy_type[3].name, "Spaceship");
	initEnemy(3, 7, 300.0f, 1.0f, 1.0f, 4.0f);
	strcpy(enemy_type[4].name, "HeadlessCow3");
	initEnemy(4, 1, 350.0f, 1.0f, 2.0f, 5.0f);
	strcpy(enemy_type[5].name, "Zombie3");
	initEnemy(5, 5, 400.0f, 1.0f, 1.0f, 6.0f);
	strcpy(enemy_type[6].name, "HeadlessCow4");
	initEnemy(6, 6, 500.0f, 2.0f, 1.0f, 7.0f);
	strcpy(enemy_type[7].name, "HeadlessCow3");
	initEnemy(7, 7, 600.0f, 1.0f, 2.0f, 8.0f);
	strcpy(enemy_type[8].name, "Zombie3");
	initEnemy(8, 1, 700.0f, 1.0f, 1.0f, 9.0f);
	strcpy(enemy_type[9].name, "HeadlessCow4");
	initEnemy(9, 5, 1000.0f, 2.0f, 1.0f, 10.0f);

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
	
	//tower initializations
	strcpy(tower_type[0].name, "Castle");
	initTower (0, 0, 0, 50.0f, 60.0f, 0.0f);
	strcpy(tower_type[1].name, "Igloo");
	initTower (1, 3, 1, 0.0f, 50.0f, 0.0f);
	strcpy(tower_type[2].name, "Cannon");
	initTower (2, 9, 2, 0.0f, 50.0f, 90.0f);
	strcpy(tower_type[3].name, "Castle2");
	initTower (3, 0, 3, 50.0f, 75.0f, 0.0f);
	strcpy(tower_type[4].name, "Igloo2");
	initTower (4, 3, 4, 0.0f, 50.0f, 0.0f);
	strcpy(tower_type[5].name, "Cannon2");
	initTower (5, 9, 5, 0.0f, 75.0f, 90.0f);
	
    //missile initializations
	strcpy(missile_type[0].name, "Arrow");
	initMissile (0, 2, 14, 3, 40.0f, 20.0f);
	strcpy(missile_type[1].name, "Snowball");
	initMissile (1, 4, 22, 2, 10.0f, 10.0f);
	strcpy(missile_type[2].name, "Cannonball");
	initMissile (2, 4, 20, 3, 7.0f, 20.0f);
	strcpy(missile_type[3].name, "Arrow2");
	initMissile (3, 2, 30, 2, 10.0f, 10.0f);
	strcpy(missile_type[4].name, "Snowball2");
	initMissile (4, 4, 30, 3, 60.0f, 50.0f);
	strcpy(missile_type[5].name, "Cannonball2");
	initMissile (5, 4, 30, 2, 10.0f, 50.0f);
	
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
	}

    //Set all missiles to deinitialized state
    for (int i=0; i<MAX_NUM_TOWERS; i++){
        missile[i].initialized=false;
    }
}


//animate the missile, returns how many enemies killed
int animateMissile(QCAR::Matrix44F& missileMatrix, int missileNumber, int x_offset, int y_offset)
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
	if (missile[missileNumber].currentTarget == -1) {
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
	}
	
	//if there is a target, calculate distance and angle
	if (missile[missileNumber].currentTarget != -1) {
		xdiff = enemy[missile[missileNumber].currentTarget].X-missile[missileNumber].X;
		ydiff = enemy[missile[missileNumber].currentTarget].Y-missile[missileNumber].Y;
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
		if (missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X > 150 || missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X < -150 
		|| missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y > 150 || missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y < -150 ) {
			missile[missileNumber].X = missile[missileNumber].defaultX;
			missile[missileNumber].Y = missile[missileNumber].defaultY;
			missile[missileNumber].currentTarget = -1;
		}
	}
    //offset the object based on corner marker in view and position
	SampleUtils::translatePoseMatrix(missile[missileNumber].X + x_offset, missile[missileNumber].Y + y_offset, 0.0f, &missileMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(missile[missileNumber].angle, 0.0f, 0.0f, 1.0f, &missileMatrix.data[0]);
    SampleUtils::scalePoseMatrix(missile[missileNumber].scale, missile[missileNumber].scale, missile[missileNumber].scale, &missileMatrix.data[0]);
    return 1;
}

int checkMissileContact(int missileNumber)
{

	    int enemiesKilled=0;
		
		//if missile is close, there may be a hit and missile is used up
		if (missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X < 15 && missile[missileNumber].X-enemy[missile[missileNumber].currentTarget].X > -15 
		&& missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y < 15 && missile[missileNumber].Y-enemy[missile[missileNumber].currentTarget].Y > -15 ) {
			missile[missileNumber].X = missile[missileNumber].defaultX;
			missile[missileNumber].Y = missile[missileNumber].defaultY;
			enemy[missile[missileNumber].currentTarget].HP = enemy[missile[missileNumber].currentTarget].HP - ((missile[missileNumber].attack)/(enemy[missile[missileNumber].currentTarget].defense));

			//if hit damages enemy enough, enemy is killed and and kill count is increased
			if (enemy[missile[missileNumber].currentTarget].HP <= 0.0f) {
				int temp = missile[missileNumber].currentTarget;
				enemy[missile[missileNumber].currentTarget].X = 10000.0f;
				enemy[missile[missileNumber].currentTarget].Y = -10000.0f;
				enemy[missile[missileNumber].currentTarget].HP = 0.0f;
				enemy[missile[missileNumber].currentTarget].dead = true;
				
				currentScore += enemy[missile[missileNumber].currentTarget].score;
				currentZen += enemy[missile[missileNumber].currentTarget].score;

				displayScore(currentScore);
				displayZen(currentZen);
				level[currentLevel].killCount = level[currentLevel].killCount + 1;

				//if enough enemies are killed, new level is started
				if (level[currentLevel].killCount >=NUM_ENEMY_PER_ROUND) {
					level[currentLevel].end = 1;
					currentLevel++;
					char levelString[20];
					sprintf (levelString, "%d", currentLevel);

					updateApplicationStatusEOL(levelString);
				}

                enemiesKilled++;

				//if other missiles are aiming at this enemy, reset their target
				for (int i = 0; i < MAX_NUM_TOWERS; i++) {
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
void animateEnemy(QCAR::Matrix44F& enemyMatrix, int enemyNumber, int x_offset, int y_offset)
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
				enemy[enemyNumber].X = 350.0f; //arbitrary initial positions
				enemy[enemyNumber].Y = -350.0f;
			}
			else if (stageType == 3) {
				enemy[enemyNumber].X = 150.0f; //arbitrary initial positions
				enemy[enemyNumber].Y = -200.0f;
			}
			enemy[enemyNumber].direction = 90.0f;
			enemy[enemyNumber].HP = enemy[enemyNumber].max_HP;
			enemy[enemyNumber].deployed = true;
		}
		else {
			moveEnemy(enemy[enemyNumber].X, enemy[enemyNumber].Y, enemy[enemyNumber].direction, enemy[enemyNumber].speed, timeDiff, enemy[enemyNumber].section);
			
			if (enemy[enemyNumber].X < 0.0f) {
				currentLives = currentLives - 1;
				displayLives(currentLives);
				if (currentLives == 0 ) {
					gameOver();
				}
				level[currentLevel].killCount = level[currentLevel].killCount + 1;
				if (level[currentLevel].killCount >=NUM_ENEMY_PER_ROUND) {
					level[currentLevel].end = 1;
					
					currentLevel++;
					char levelString[20];
					sprintf (levelString, "%d", currentLevel);
					updateApplicationStatusEOL(levelString);
				}
				removeEnemy(enemyNumber);
			}
        }
		enemy[enemyNumber].prevTime = currentTime;	
	}		

    //offset the object based on corner marker in view
	SampleUtils::translatePoseMatrix(enemy[enemyNumber].X + x_offset, enemy[enemyNumber].Y + y_offset, 20.0f, &enemyMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(enemy[enemyNumber].direction, 0.0f, 0.0f, 1.0f, &enemyMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(90.0f, 1.0f, 0.0f, 0.0f, &enemyMatrix.data[0]);
	SampleUtils::scalePoseMatrix(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE, &enemyMatrix.data[0]);

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


void gameOver ()
{
	for (int enemyNumber2 = 0; enemyNumber2 < MAX_NUM_ENEMIES; enemyNumber2++) {
		removeEnemy(enemyNumber2);
	}
	displayMessage("Game Over, all lives lost!");
}

void moveEnemy (float &x, float &y, float &direction, float speed, float timeDiff, int section)
{
	//Level1: basic
	if (stageType == 1) {
		if (y < 0.0f) {
			x = 350.0f;
			y += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 90.0f; //up
		}
		else
		{
			y = 0.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 180.0f; //left
		}
	}
	
	//Level2: S-shaped
	else if (stageType == 2) {
		if (x == 350.0f && y < 0.0f) {
			y += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 90.0f; //up
		}
		else if (x > 200.0f){
			y = 0.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 180.0f; //left
		}
		else if (y > -350.0f){
			x = 200.0f;
			y -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 270.0f; //down
		}
		else if (x > 0.0f){
			y = -350.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 180.0f; //left
		}
		else
		{
			x = 0.0f;
			y += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 90.0f; //up
		}
	}
	
	//Level3: spiral
	else if (stageType == 3) {
		if (section == 0 && x <= 250.0f) {
			y = -200.0f;
			x += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 0.0f; //right
		}
		else if ((section == 0 || section == 1) && y < -100.0f){
			section = 1;
			y += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			x = 250.0f;
			direction = 90.0f; //up
		}
		else if ((section == 1 || section == 2) && x > 0.0f){
			section = 2;
			y = -100.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 180.0f; //left
		}
		else if ((section == 2 || section == 3) && y > -350.0f){
			section = 3;
			x = 0.0f;
			y -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 270.0f; //down
		}
		else if ((section == 3 || section == 4) && x < 350.0f){
			section = 4;
			y = -350.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 0.0f; //right
		}
		else if ((section == 4 || section == 5) && y < 0.0f){
			section = 5;
			x = 350.0f;
			y += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 90.0f; //up
		}
		else
		{
			section = 6;
			y = 0.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 180.0f; //left
		}
	}
	
	//default to basic
	else
	{
		if (y < 0.0f) {
			y += timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 90.0f; //up
		}
		else
		{
			y = 0.0f;
			x -= timeDiff * ENEMY_MOVEMENT_SPEED * speed;
			direction = 180.0f; //left
		}
	}
}
