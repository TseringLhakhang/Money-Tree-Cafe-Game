#include "graphics.h"
#include "Button.h"
#include "Quad.h"
#include "circle.h"
#include <iostream>
#include <time.h>
#include <vector>
#include <memory>
using namespace std;

GLdouble width, height;
int wd;

// Game color with fun and descriptive names
const color leafGreen(124/255.0, 181/255.0, 24/255.0);
const color grassGreen(36/255.0, 85/255.0, 1/255.0);
const color sunnyYellow(255/255.0, 195/255.0, 0);
const color pastelYellow(255/255.0, 251/255.0, 193/255.0);
const color pastelPink(247/255.0, 164/255.0, 164/255.0);
const color pastelPurple(186/255.0, 148/255.0, 209/255.0);
const color buttonBeige(171/255.0, 120/255.0, 78/255.0);
const color barkBrown(0.5, 0.25, 0);
const color skyBlue(164/255.0, 219/255.0, 232/255.0);
const color creamWhite(255/255.0, 248/255.0, 234/255.0);

Button toGarden(buttonBeige, {65, 40}, 100, 50, "To Garden");
Button toCafe(buttonBeige, {935, 40}, 100, 50, "To Cafe");

Quad tree1(barkBrown, {200, 311}, 50, 149);
Button tree2(barkBrown, {500, 311}, 50, 149, "tree");
Quad tree3(barkBrown, {800, 311}, 50, 149);

vector<unique_ptr<Shape>> leaves;

Quad table(buttonBeige, {900, 400}, 800, 200);
Quad grass(grassGreen, {500,450}, 1000, 150);
Circle sun(sunnyYellow, 100,100, 50);

Button glass1(skyBlue, {900, 250}, 50, 100, "");
Button glass2(skyBlue,{800, 250}, 50, 100, "");
Button glass3(skyBlue,{700, 250}, 50, 100, "");

vector<Quad> window1;
Circle window2(creamWhite, 245, 250, 150);
Circle window3(skyBlue, 245, 250, 135);
vector<unique_ptr<Shape>> window4;

vector<Button> drinkMenu;

Quad bev1(pastelPink,{900, 260}, 40, 70);
Quad bev2(pastelYellow, {800, 260}, 40, 70);
Quad bev3(pastelPurple,{700, 260}, 40, 70);

bool purchased1 = false;
bool purchased2 = false;
bool purchased3 = false;

int price[] = {10, 15, 20};

int subtractMoney = 0;
int moneyCount = 0;


vector<Circle> money1;
vector<Circle> money2;
vector<Circle> money3;

enum gameScreen {start, garden, cafe, win};
gameScreen screen = start;

void initMessage(string messageScreen, string message) {
    // If user is on the start or win screen than it only message will show up at the middle
    if (messageScreen == "starting" || messageScreen == "winning") {
        glColor3f(1, 1, 1);
        glRasterPos2i((width/2)-80, (height/2)-5);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }
    // If user is on the play screen (ie garden or cafe) than it will show the score count of the bottom right corner
    else if (messageScreen == "playing") {
        glColor3f(1, 1, 1);
        glRasterPos2i(width-315, height-20);
        for (char letter : message) {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, letter);
        }
    }
}

void initMoneyCount() {
    // Keeping track of the money count
    // Subtract when drinks are purchased
    if (subtractMoney != 0) {
        moneyCount -= subtractMoney;
    }

    // Message of how many coins have been earned
    string message = "You earned: " + to_string(moneyCount) + " coins";
    string messageScreen = "playing";
    initMessage(messageScreen, message);
}

void initLeaves() {
    //Circles that make up each tree leaves/bush
    leaves.clear();

    // First Tree leaves
    leaves.push_back(make_unique<Circle>(leafGreen, 200, 200, 50));
    leaves.push_back(make_unique<Circle>(leafGreen, 255, 225, 45));
    leaves.push_back(make_unique<Circle>(leafGreen, 225, 250, 40));
    leaves.push_back(make_unique<Circle>(leafGreen, 175, 250, 40));
    leaves.push_back(make_unique<Circle>(leafGreen, 145, 225, 45));
    //leafBase.push_back(Quad(leafGreen,{200, 220}, 130, 60));

    // Second tree leaves
    leaves.push_back(make_unique<Circle>(leafGreen, 500, 180, 50));
    leaves.push_back(make_unique<Circle>(leafGreen, 555, 205, 45));
    leaves.push_back(make_unique<Circle>(leafGreen, 525, 230, 40));
    leaves.push_back(make_unique<Circle>(leafGreen, 475, 230, 40));
    leaves.push_back(make_unique<Circle>(leafGreen, 445, 205, 45));
    //leafBase.push_back(Quad(leafGreen,{500, 220}, 130, 60));

    // Third tree leaves
    leaves.push_back(make_unique<Circle>(leafGreen, 800, 200, 50));
    leaves.push_back(make_unique<Circle>(leafGreen, 855, 225, 45));
    leaves.push_back(make_unique<Circle>(leafGreen, 825, 250, 40));
    leaves.push_back(make_unique<Circle>(leafGreen, 775, 250, 40));
    leaves.push_back(make_unique<Circle>(leafGreen, 745, 225, 45));
    //leafBase.push_back(Quad(leafGreen,{800, 220}, 130, 60));

}

