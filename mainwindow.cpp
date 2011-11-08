#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Button.h"
#include <QGridLayout>
#include <QBitmap>
#include <QMouseEvent>
#include <QTimer>
#include <ctime>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDataStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mines_left = MINES;

    //intialize high scores and names
    for(int i=0; i<10; i++) {
        scores.push_back(9999);
        names.push_back("noname");
    }
    read_in_highscores();
    //construct and display the grid
    prepare_grid(50, 100, GRID_SIZE, this);
    //initialize counter for number of tiles uncovered
    numUncovered = 0;
    //initialize timer
    elapsed_time = 0;
    timer = new QTimer(this);
    timer->start(1000);
    connect (timer, SIGNAL(timeout()), this, SLOT(update_timer()));
}

//reads in highscores from file
void MainWindow::read_in_highscores() {
    QFile file1("./names.txt");
    file1.open(QIODevice::ReadOnly | QIODevice::Text );
    QTextStream in1(&file1);
    QString line;
    for(int i = 0; i < 10; ++i) {
        line = in1.readLine();
        if(line.size() > 0)
            names[i] = line;
    }
    file1.close();

    QFile file2("./scores.txt");
    file2.open(QIODevice::ReadOnly | QIODevice::Text );
    QDataStream in2(&file2);
    for(int i = 0; i < 10; ++i) {
    //     in2 >> scores[i];
    }
    file2.close();

}

void MainWindow::write_highscores() {

}

void MainWindow::prepare_grid(int top_left_x, int top_left_y, int grid_size, QWidget *parent) {
    srand(time(NULL));
    for(int i=0; i<grid_size; ++i) {
        for(int j=0; j<grid_size; ++j) {
            //create and display the button
            Button* p = new Button(i, j, top_left_x, top_left_y, "", parent);
            //connect signals
            QObject::connect(p, SIGNAL(mine_marked()), this, SLOT(decrement_mines_left()));
            QObject::connect(p, SIGNAL(mine_unmarked()), this, SLOT(increment_mines_left()));
            QObject::connect(p, SIGNAL(player_lose_signal()), this, SLOT(player_lose()));
            QObject::connect(p, SIGNAL(mine_search_signal(Button*)), this, SLOT(mine_search(Button*)));
            p->setUI(ui);
            //add button to vector
            buttons.push_back(p);
        }
    }
    place_mines();
    calc_mines();
    found_images = false;
    QPixmap p;
    p.load("images/mine.png", "PNG", 0);
    if(p.isNull()) {
        ui->plainTextEdit->appendPlainText("Could not find images");
    }
    ui->label->setPixmap(p);
}

