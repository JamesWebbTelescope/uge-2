Mastermind
This is a simple, text-based version of Mastermind.

Prerequisites:
In order to run this game, you need to have the C++ Extensions for VS Code installed.

Running the game:
In order to run the game, you first need to compile the Mastermind.cpp-file. To do this in VS Code, choose Terminal->Run build task. Make sure to use the C/C++ compiler for Windows.
Once the game is built successfully, choose Run->Start without debugging. A terminal will open, where you can then play the game.

How to play:
The game starts with the computer choosing a set of four random colours from a list of allowed colours. Once it's done that, the game asks you (the player) to choose four colours. The list must be separated by spaces and you must hit "Enter" after typing the list of colours. If one or more of the colours are not allowed, the game will prompt you to give a new colour.

Then, the game checks which colours are correct and in the correct place. It also checks how many colors are correct, but in the wrong place. It then gives you feedback in the form of a black arrow for each correct color in the correct place and a white arrow for each correct color in the wrong place

You win by guessing all the colors and their placement.
If you spend more than 12 turns guessing, you lose the game.
