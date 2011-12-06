#ifndef BUTTON_H
#define BUTTON_H

#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QDir>

namespace Ui {
    class MainWindow;
}

class Button : public QPushButton
{
    enum btn_display { BLANK, MINE, Q_MARK, REVEALED };
    Q_OBJECT
private:
    btn_display display;
    int row;
    int col;
    bool mine;
    int num_mines_around;
    Ui::MainWindow *ui;
    QString path, zero, one, two, three, four, five, six, seven, eight, qmark, m;
    QIcon icZero, icOne, icTwo, icThree, icFour, icFive, icSix, icSeven, icEight, icQ, icM;
public:
    Button(QString text, QWidget *parent = 0);
    //get a pointer to MainWindow into the button
    void setUI(Ui::MainWindow *uiparam);
    //constructs a button at row, col, with size x and y
    Button(int row, int col, int x, int y, QString text, QWidget *parent);
    //sets the button display to a number
    void setNum(int a);
    //event for when mouse released on a button
    void mouseReleaseEvent(QMouseEvent* e);
    //when a button is rightclicked
    void right_clicked();
    //when button is leftclicked
    void left_clicked();
    //resets state of button
    void reset_btn();
    //return the row
    int get_row();
    //return the col
    int get_col();
    //returns number of mines surrounding button, assuming MainWindow->calc_mines() was called
    int get_num_surround_mines();
    //returns whether button has a mine
    bool has_mine();
    //sets a mine under the button
    void set_mine();
    //sets number of surrounding mines
    void set_num_mines(int a);
    //disables the button
    void disable();
    //enables the button
    void enable();
    ~Button();
    void setImgPathBtn(QString path_);
    QDir dir;
signals:
     void mine_marked();
     void mine_unmarked();
     void player_lose_signal();
     void mine_search_signal(Button* b);
};

#endif // BUTTON_H
