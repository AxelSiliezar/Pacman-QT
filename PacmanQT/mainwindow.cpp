#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioOutput>
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

void MainWindow::PlayMusic(){
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput * audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    player->setSource(QUrl("qrc:/ui/pacman.wav"));
    audioOutput->setVolume(50);
    player->play();
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
void MainWindow::keyPressEvent(QKeyEvent *e) {
    switch (e->key()) {
    case Qt::Key_W:

        for (int i = 0; i < 20; i++){
            game->pacman->move(1);
        }

        break;
    case Qt::Key_A:
        for (int i = 0; i < 20; i++){
            game->pacman->move(2);
        }

        break;
    case Qt::Key_S:
        for (int i = 0; i < 20; i++){
            game->pacman->move(3);
        }

        break;
    case Qt::Key_D:

        for (int i = 0; i < 20; i++){
            game->pacman->move(4);
        }


        break;
    case Qt::Key_I:
        for (int i = 0; i < 20; i++){
            game->pacmanTwo->move(1);
        }

        break;
    case Qt::Key_J:
        for (int i = 0; i < 20; i++){
            game->pacmanTwo->move(2);
        }

        break;
    case Qt::Key_K:
        for (int i = 0; i < 20; i++){
            game->pacmanTwo->move(3);
        }

        break;
    case Qt::Key_L:
        for (int i = 0; i < 20; i++){
            game->pacmanTwo->move(4);
        }

        break;
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_onePlayer_clicked()
{

    PlayMusic();
    HideLabels();
    int height = 21, width = 33;            // 20x29 game map
    int x = 230, y = 50;                             // x y in mainwindow
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level1.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}
void MainWindow::HideLabels(){
    ui->onePlayer->setVisible(false);
    ui->twoPlayer->setVisible(false);
    ui->levelOne->setVisible(false);
    ui->levelTwo->setVisible(false);
    ui->levelThree->setVisible(false);
    ui->takeBreak->setVisible(false);
    ui->label->setVisible(false);
    ui->graphicsView_2->setVisible(false);
}

void MainWindow::on_twoPlayer_clicked()
{
      HideLabels();
    int height = 35, width = 35;            // 20x29 game map
    int x = 35, y = 35;                             // x y in mainwindow
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);
    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/versus.txt",true);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}

void MainWindow::on_levelOne_clicked()
{
     PlayMusic();
      HideLabels();
    int height = 21, width = 33;            // 20x29 game map
    int x = 400, y = 200;                             // x y in mainwindow
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level1.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_levelTwo_clicked()
{
     PlayMusic();
      HideLabels();
    int height = 17, width = 55;            // 20x29 game map
    int x = 18, y = 68;                       // x y in mainwindow
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level2.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}


void MainWindow::on_levelThree_clicked()
{
     PlayMusic();
      HideLabels();
    int height = 24, width = 28;            // 20x29 game map
    int x = 50, y = 50;                             // x y in mainwindow
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);
    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level3.txt", false);
    ui->graphicsView->setScene(game);
    initLabels();
    game->start();
}
void MainWindow::on_takeBreak_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley"));
}

