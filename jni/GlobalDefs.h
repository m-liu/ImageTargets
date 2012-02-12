

#ifndef _GLOBALDEFS_H_
#define _GLOBALDEFS_H_


// Defines:

//enemy properties
#define MAX_NUM_ENEMIES 10
#define NUM_ENEMY_TYPES 2
#define ENEMY_NUM_FRAMES 48
#define ENEMY_SCALE 50.0f

//tower/missile properties
#define NUM_MISSILE_TYPES 2
#define MAX_NUM_TOWERS 4
#define MISSILE_NUM_FRAMES 24
#define TOWER_SCALE 75.0f
#define MISSILE_SCALE 75.0f

//game properties
#define NUM_LEVELS 3



// Structures: 
struct EnemyUnit
{
    int type;
	char name[30];
    float X;
    float Y;
	float HP;
	float max_HP;
	float speed;
	float defense;
	float score;
	float count;
    double prevTime;
};

struct MissileUnit
{
	bool initialized;
    int type;
	char name[20];
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

//Level struct
struct Level
{
    float start;
    float end;
    int killCount;
};


#endif