void initMenu() {
    drinkMenu.push_back(Button(pastelPink,{900, 170}, 50, 20, "$10"));
    drinkMenu.push_back(Button(pastelYellow,{800, 170}, 50, 20, "$15"));
    drinkMenu.push_back(Button(pastelPurple,{700, 170}, 50, 20, "$20"));
}

void initFrenchWindow() {
    window1.push_back(Quad(creamWhite, {245, 400}, 300, 300));
    window1.push_back(Quad(skyBlue, {245, 400}, 270, 300));
    window1.push_back(Quad(barkBrown, {245, 430}, 40, 150));
    window1.push_back(Quad(creamWhite, {245, 270}, 300, 17));
    window1.push_back(Quad(creamWhite, {245, 400}, 300, 17));
    window1.push_back(Quad(creamWhite, {245, 310}, 17, 400));

    window4.push_back(make_unique<Circle>(leafGreen, 245, 290, 55));
    window4.push_back(make_unique<Circle>(leafGreen, 300, 315, 50));
    window4.push_back(make_unique<Circle>(leafGreen, 270, 340, 45));
    window4.push_back(make_unique<Circle>(leafGreen, 220, 340, 45));
    window4.push_back(make_unique<Circle>(leafGreen, 190, 315, 50));
}

void init() {
    width = 1000;
    height = 500;
    srand(time(0));

    initLeaves();
    initMenu();
    initFrenchWindow();
    // coin fall logic
    for (int i = 0; i < 40; ++i) {
        money1.push_back(Circle(203.0/255.0, 161/255.0, 53/255.0, 1, rand() % 200 + 100, rand() % 260 + 150, rand() % 5 + 1));
    }
    for (int i = 0; i < 40; ++i) {
        money2.push_back(Circle(203.0/255.0, 161/255.0, 53/255.0, 1, rand() % 200 + 400, rand() % 240 + 150, rand() % 5 + 1));
    }
    for (int i = 0; i < 40; ++i) {
        money3.push_back(Circle(203.0/255.0, 161/255.0, 53/255.0, 1, rand() % 200 + 700, rand() % 260 + 150, rand() % 5 + 1));
    }

}

/* Initialize OpenGL Graphics */
void initGL() {
    // Set "clearing" or background color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black and opaque
}

/* Handler for window-repaint event. Call back when the window first appears and
 whenever the window needs to be re-painted. */
