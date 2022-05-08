#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("pac-man"));

    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);


}


/* Initialize UI */
void MainWindow::initLabels()
{
    score_title = new QLabel(this);
    score_title->setText("score");
    score_title->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score_title->setGeometry(50, 12, 60, 26);

    score = new QLabel(this);
    score->setIndent(-80);
    score->setText("0");
    score->setStyleSheet("QLabel {font-family: Fixedsys;color: white;font-size: 16px;}");
    score->setGeometry(110, 12, 150, 26);

    win_label = new QLabel(this);
    win_label->hide();
    win_label->setText("You win!");
    win_label->setStyleSheet("QLabel {font-family: Fixedsys;color: yellow;font-size: 16px;}");
    win_label->setGeometry(310, 12, 150, 26);

    lose_label = new QLabel(this);
    lose_label->hide();
    lose_label->setText("You lose!");
    lose_label->setStyleSheet("QLabel {font-family: Fixedsys;color: red;font-size: 16px;}");
    lose_label->setGeometry(310, 12, 150, 26);

    score_timer = new QTimer(this);
    score_timer->start(25);
    connect(score_timer, SIGNAL(timeout()), this , SLOT(update_score()));
}


/* Update score UI */




void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:
        game->pacman_next_direction(GameObject::Up);
        break;
    case Qt::Key_A:
        game->pacman_next_direction(GameObject::Left);
        break;
    case Qt::Key_S:
        game->pacman_next_direction(GameObject::Down);
        break;
    case Qt::Key_D:
        game->pacman_next_direction(GameObject::Right);
        break;
    case Qt::Key_I:
        game->pacmanTwo_next_direction(GameObject::Up);
        break;
    case Qt::Key_J:
        game->pacmanTwo_next_direction(GameObject::Left);
        break;
    case Qt::Key_K:
        game->pacmanTwo_next_direction(GameObject::Down);
        break;
    case Qt::Key_L:
        game->pacmanTwo_next_direction(GameObject::Right);
        break;
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::beginGame(int mode){


}

void MainWindow::on_onePlayer_clicked()
{
    int map_height = 21, map_width = 33;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_twoPlayer_clicked()
{
    int map_height = 35, map_width = 35;            // 20x29 game map
    int x = 35, y = 35;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);
    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/versus.txt",true);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}

void MainWindow::on_levelOne_clicked()
{
    int map_height = 21, map_width = 33;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_levelTwo_clicked()
{
    int map_height = 17, map_width = 55;            // 20x29 game map
    int x = 18, y = 68;                       // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/level2.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_levelThree_clicked()
{
    int map_height = 24, map_width = 28;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/level3.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_levelFour_clicked()
{
    int map_height = 20, map_width = 29;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_levelFive_clicked()
{
    int map_height = 20, map_width = 29;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_boss_clicked()
{
    int map_height = 20, map_width = 29;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (map_width * GameObject::Width);
    int h = (map_height * GameObject::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, map_width, map_height, ":/game_objects/map_objects/map.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_takeBreak_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley"));
}

