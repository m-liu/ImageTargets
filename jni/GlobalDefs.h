

#ifndef _GLOBALDEFS_H_
#define _GLOBALDEFS_H_


// Defines:

//enemy properties
#define MAX_NUM_ENEMIES 10
#define NUM_ENEMY_TYPES 7
#define ENEMY_NUM_FRAMES 48
#define ENEMY_SCALE 50.0f
#define ENEMY_MOVEMENT_SPEED 50.0f

//tower/missile properties
#define NUM_MISSILE_TYPES 2
#define MAX_NUM_TOWERS 4
#define MISSILE_NUM_FRAMES 24
#define TOWER_SCALE 75.0f
#define MISSILE_SCALE 75.0f

#define STARTING_X 350.0f
#define STARTING_Y -350.0.0f


//game properties
#define NUM_LEVELS 3



// Structures: 
struct EnemyUnit
{
    int type;
	int texture;
	char name[30];
    float X;
    float Y;
	float direction;
	float max_HP;
	float HP;
	float speed;
	float defense;
	float score;
	float deploydelay;
	bool deployed;
	bool dead;
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
