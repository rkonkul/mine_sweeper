#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <vector>
#include <algorithm>
#include "Button.h"

namespace Ui {
    class MainWindow;
}
enum direction { TOPLEFT, TOP, TOPRIGHT, LEFT, RIGHT, BOTTOMLEFT, BOTTOM, BOTTOMRIGHT };
inline direction& operator++(direction& e, int a) {
    const int i = static_cast<int>(e)+1;
    e = static_cast<direction>((i) % 9);
    return e;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    //reads in highscores from file
    //if file not found, one created
    void read_in_highscores();
    //writes out highscores to file
    void write_highscores();
    //constructs a grid of buttons
    void prepare_grid(int top_left_x, int top_left_y, int grid_size, QWidget *parent);
    //randomly places mines
    void place_mines();
    //checks if a surrounding button has a mine
    bool surround_mine(Button* b, direction dir);
    //gets the button in a direction
    //returns parameter if out of bounds
    Button* move_dir(Button* b, direction dir);
    //calculates number of mines surrounding button
    void calc_mines();
    //handles when player has won
    void player_won();
    //returns the Button at a row, col
    Button* get_button(int row, int col);
    ~MainWindow();

public slots:
    void increment_mines_left();
    void decrement_mines_left();
    //increment timer on QTimer signal
    void update_timer();
    //resets timer and gameboard
    void reset();
    //handles when player loses
    void player_lose();
    //recursively searches board for 0 buttons and reveals
    //those around it
    void mine_search(Button *b);
    //debug slot
    void show_mines();
    //debug slot
    void show_num_mines();

private slots:
    //menu: Reset/Reset
    void on_actionReset_triggered();

    void on_actionExit_triggered();

    void on_actionTop_Ten_triggered();

    void on_actionReset_Top_Ten_triggered();

private:
    const static int GRID_SIZE = 10;
    const static int MINES = 10;
    int numUncovered;
    //QString* names;
    //int* scores;
    std::vector<QString> names;
    std::vector<int> scores;
    Ui::MainWindow *ui;
    int mines_left;
    QTimer* timer;
    int elapsed_time;
    std::vector<Button*> buttons;
    bool found_images;
    std::vector<int> high_scores;
};

#endif // MAINWINDOW_H
