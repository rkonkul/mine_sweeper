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
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setImgPaths();
    QPixmap bg(path+"/images/dsknight.png");
    QPalette p(palette());
    p.setBrush(QPalette::Background, bg);
    setAutoFillBackground(true);
    setPalette(p);
    mines_left = MINES;

    QWidget::setWindowIcon(QIcon(QString(path+"/images/skull.png")));
    QWidget::setFixedSize(this->size());

    //initialize the high scores
    for(unsigned int i=0; i<10; i++) {
        scores.push_back(9999);
        names.push_back("noname");
    }
    //read in the high scores from the files
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
    //set the reset button icon
    ui->reset_button->setIcon(QIcon(okay));
    ui->reset_button->setStyleSheet( "background-color: rgba( 50, 50, 50, 60% ); color: white;" );
    ui->label_2->setStyleSheet("color: white;");
    ui->mine_left_label->setStyleSheet("color: white;");
    ui->mines_left_display->setStyleSheet("color: white;");
    ui->timer_label->setStyleSheet("color: white;");
}

void MainWindow::setImgPaths() {
   //get the current directory path
   path = dir.currentPath();
   okay = path + "/images/okay.jpg";

   QFile file(okay);
   if(file.exists()) {
       //set the reset button to okay
       ui->reset_button->setIcon(QIcon(okay));
   }
   //if the file does not exist, check other directories
   else {
       //go up a folder and check again
       path = dir.currentPath() + "../mine_sweeper";
       okay = path + "/images/okay.png";
       QFile file(okay);
       if(file.exists()) {
           //set the reset button to okay
           ui->reset_button->setIcon(QIcon(okay));
       }
       //if the file does not exist, go up again and check one more time
       else {
           path = dir.currentPath() + "../../mine_sweeper";
           okay = path + "/images/okay.png";
           QFile file(okay);
           if(file.exists()) {
               //set the reset button to okay
               ui->reset_button->setIcon(QIcon(okay));
           }
       }
   }
   //set the full path for x, mine, name, and score
   x = path + "/images/X.png";
   mine = path + "/images/mine.png";
   name = path + "/names.txt";
   score = path + "/scores.txt";

}

//reads in highscores from file
void MainWindow::read_in_highscores() {
    //create a file with the given location
    QFile file1(name);
    //if the file exists
    if(file1.open(QIODevice::ReadOnly | QIODevice::Text )) {
        //open the file and read in the names
        QTextStream in1( &file1 );
        QString line;
        for(int i = 0; i < 10; ++i) {
            line = in1.readLine();
            //store the names into the names vector
            if(line.size() > 0)
                names[i] = line;
        }
        //close the file
        file1.close();
    }
    //otherwise, create the file and write in noname for all names
    else {
        file1.open(QIODevice::ReadWrite);
        QTextStream in1( &file1 );
        QString line;
        for(int i = 0; i < 10; ++i) {
            in1 << "noname" << "\n";
        }
        //close the new file
        file1.close();
    }
    QFile file2(score);
    //if the file exists
    if(file2.open(QIODevice::ReadOnly | QIODevice::Text )) {
        //open the file and read in the scores
        QTextStream in2(&file2);
        for(int i = 0; i < 10; ++i) {
            //store the scores into the scores vector
             in2 >> scores[i];
        }
        //close the file
        file2.close();
    }
    //otherwise, create the file and write in 9999 for all scores
    else {
        file2.open(QIODevice::ReadWrite);
        QTextStream in2(&file2);
        for(int i = 0; i < 10; ++i) {
            in2 << "9999" << "\n";
        }
        //close the new file
        file2.close();
    }
}

void MainWindow::write_highscores() {
    //create a file with the given location
    QFile file1(name);
    //open the file
    file1.open(QIODevice::WriteOnly | QIODevice::Text );
    //for every name in the names vector, write the name to the names.txt file
    QTextStream in1( &file1 );
    QString line;
    for(int i = 0; i < 10; ++i) {
        in1 << names[i] << "\n";
    }
    //close the file
    file1.close();
    //create a file with the given location
    QFile file2(score);
    //open the file
    file2.open(QIODevice::WriteOnly | QIODevice::Text );
    //for every score in the scores vector, write the score to the scores.txt file
    QTextStream in2(&file2);
    for(int i = 0; i < 10; ++i) {
        in2 << scores[i] << "\n";
    }
    //close the file
    file2.close();

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
            p->setImgPathBtn(path);
        }
    }
    place_mines();
    calc_mines();
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
    //reset the reset button icon
    ui->reset_button->setIcon(QIcon(okay));

    elapsed_time = 0;
    numUncovered = 0;
    timer->start();
    ui->timer_label->setNum(0);
    //reset number of mines left
    mines_left = MINES;
    ui->mines_left_display->setNum(MINES);
    for(unsigned int i=0; i<buttons.size(); ++i) {
       buttons[i]->reset_btn();
       //reset the mine icons to an empty icon
       buttons[i]->setIcon(QIcon(""));
    }
    place_mines();
    calc_mines();
}

