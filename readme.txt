Ryan Konkul
Scott Prentice
CS 340
Project 4: Mine Sweeper

To implement buttons we created a class called Button which inherits from QPushButton. Each button has it's row and col in the grid created by MainWindow. When right-clicked, the display changes. Rather than rely on the text on the button to determine the state, an enum is used in the background to show its state. The class also stores whether the button has a mine and how many mines surround the button. 
When a button is rightclicked, the display changes and a signal which means a mine is marked or unmarked is emitted to tell MainWindow to increment or decrement mines_left. This value may be negative and does not affect the game. 

When a button is leftclicked, the state is checked. If the state is a mine or question mark, nothing is done. If a mine was leftclicked, a player_lose() signal is emitted. If a blank button and not a mine, mine_search_signal() is emitted. This signal is slotted by MainWindow which goes and recursively searches for buttons with no surrounding mines and reveals those. 
The algorithm for mine_search is such:
1. Disable the button
2. Reveal number of surrounding mines
3. If no surrounding mines, check all 8 directions.
4. If the button in a direction is not out of bounds and enabled, recurse on the button. 

In MainWindow there are two constants: GRID_SIZE and MINES. These allow the grid to be easily changed. When MainWindow is initialized, the grid is prepared by creating Buttons in two for loops. Signals and Slots are connected and then it is added to a vector of Button*. After the grid is initialized, mines are randomly placed. Then each button calculates the number of surrounding mines. 
