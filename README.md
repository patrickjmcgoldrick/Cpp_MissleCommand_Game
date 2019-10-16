# Missle Command Game

<img src="missle_command.png"/>

## for MacOS

Install homebrew first.

```ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null```

Install cmake

```brew install cmake```

Install sdl2_image.

```brew install sdl2_image```



## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make sure you have libraries SDL2 and SDL2_Image installed.
3. Make a build directory in the top level directory: `mkdir build && cd build`
4. Compile: `cmake .. && make`
5. Run it: `./MissleCommand`.


## Code Write Up

### Compiling And Testing
* The submission must compile and run.

### Loops, Functions, I/0
* Functions and controll structures are there.
* No External files read.
* User input is take from the mouse pointer to aim missles.

### Object Oriented Programming
* OO Techniques are used
* Classes use accessor functions
* Class constructors use Member initialization lists 
* * Game.cpp Renderer.cpp Controler.cpp
* Details abstracted in classes
* * Silo.cpp City.cpp Missle.cpp
* Encapsalation
* * Silo.cpp City.cpp Missle.cpp

### Memory Management
* Refernces are passed, specially vectors of shared_ptrs.
* Uses shared_ptr for Vectors of Silo.cpp City.cpp Missle.cpp

### Concurrency
* 





## Inital starter code from - CPPND: Capstone Snake Game Example

[repo](https://github.com/udacity/CppND-Capstone-Snake-Game)

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.