void display() {
    // tell OpenGL to use the whole window for drawing
    glViewport(0, 0, width, height);
    
    // do an orthographic parallel projection with the coordinate
    // system set to first quadrant, limited by screen/window size
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /*
     * Draw here
     */
    if (screen == start) {
        string message = "Press s to start";
        string messageScreen = "starting";
        initMessage(messageScreen, message);
    }

    else if(screen == garden) {
        glClearColor(164/255.0f, 219/255.0f, 232/255.0f, 1.0f);

        // Draw all items in gardeN
        sun.draw();
        toCafe.draw();
        tree1.draw();
        tree2.draw();
        tree3.draw();

        // Coin falling animation is drawn
        for (Circle &coin : money1) {
            coin.draw();
        }
        for (Circle &coin : money2) {
            coin.draw();
        }
        for (Circle &coin : money3) {
            coin.draw();
        }
        //Draw tree leaves and grass after money animation to make it look better
        for (unique_ptr<Shape> &leaf : leaves) {
            leaf->draw();
        }
        grass.draw();

        // Money counter display
        initMoneyCount();
    }

    else if(screen == cafe) {
        glClearColor(235/255.0f, 199/255.0f, 178/255.0f, 1.0f);
        toGarden.draw();
        table.draw();
        initMoneyCount();

        for (Button &text : drinkMenu) {
            text.draw();
        }

        // Drawing window components, Order looks messy but it's so that the layers appear correctly
        window1.at(0).draw();
        window2.draw();
        window1.at(1).draw();
        window3.draw();
        window1.at(2).draw();
        for (unique_ptr<Shape> &leaf : window4) {
            leaf->draw();
        }
        window1.at(3).draw();
        window1.at(4).draw();
        window1.at(5).draw();

        // Check which drink was not purchased and draw
        if(!purchased1){
            glass1.draw();
            bev1.draw();
        }

        if(!purchased2){
            glass2.draw();
            bev2.draw();
        }

        if(!purchased3){
            glass3.draw();
            bev3.draw();
        }
    }

    // Player wins if all drinks have been purchased
    else if (screen == win) {
        glClearColor(164/255.0f, 219/255.0f, 232/255.0f, 1.0f);
        string message = "You Win!";
        string messageScreen = "winning";
        initMessage(messageScreen, message);
    }
    if(purchased1 && purchased2 && purchased3) {
        screen = win;
    }

    glFlush();  // Render now
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    // press s to start game
    if (key == 115 && screen == start) {
        screen = garden;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    switch(key) {
        case GLUT_KEY_DOWN:
            tree2.move(0,1);
            
            break;
        case GLUT_KEY_LEFT:
            tree2.move(-1,0);
            
            break;
        case GLUT_KEY_RIGHT:
            tree2.move(1,0);
            
            break;
        case GLUT_KEY_UP:
            tree2.move(0,-1);
            
            break;
    }
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    // DONE: If the Button is overlapping with the (x, y) coordinate passed in, call the hover method. Otherwise, call the release method.
    if(tree2.isOverlapping(x,y)) {
        tree2.hover();
    }
    else{
        tree2.release();
    }

    //in garden, toCafe sign
    if(toCafe.isOverlapping(x,y)) {
        toCafe.hover();
    }
    else{
        toCafe.release();
    }

    //in cafe, toGarden sign
    if(toGarden.isOverlapping(x,y)) {
        toGarden.hover();
    }
    else{
        toGarden.release();
    }

    //glasses
    if(glass1.isOverlapping(x,y)) {
        glass1.hover();
    }
    else{
        glass1.release();
    }

    if(glass2.isOverlapping(x,y)) {
        glass2.hover();
    }
    else{
        glass2.release();
    }

    if(glass3.isOverlapping(x,y)) {
        glass3.hover();
    }
    else{
        glass3.release();
    }

    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    //If the left button is down and the cursor is overlapping with the Button, call the pressDown method. Otherwise, call the release method.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && tree2.isOverlapping(x,y)) {
        tree2.pressDown();
    }
    else {
        tree2.release();
    }

    //If the left button is up and the cursor is overlapping with the Button, call spawnMoney.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && tree2.isOverlapping(x,y)) {
        //spawnMoney();
        moneyCount++;
    }

    //for toCafe sign
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && toCafe.isOverlapping(x,y)) {
        toCafe.pressDown();
    }
    else {
        toCafe.release();
    }
    //if click sign, change to cafe screen
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && toCafe.isOverlapping(x,y)) {
        screen = cafe;
    }

    //for toGarden sign
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && toGarden.isOverlapping(x,y)) {
        toGarden.pressDown();
    }
    else {
        toGarden.release();
    }
    //if click sign, change to garden screen
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && toGarden.isOverlapping(x,y)) {
        screen = garden;
    }

    //glasses
    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && glass1.isOverlapping(x,y) && moneyCount >= price[0]) {
        moneyCount -= price[0];
        purchased1 = true;
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && glass2.isOverlapping(x,y) && moneyCount >= price[1]) {
        moneyCount -= price[1];
        purchased2 = true;
    }

    if(button == GLUT_LEFT_BUTTON && state == GLUT_UP && glass3.isOverlapping(x,y) && moneyCount >= price[2]) {
        moneyCount -= price[2];
        purchased3 = true;
    }

    glutPostRedisplay();
}

void timer(int dummy) {
    // Sun moving across screen and changes to a darker orange.
    // Then restarts with x position back to 0 and color back to yellow
    sun.moveX(2);
    sun.setColor(sun.getRed() + 1.0/1000, sun.getGreen() - 1.0/1000, 0, 1);

    if (sun.getCenterX() > (width + sun.getRadius())) {
        // Set it to the right of the screen so that it passes through again
        sun.setCenterX(0);
        sun.setColor({255/255.0, 195/255.0, 0});
    }


    // Snow falling logic
    for (Circle &coin : money1) {
        coin.moveY(coin.getRadius());
        if (coin.getBottomY() > 385) {
            coin.setCenter(rand() % 200 + 100, 260);
        }
    }
    for (Circle &coin : money2) {
        coin.moveY(coin.getRadius());
        if (coin.getBottomY() > 385) {
            coin.setCenter(rand() % 200 + 400, 240);
        }
    }
    for (Circle &coin : money3) {
        coin.moveY(coin.getRadius());
        if (coin.getBottomY() > 385) {
            coin.setCenter(rand() % 200 + 700, 240);
        }
    }
    
    glutPostRedisplay();
    glutTimerFunc(30, timer, dummy);
}

/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) {
    
    init();
    
    glutInit(&argc, argv);          // Initialize GLUT
    
    glutInitDisplayMode(GLUT_RGBA);
    
    glutInitWindowSize((int)width, (int)height);
    glutInitWindowPosition(100, 200); // Position the window's initial top-left corner
    /* create the window and store the handle to it */
    wd = glutCreateWindow("Money Tree Cafe" /* title */ );
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    // Our own OpenGL initialization
    initGL();
    
    // register keyboard press event processing function
    // works for numbers, letters, spacebar, etc.
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}