void MainWindow::player_lose() {
    ui->timer_label->setText("You lost.");
    //stop the timer, show the mines and the numbers around them
    timer->stop();
    show_num_mines();
    show_mines();
    //disable the buttons so that the player cannot keep clicking
    for(unsigned int i = 0; i < buttons.size(); ++i) {
        if(buttons.at(i)->has_mine()) {
            buttons.at(i)->disable();
            QIcon icon;
            icon.addPixmap(QPixmap(mine),QIcon::Disabled);
            buttons.at(i)->setIcon(icon);
        }
        else buttons.at(i)->disable();
    }
    //set the reset button icon
    ui->reset_button->setIcon(QIcon(x));
}

void MainWindow::rec_mine_search(Button *b) {
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
                rec_mine_search(other_btn);
            }
        }
    }
}

void MainWindow::mine_search(Button* b) {
    rec_mine_search(b);
    //check if player has won
    bool won = true;
       for(unsigned int i=0; i<buttons.size(); i++) {
           if(!buttons[i]->has_mine() && buttons[i]->isEnabled()) {
               won = false;
           }
       }
       if(won) {
           player_won();
       }
}

void MainWindow::player_won() {
    //stop the timer
    timer->stop();
    //if the user's time is faster than the slowest score, there is a new high score
    if(elapsed_time <= scores[9]) {
        //for every score, check to see if the user's score is better or equal
        for(int i = 0; i < 10; ++i) {
            //if the user's score is better or equal, ask the user for their name, insert their score/name
            //above the lower/equal score/name, and delete the lowest score/name
            if(elapsed_time <= scores[i]) {
                bool ok;
                QString text = QInputDialog::getText(this, tr("New High Score!"),
                                                      tr("Enter your name:"), QLineEdit::Normal,
                                                      QDir::home().dirName(), &ok);
                names.insert(names.begin() + i, text);
                names.pop_back();
                scores.insert(scores.begin() + i, elapsed_time);
                scores.pop_back();
                //write the scores to the files
                write_highscores();
                //exit the loop
                return;
            }
        }
    }
}

void MainWindow::show_mines() {
    for(unsigned int i=0; i<buttons.size(); ++i) {
        if(buttons[i]->has_mine()) {
            buttons[i]->setIcon(QIcon(mine));
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
    QMessageBox msgBox;
    msgBox.setWindowTitle("Top Ten");
    msgBox.setText("1.  " + names[0] + ": " + QString::number(scores[0]) + " seconds\n" +
                   "2.  " + names[1] + ": " + QString::number(scores[1]) + " seconds\n" +
                   "3.  " + names[2] + ": " + QString::number(scores[2]) + " seconds\n" +
                   "4.  " + names[3] + ": " + QString::number(scores[3]) + " seconds\n" +
                   "5.  " + names[4] + ": " + QString::number(scores[4]) + " seconds\n" +
                   "6.  " + names[5] + ": " + QString::number(scores[5]) + " seconds\n" +
                   "7.  " + names[6] + ": " + QString::number(scores[6]) + " seconds\n" +
                   "8.  " + names[7] + ": " + QString::number(scores[7]) + " seconds\n" +
                   "9.  " + names[8] + ": " + QString::number(scores[8]) + " seconds\n" +
                   "10. " + names[9] + ": " + QString::number(scores[9]) + " seconds");
    msgBox.setStyleSheet("background-color: rgba( 10, 10, 10, 100% ); color: white;");
    msgBox.setWindowIcon(QIcon(QString(path+"/images/skull.png")));
    msgBox.exec();
}

void MainWindow::on_actionExit_triggered() {
    write_highscores();
    exit(0);
}

void MainWindow::on_actionReset_Top_Ten_triggered() {
    for(unsigned int i=0; i<scores.size(); i++) {
        scores[i] = 9999;
        names[i] = "noname";
    }
    write_highscores();
}

void MainWindow::on_actionHelp_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Help");
    msgBox.setText("You can uncover a square by clicking it. If you uncover a mine, you lose the game.\n"
                   "\nIf a number appears on a square, it indicates how many total mines are in the eight "
                   "squares that surround the numbered one. You can use this number to help deduce whether "
                   "a square is safe to uncover.\n\nTo mark a square you suspect contains a mine, "
                   "right-click it. This will add a M to the square. If you're not sure, right-click it "
                   "again, which will add a question mark to the square.");
    msgBox.setStyleSheet("background-color: rgba( 10, 10, 10, 100% ); color: white;");
    msgBox.setWindowIcon(QIcon(QString(path+"/images/skull.png")));
    msgBox.exec();
}

void MainWindow::on_actionAbout_triggered() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("About");
    msgBox.setText("Authors: Ryan Konkul(rkonku2) and Scott Prentice(sprent2)\n\nMinesweeper - Project 4\n"
                   "CS340 Fall 2011 - Professor Troy\n11/10/2011");
    msgBox.setStyleSheet("background-color: rgba( 10, 10, 10, 100% ); color: white;");
    msgBox.setWindowIcon(QIcon(QString(path+"/images/skull.png")));
    msgBox.exec();
}
