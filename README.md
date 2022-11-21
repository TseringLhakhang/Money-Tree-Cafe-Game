# Money Tree Cafe Game
### Rachel Atherly and Tsering Lhakhang 

Installation: none
###Summary: 
The program works similarly to an old clicker style game.  There are four separate screens (2 playable and 2 message) controlled by enums.
In the garden screen, players click on a "money tree" which increases an on-screen counter of player funds.  
The money is taken to the cafe screen where players can spend their money to buy drinks.
Once all three drinks are purchased, the game is over and the "win" screen is displayed.

##Concepts:
- OpenGl and GLUT
- graphics with C++ classes
- drawing
- mouse and keyboard listeners
- timers

All the buttons and shapes are divided into separate classes, using inheritance to connect them when appropriate.

###Future improvements: 
We hope to expand on this project in several ways.  For one, we would like to increase the interaction with the money trees.  We would like
to design it so that the continuous money falling animation does not run constantly.  Instead, it is triggered for a set amount of time
each time the user clicks the tree.  We could make that even more detailed by having each click correspond to a coin falling.

In the cafe, we would like to improve upon the design of the drinks.  We hope to implement separate drink class, so we can populate
them as their own objects and more variety of drinks.  Additionally, we would like to utilize 8 bit drawing with a text file, to allow for
more detailed drink designs.

##Bugs: 
At this time, there are no known bugs within the current functionality.

#### Starter code (including glut setup, shape classes, timer functions...) provided by L.Dion