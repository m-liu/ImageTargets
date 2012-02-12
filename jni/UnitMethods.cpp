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
	enemy[enemyNumber].X = enemy_type[enemyType].X;
	enemy[enemyNumber].Y = enemy_type[enemyType].Y;
	enemy[enemyNumber].max_HP = enemy_type[enemyType].max_HP;
	enemy[enemyNumber].HP = enemy_type[enemyType].max_HP;
	enemy[enemyNumber].speed = enemy_type[enemyType].speed;
	enemy[enemyNumber].defense = enemy_type[enemyType].defense;
	enemy[enemyNumber].score = enemy_type[enemyType].score;
	enemy[enemyNumber].count = delay;
    enemy[enemyNumber].prevTime = getCurrentTime();
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


/********************
 * Initializes the DB and the unit stats
 ********************/
void initUnitDB () {
    //enemy initialization
    //strcpy(enemy_type[0].name, "HeadlessCow");
    enemy_type[0].type = 1;
    enemy_type[0].max_HP = 25.0f;
    enemy_type[0].X = 10000.0f;
    enemy_type[0].Y = -10000.0f;
    enemy_type[0].HP = enemy_type[0].max_HP;
    enemy_type[0].speed = 1.0f;
    enemy_type[0].defense = 1.0f;

    strcpy(enemy_type[0].name, "Zombie");
    enemy_type[1].type = 2;
    enemy_type[1].max_HP = 40.0f;
    enemy_type[1].X = 10000.0f;
    enemy_type[1].Y = -10000.0f;
    enemy_type[1].HP = enemy_type[1].max_HP;
    enemy_type[1].speed = 1.3f;
    enemy_type[1].defense = 1.0f;


    //missile initializations
    strcpy(missile_type[0].name, "Arrow");
    missile_type[0].type = 1;
    missile_type[0].speed = 14;
    missile_type[0].cost = 3;
    missile_type[0].attack = 2.0f;

    strcpy(missile_type[1].name, "Snowball");
    missile_type[1].type = 2;
    missile_type[1].speed = 22;
    missile_type[1].cost = 2;
    missile_type[1].attack = 1.0f;


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
	float angle;
	float slope;

	int possibleTarget = 0;
	int possibleTargetDistance = 0;
	double time4 = getCurrentTime();  
	float dt4 = (float)(time4-missile[missileNumber].prevTime);          // from frame to frame
	missile[missileNumber].prevTime = time4;
			
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
		angle = atan2(ydiff, xdiff) * 180 / 3.14159265;
		//x2 + y2 = 196 (move 14 units each second)
		//y/x = slope (move along slope)
		float xdist = sqrt(missile[missileNumber].speed*missile[missileNumber].speed/(1+(slope*slope)));
		float ydist = sqrt(missile[missileNumber].speed*missile[missileNumber].speed-(xdist*xdist));
		xdist = dt4*10.0f*xdist;
		ydist = dt4*10.0f*ydist;
		
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
	SampleUtils::translatePoseMatrix(missile[missileNumber].X + x_offset, missile[missileNumber].Y + y_offset, 20.0f, &missileMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(angle, 0.0f, 0.0f, 1.0f, &missileMatrix.data[0]);
    SampleUtils::scalePoseMatrix(MISSILE_SCALE, MISSILE_SCALE, MISSILE_SCALE, &missileMatrix.data[0]);
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
				enemy[missile[missileNumber].currentTarget].count = -1;
				
				currentScore += enemy[missile[missileNumber].currentTarget].score;
                //TODO: Uncomment
				//updateScore((int)currentScore);
				level[currentLevel].killCount = level[currentLevel].killCount + 1;

				//if enough enemies are killed, new level is started
				if (level[currentLevel].killCount >=10) {
					level[currentLevel].end = 1;
					currentLevel++;
					startLevel(currentLevel);
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
void animateTower(QCAR::Matrix44F& towerMatrix)
{
    /*
    static float rotateBowlAngle2 = 0.0f;
    static double prevTime2 = getCurrentTime();
    double time2 = getCurrentTime();             // Get real time difference
    float dt2 = (float)(time2-prevTime2);          // from frame to frame
    rotateBowlAngle2 += dt2 * 360.0f;     // Animate angle based on time
    SampleUtils::rotatePoseMatrix(rotateBowlAngle2, 0.0f, 0.0f, 1.0f, &towerMatrix.data[0]);
    prevTime2 = time2;
    */ 

    //FIXME: Model base not at Z=0?
    SampleUtils::translatePoseMatrix(0 ,0, 50.0f, &towerMatrix.data[0]);
    SampleUtils::scalePoseMatrix(TOWER_SCALE, TOWER_SCALE, TOWER_SCALE, &towerMatrix.data[0]);
}



//animate the enemy
void animateEnemy(QCAR::Matrix44F& enemyMatrix, int enemyNumber, int x_offset, int y_offset)
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
				enemy[enemyNumber].Y += dt4 * 10.0f * enemy[enemyNumber].speed;
				direction = 90.0f;
			}
            else
			{
				enemy[enemyNumber].X -= dt4 * 10.0f * enemy[enemyNumber].speed;
				direction = 180.0f;
			}
			if (enemy[enemyNumber].X < 0.0f) {
				currentLives = currentLives - 1;
				if (currentLives == 0 ) {
					for (int enemyNumber2 = 0; enemyNumber2 < MAX_NUM_ENEMIES; enemyNumber2++) {
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

    //offset the object based on corner marker in view
	SampleUtils::translatePoseMatrix(enemy[enemyNumber].X + x_offset, enemy[enemyNumber].Y + y_offset, 20.0f, &enemyMatrix.data[0]);
	SampleUtils::rotatePoseMatrix(direction, 0.0f, 0.0f, 1.0f, &enemyMatrix.data[0]);
	SampleUtils::scalePoseMatrix(ENEMY_SCALE, ENEMY_SCALE, ENEMY_SCALE, &enemyMatrix.data[0]);

}


//update missile positions
void updateMissileDefaultPos(int missileNumber, float lx, float ly)
{
	missile[missileNumber].defaultX = lx;
	missile[missileNumber].defaultY = ly;
}




