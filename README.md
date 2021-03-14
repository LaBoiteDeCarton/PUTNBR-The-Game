Hello!

This is a repository for my game called "PUTNBR"

Some useful command: 
To compile all source code use the command: 'make'
To run the game use the command: 'make run'
To clean temp files .o use the command: 'make clean'
To delete all temp files including the game use the command: 'make fclean'
To recompile the game use the command: 'make re'

About the game:
In this game you will control a part of PUTNBR in a 2D world. Your goal is to collect all letters of PUTNBR and reach the exit.
Your final shape can be everything BUT the letters should be besides in the same order as the word PUTNBR itself.
The world have obstacles and dead obstacles, there is no time limit or movement limit. If you die the level is restarted.
You can choose to restart yourself by pressing 'R' if you are stuck (and it will happen, trust me, not only once)
There is no save system, if you quit, the game will restart at the level 1.
There is no selection level system, if you finished a level you cannot go back.
There is only 13 levels available, at the end of the project there will be 42 levels.

    Control: 
    Left arrow: move to the left
    Right arrow: move to the right
    Up arrow: move to top
    Down arrow: move to bottom
    Q: quit the game
    R: restart level
    Enter: Select menu button

About the code:
We used the "ncurses" library to display the game on the terminal.
The levels data is stored in the files in the files/ directory. The level files had a particular structure, this structure make the file readable by the program (especially the creat_map_from_content() function).
There is no data protection, if the file is modified and is no longer in a valid form, the game will be corrupted and segmentation fault is expected when loading the file.
The game was created on MACOSX, the other OS behaviors of the game are unpredicted yet.

Future features:
- 42 levels
- Saving progress system
- Adding "level" in menu to select levels (saving system needed first)
- Quit in a level should redirect to menu and not to the end of the game
- Items is implemented in the code but not used, create some item behaviors, like moving boxes and maybe teleportation.
- Create a "create your level" section, when user can create his own level. 

Last Update: 14/03/2021:
    First README file commit