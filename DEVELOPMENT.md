# Project Development Log

* December 08: More game logic and object tracking/gameplay integration
  * Fixed bug of fruit explosion animation
  * Implemented bombs, game over screen, player HP, speed progression
  * Replaced mouse with tracked object on webcam
* December 07: Object tracking
  * Grabbed live video from the user's webcam
  * Tracked an object of a specific color from the video
* December 06: Game mechanics
  * Handled Fruit collision with mouse, and animate an explosion when this happens
  * Made a FruitCannon that shoots Fruit objects from the bottom of the game screen
  * Recorded the player's points
* December 05: Created the basic structure and movement of a Fruit object
* December 04: Changed project idea
  * Realized that my original idea was too simple, and required very little of oF's features
  * Gathered info on the necessary librairies needed to finish new project idea
* November 22: Setup project with Azure Speech SDK, wrote code for voice-to-text 
* November 20-21: Configured project with openFrameworks, started looking at suitable APIs to use

# Project Summary

I will write an openFrameworks implementation of Halfbrick's classic game: Fruit Ninja, with an extra twist. First, I will
finish the game mechanics, which would allow the player to slice through "fruits" and gain points. Then, I will attempt to
leverage ofxOpenCV to allow the player to slice the on-screen fruits with their fingers. Lastly, time permitting, I will
improve the game graphics and create a start/end screen.