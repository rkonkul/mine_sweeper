#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Button.h"
#include <QGridLayout>
#include <QBitmap>
#include <QMouseEvent>

namespace Ui {
    class MainWindow;
}

void Button::setUI (Ui::MainWindow *uiparam) {
    ui = uiparam;
}

void Button::setNum(int a) {
    QString f;
    f.setNum(a);
    this->setText(f);
}

void Button::mouseReleaseEvent(QMouseEvent* e) {
    QString f, g;
    f.setNum(get_row());
    g.setNum(get_col());
    ui->label->setText(f);
    ui->label_2->setText(g); //debug stuff

    if (e->button() == Qt::RightButton)  {
        ui->label_3->setText("rightbutton");
        right_clicked();
    }
    else if (e->button() == Qt::LeftButton) {
         ui->label_3->setText("leftbutton");
         left_clicked();
    }
    //for some reason, button sticks
    //so push it back up
    this->setDown(false);
}

void Button::right_clicked() {
    if(this->display == BLANK) {
        display = MINE;
        this->setText("M");
        //emit signal since mine was marked
        emit mine_marked();
    }
    else if(this->display == MINE) {
        display = Q_MARK;
        this->setText("?");
        emit mine_unmarked();
    }
    else if(this->display == Q_MARK) {
        display = BLANK;
        this->setText("");
    }
}

void Button::left_clicked() {
    if(this->display == MINE || this->display == Q_MARK)
    {
        //ignore the input
    }
    else if(this->has_mine()) {
        //clicked on mine game over
        this->setText("BOOM");
        emit player_lose_signal();
    }
    else {
        this->display = REVEALED;
        emit mine_search_signal(this);
    }
}

Button::Button(QString text, QWidget *parent)
    : QPushButton(text, parent)
{
    display = BLANK;
    mine = false;
}
Button::Button(int row, int col, int x, int y, QString text, QWidget *parent)
    :QPushButton(text, parent)
{
    //save off the row and col
    this->row = row;
    this->col = col;
    //set position and size
    this->setGeometry(row*35+x, col*35+y, 35, 35);
    //intialize state
    display = BLANK;
    mine = false;
    num_mines_around = 0;
}

void Button::reset_btn() {
    display = BLANK;
    mine = false;
    setText("");
    setEnabled(true);
}

int Button::get_row() {
    return row;
}

int Button::get_col() {
    return col;
}

int Button::get_num_surround_mines() {
    return num_mines_around;
}

bool Button::has_mine() {
    return mine;
}

void Button::set_mine() {
    mine = true;
}

void Button::set_num_mines(int a) {
    num_mines_around = a;
}

void Button::disable() {
    this->setEnabled(false);
}

Button::~Button()
{
}

