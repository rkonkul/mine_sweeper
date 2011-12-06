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

void Button::setImgPathBtn(QString path_) {
    path = path_;
    //set the full path for all numbers
    zero = path + "/images/zero.png";
    one = path + "/images/one.png";
    two = path + "/images/two.png";
    three = path + "/images/three.png";
    four = path + "/images/four.png";
    five = path + "/images/five.png";
    six = path + "/images/six.png";
    seven = path + "/images/seven.png";
    eight = path + "/images/eight.png";
    qmark = path + "/images/qmark.png";
    m = path + "/images/m.png";
    icZero.addPixmap(QPixmap(zero),QIcon::Disabled);
    icOne.addPixmap(QPixmap(one),QIcon::Disabled);
    icTwo.addPixmap(QPixmap(two),QIcon::Disabled);
    icThree.addPixmap(QPixmap(three),QIcon::Disabled);
    icFour.addPixmap(QPixmap(four),QIcon::Disabled);
    icFive.addPixmap(QPixmap(five),QIcon::Disabled);
    icSix.addPixmap(QPixmap(six),QIcon::Disabled);
    icSeven.addPixmap(QPixmap(seven),QIcon::Disabled);
    icEight.addPixmap(QPixmap(eight),QIcon::Disabled);
    icQ.addPixmap(QPixmap(qmark),QIcon::Disabled);
    icM.addPixmap(QPixmap(m),QIcon::Disabled);
}

void Button::setNum(int a) {
    switch(a) {
        case 0:
            this->setIcon(icZero);
            break;
        case 1:
            this->setIcon(icOne);
            break;
        case 2:
            this->setIcon(icTwo);
         break;
        case 3:
            this->setIcon(icThree);
            break;
        case 4:
            this->setIcon(icFour);
            break;
        case 5:
            this->setIcon(icFive);
            break;
        case 6:
            this->setIcon(icSix);
            break;
        case 7:
            this->setIcon(icSeven);
            break;
        case 8:
            this->setIcon(icEight);
            break;
    }
}

void Button::mouseReleaseEvent(QMouseEvent* e) {
    if (e->button() == Qt::RightButton)  {
        right_clicked();
    }
    else if (e->button() == Qt::LeftButton) {
         left_clicked();
    }
    //for some reason, button sticks
    //so push it back up
    this->setDown(false);
}

void Button::right_clicked() {
    if(this->display == BLANK) {
        display = MINE;
        this->setIcon(icM);
        //emit signal since mine was marked
        emit mine_marked();
    }
    else if(this->display == MINE) {
        display = Q_MARK;
        this->setIcon(icQ);
        emit mine_unmarked();
    }
    else if(this->display == Q_MARK) {
        display = BLANK;
        this->setIcon(QIcon(""));
    }
}

void Button::left_clicked() {
    if(this->display == MINE || this->display == Q_MARK)
    {
        //ignore the input
    }
    else if(this->has_mine()) {
        //clicked on mine game over
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
    enable();
}

void Button::reset_btn() {
    display = BLANK;
    mine = false;
    setText("");
    enable();
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
    setStyleSheet("background-color: rgba( 100, 100, 100, 80% ); border: 1px solid #8f8f91; color: white;" );
}

void Button::enable() {
    this->setEnabled(true);
    setStyleSheet( "background-color: rgba( 20, 20, 20, 65% ); border: 1px solid #8f8f91; color: white;" );
}

Button::~Button()
{
}

