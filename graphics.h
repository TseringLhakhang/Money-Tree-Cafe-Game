#ifndef MONEY_TREE_CAFE_GAME_GRAPHICS_H
#define MONEY_TREE_CAFE_GAME_GRAPHICS_H

#include <stdlib.h>
#include <string>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// Program initialization NOT OpenGL/GLUT dependent,
// as we haven't created a GLUT window yet

// Will display the message for start and end screen as well as coin count
void initMessage(std::string messageScreen, std::string message);

// Will display the money count message
void initMoneyCount();

// Will draw the leaves of the tree
void initLeaves();

// Contains the beverage themselves and their corresponding price
void initMenu();

void initFrenchWindow();

void init();

// Initialize OpenGL Graphics
void InitGL();

// Callback functions for GLUT

// Draw the window - this is where all the GL actions are
void display();

// Trap and process alphanumeric keyboard events
void kbd(unsigned char key, int x, int y);

// Trap and process special keyboard events
void kbdS(int key, int x, int y);

// Handle "mouse cursor moved" events 
void cursor(int x, int y);

// Calls itself after a specified time
void timer(int dummy);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

#endif //MONEY_TREE_CAFE_GAME_GRAPHICS_H
