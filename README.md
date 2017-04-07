# CIS 343 Project 3 - Connect Four in C
This is the classic game Connect Four written in C.  It's a game where 2 players drop tiles into a grid, and each player tries to connect four of their tiles in a row to win. This program is a text-based version of Connect Four run in the command line.  The user types in the number of the column they want to drop a tile into, and the grid/board is re-printed everytime a change is made.  

### Features
Several things are configurable by the user, such as the width and the height of the board, as well as how many tiles a player must connect to win. (Instead of connect four, you can play connect five, connect six, connect 42... etc.)  The user can also save a game in progress, and load a previously saved game.

I used the argp library to automate parsing arguments. It can take the following command line arguments:

 Short| Long | Description
---|---|---
 **-?** | **--help** | Display a help message
 (none) | **--usage** | Display a usage message
 **-V** | **--version** | Show the version number
 **-w** | **--width=** | Width of the board
 **-h** | **--height=** | Height of the board
 **-s** | **--square=** | Set both the width and height
 **-c** | **--connect=** | How many connections needed to win
 **-l** | **--load=** | Load a game board from a file (overwrites other options)
 **-a** | **--ai=** | Determines if the AI should play as player 2
 
 While the game is running, it will accept the following commands:\*
 
  Command | Description
----------|----------
 **Any Number** | The column that the current player wants to drop a tile in.
 **(l)oad** | Load a game from a file (deletes exisiting game)
 **(s)ave** | Save the current game and it's parameters.
 **(q)uit** | Quits the game.
 
 \*Parenthesis around a letter indicate the short version of the command.

There is also a basic AI that was implemented to play against.  It's not a very robust AI, but it does more than just pick a random column.