void MainWindow::place_mines() {
    int mine_count=0;
    while(mine_count < MINES) {
        //pick a random button
        int r = rand() % (GRID_SIZE*GRID_SIZE);
        //make sure it doesn't already have a mine
        if(!buttons[r]->has_mine()) {
            ++mine_count;
            buttons[r]->set_mine();
        }
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::increment_mines_left() {
    mines_left++;
    ui->mines_left_display->setNum(mines_left);
}

void MainWindow::decrement_mines_left() {
    mines_left--;
    ui->mines_left_display->setNum(mines_left);
}

void MainWindow::reset() {
    elapsed_time = 0;
    numUncovered = 0;
    timer->start();
    ui->timer_label->setNum(0);
    //reset number of mines left
    mines_left = MINES;
    ui->mines_left_display->setNum(MINES);
    for(unsigned int i=0; i<buttons.size(); ++i) {
       buttons[i]->reset_btn();
    }
    place_mines();
    calc_mines();
}

void MainWindow::player_lose() {
    ui->plainTextEdit->appendPlainText("player_lose()");
    ui->timer_label->setText("you lost");
    timer->stop();
    show_mines();
}

void MainWindow::mine_search(Button* b) {
    ++numUncovered;
    //disable and display mines
    b->disable();
    b->setNum(b->get_num_surround_mines());
    //if it is a zero button
    if(b->get_num_surround_mines() == 0) {
        //go searching
        //also reveal those around the '0'
        for(direction j = TOPLEFT; j <= BOTTOMRIGHT; j++) { //for all directions
            Button* other_btn = move_dir(b, j);
            //if not out of bounds and not already disabled
            if(b != other_btn && other_btn->isEnabled()) {
                //recurse on the direction
                mine_search(other_btn);
            }
        }
    }
    ui->plainTextEdit->appendPlainText("mine_search()");
    //check if player has won
    if(numUncovered == GRID_SIZE*GRID_SIZE - MINES)
        player_won();
}

void MainWindow::player_won() {
    ui->plainTextEdit->appendPlainText("player won!");
    timer->stop();
    write_highscores();
}

void MainWindow::show_mines(){
    for(unsigned int i=0; i<buttons.size(); ++i) {
        if(buttons[i]->has_mine()) {
            buttons[i]->setText("mine");
        }
    }
}

Button* MainWindow::get_button(int row, int col) {
    for(unsigned int i=0; i<buttons.size(); ++i) {
        if(buttons[i]->get_row() == row && buttons[i]->get_col() == col) {
            return buttons[i];
        }
    }
    return NULL;
}

void MainWindow::calc_mines() {
    int num_mines;
    for(unsigned int i=0; i<buttons.size(); ++i) {
        num_mines = 0;
        for(direction j = TOPLEFT; j <= BOTTOMRIGHT; j++) { //for all directions
            if(surround_mine(buttons[i], j)) {
                num_mines++;
            }
        }
        buttons[i]->set_num_mines(num_mines);
    }
}

bool MainWindow::surround_mine(Button* b, direction dir) {
    int row, col;
    row = b->get_row();
    col = b->get_col();
    int other_row, other_col;
    other_row = row;
    other_col = col;
    if(dir == TOPLEFT) {
        if(row == 0 || col == 0) return false;
        other_row--;
        other_col--;
    }
    else if(dir == TOP) {
        if(row == 0) return false;
        other_row--;
    }
    else if(dir == TOPRIGHT) {
        if(row == 0 || col == GRID_SIZE-1) return false;
        other_row--;
        other_col++;
    }
    else if(dir == RIGHT) {
        if(col == GRID_SIZE-1) return false;
        other_col++;
    }
    else if(dir == BOTTOMRIGHT) {
        if(row == GRID_SIZE-1 || col == GRID_SIZE-1) return false;
        other_row++;
        other_col++;
    }
    else if(dir == BOTTOM) {
        if(row == GRID_SIZE-1) return false;
        other_row++;
    }
    else if(dir == BOTTOMLEFT) {
        if(row == GRID_SIZE-1 || col == 0) return false;
        other_row++;
        other_col--;
    }
    else if(dir == LEFT) {
        if(col == 0) return false;
        other_col--;
    }
    Button* other_button = get_button(other_row, other_col);
    if(other_button == NULL) {
        ui->label_3->setText("null pointer in surround_mine()");
    }
    if(other_button != NULL && other_button->has_mine())
        return true;
    return false;
}

Button* MainWindow::move_dir(Button* b, direction dir) {
    int row, col;
    row = b->get_row();
    col = b->get_col();
    int other_row, other_col;
    other_row = row;
    other_col = col;
    if(dir == TOPLEFT) {
        if(row == 0 || col == 0) return b;
        other_row--;
        other_col--;
    }
    else if(dir == TOP) {
        if(row == 0) return b;
        other_row--;
    }
    else if(dir == TOPRIGHT) {
        if(row == 0 || col == GRID_SIZE-1) return b;
        other_row--;
        other_col++;
    }
    else if(dir == RIGHT) {
        if(col == GRID_SIZE-1) return b;
        other_col++;
    }
    else if(dir == BOTTOMRIGHT) {
        if(row == GRID_SIZE-1 || col == GRID_SIZE-1) return b;
        other_row++;
        other_col++;
    }
    else if(dir == BOTTOM) {
        if(row == GRID_SIZE-1) return b;
        other_row++;
    }
    else if(dir == BOTTOMLEFT) {
        if(row == GRID_SIZE-1 || col == 0) return b;
        other_row++;
        other_col--;
    }
    else if(dir == LEFT) {
        if(col == 0) return b;
        other_col--;
    }
    Button* other_button = get_button(other_row, other_col);
    if(other_button == NULL) {
        ui->label_3->setText("null pointer in move_dir()");
    }
    return other_button;
}

void MainWindow::show_num_mines() {
    for(unsigned int i=0; i<buttons.size(); i++) {
        buttons[i]->setNum(buttons[i]->get_num_surround_mines());
    }
}

void MainWindow::update_timer() {
    ++elapsed_time;
    ui->timer_label->setNum(elapsed_time);
}

void MainWindow::on_actionReset_triggered() {
    reset();
}

void MainWindow::on_actionTop_Ten_triggered(){
    QString f;
    f.setNum(scores[4]);
    ui->plainTextEdit->appendPlainText(f);
    QMessageBox msgBox;
    msgBox.setText("1.  " + names[0] + " " + QString::number(scores[0]) + " seconds\n" +
                   "2.  " + names[1] + " " + QString::number(scores[1]) + " seconds\n" +
                   "3.  " + names[2] + " " + QString::number(scores[2]) + " seconds\n" +
                   "4.  " + names[3] + " " + QString::number(scores[3]) + " seconds\n" +
                   "5.  " + names[4] + " " + QString::number(scores[4]) + " seconds\n" +
                   "6.  " + names[5] + " " + QString::number(scores[5]) + " seconds\n" +
                   "7.  " + names[6] + " " + QString::number(scores[6]) + " seconds\n" +
                   "8.  " + names[7] + " " + QString::number(scores[7]) + " seconds\n" +
                   "9.  " + names[8] + " " + QString::number(scores[8]) + " seconds\n" +
                   "10. " + names[9] + " " + QString::number(scores[9]) + " seconds");
    msgBox.exec();
}

void MainWindow::on_actionExit_triggered() {
    exit(0);
}

void MainWindow::on_actionReset_Top_Ten_triggered() {
    for(unsigned int i=0; i<scores.size(); i++) {
        scores[i] = 9999;
        names[i] = "noname";
    }
    write_highscores();
}
