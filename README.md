# Kulki

Kulki is a project in command line environment written in C++.
Previously I was using MSVC compiler for it.
I reworked the code, so now it (almost) works also on gcc.

Kulki is a Polish variant of other game called Lines (Шарики).
The game make save file which saves after every move. You can load it in the menu.
It also includes scoreboard.

### Rules:

Rules are included in program. Please read them before play.


## Prerequisites

You need to compile this project by yourself in any C++ compiler.  
gcc example:

```
$ gcc Main.cpp [rest of .cpp and .h files] -o output
$ ./output
```

## How to use

### Moving in game menu

Every option in menu is preceded by number it represents. Just simply type exact number and press Enter.

### Movement

To move you need to type coordinates of piece and coordinates of empty field.

For example:

```
B3
**pressing Enter**
C2
**pressing Enter**
```

Every rule about moving piece is explained in in-game rules.

## Tools used to create this project

### Before gcc compatibility
* [Windows 7 Ultimate](https://www.microsoft.com/en-us/windows/) - System used to make this project
* [Visual Studio Professional 2013](https://msdn.microsoft.com/en-us/library/dd831853(v=vs.120)) - C++ IDE and compiler

### After gcc compatibility
* [Antergos 17.10](https://antergos.com) - System used to make this project
* [Code::Blocks](http://www.codeblocks.org) - C++ IDE
* [gcc](https://gcc.gnu.org) - C++ compiler


## Problem with proper working if compiled in gcc

Yes sir/madame, there is a problem in-game when compiled in gcc.
This problem shows up in first moves, especially when you move by exactly one field.
But there is possibility that you will not encounter that problem at all, it's completly random.

If I find time for precise analysis, then I probably fix this problem.

If you are a good and helpful person, and you want to help me - contact me via Discord:
```
Gregorit#7618
```
