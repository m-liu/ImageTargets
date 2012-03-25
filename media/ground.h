/*
created with obj2opengl.pl

source file    : ./ground.obj
vertices       : 4
faces          : 2
normals        : 1
texture coords : 4


// include generated arrays
#import "./ground.h"

// set input data to arrays
glVertexPointer(3, GL_FLOAT, 0, groundVerts);
glNormalPointer(GL_FLOAT, 0, groundNormals);
glTexCoordPointer(2, GL_FLOAT, 0, groundTexCoords);

// draw data
glDrawArrays(GL_TRIANGLES, 0, groundNumVerts);
*/

unsigned int groundNumVerts = 6;

float groundVerts [] = {
  // f 1/1/1 4/2/1 3/3/1
  0.5, 0, -0.5,
  -0.5, 0, -0.5,
  -0.5, 0, 0.5,
  // f 1/1/1 3/3/1 2/4/1
  0.5, 0, -0.5,
  -0.5, 0, 0.5,
  0.5, 0, 0.5,
};

float groundNormals [] = {
  // f 1/1/1 4/2/1 3/3/1
  0, 1, 0,
  0, 1, 0,
  0, 1, 0,
  // f 1/1/1 3/3/1 2/4/1
  0, 1, 0,
  0, 1, 0,
  0, 1, 0,
};

float groundTexCoords [] = {
  // f 1/1/1 4/2/1 3/3/1
  0.000000, 1,
  1.000000, 1,
  1.000000, 0,
  // f 1/1/1 3/3/1 2/4/1
  0.000000, 1,
  1.000000, 0,
  0.000000, 0,
};


