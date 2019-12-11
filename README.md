# Finger Ninja

Ever dreamt of playing fruit ninja by actually slicing through the air like a real ninja? Well, then this openFrameworks
implementation -- Finger Ninja -- might just be for you!

## Dependencies

* [openFrameworks](https://openframeworks.cc/)
* Any IDE supported by openFrameworks' project generator

## Building the Project

* Clone this repository
* Build this project using openFrameworks' [project generator](https://openframeworks.cc/learning/01_basics/create_a_new_project/), and make sure to select `ofxOpenCv` in the Addons menu
* You're all set!

## Gameplay

Currently, the way the program tracks your finger is via the color yellow. To play the game, simply obtain a small yellow
ball and hold it in your hand, in view of your webcam. For the program to work nicely, it is important to have a relatively 
strong contrast in color between the tracked object and your surroundings. If you would like to use a different colored 
object, open up `src/ofApp.h` and change the HSV range accordingly.

* Move your hand around to wave your "sword" and slice the orange fruits that pop up
* Make sure to avoid the black balls (bombs!)
* The game is over once you hit a bomb, or miss three orange fruits
* To replay, simply press the "Enter" key once

## Project Purpose

Developed as the final project for UIUC's CS126 class, Software Design Studio.
