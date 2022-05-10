#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioOutput>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("CSE 165: Pacman"));

    ui->graphicsView->setStyleSheet("QGraphicsView {border: none;}");
    ui->graphicsView->setBackgroundBrush(Qt::black);
    ui->graphicsView->setFocusPolicy(Qt::NoFocus);

     ui->scoreLabel->setVisible(false);
      ui->score->setVisible(false);

      ui->playerOne->setVisible(false);
       ui->playerOneScore->setVisible(false);

       ui->playerTwo->setVisible(false);
        ui->playerTwoScore->setVisible(false);
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


void MainWindow::keyPressEvent(QKeyEvent *e) {
    if(game->pacman->lost == true){
        ShowLabels();
    }
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
    int height = 21, width = 33;
    int x = 230, y = 50;
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level1.txt", false);
    ui->graphicsView->setScene(game);

    game->start();
}
void MainWindow::HideLabels(){

    scoreTimer = new QTimer(this);
    scoreTimer->start(25);
    connect(scoreTimer, SIGNAL(timeout()), this , SLOT(updateBallCount()));

    ui->scoreLabel->setVisible(true);
     ui->score->setVisible(true);
     ui->graphicsView->setVisible(true);
    ui->onePlayer->setVisible(false);
    ui->twoPlayer->setVisible(false);
    ui->levelOne->setVisible(false);
    ui->levelTwo->setVisible(false);
    ui->levelThree->setVisible(false);
    ui->takeBreak->setVisible(false);
    ui->label->setVisible(false);
    ui->graphicsView_2->setVisible(false);
}
void MainWindow::ShowLabels(){

    ui->graphicsView->setVisible(false);
    ui->onePlayer->setVisible(true);
    ui->twoPlayer->setVisible(true);
    ui->levelOne->setVisible(true);
    ui->levelTwo->setVisible(true);
    ui->levelThree->setVisible(true);
    ui->takeBreak->setVisible(true);
    ui->label->setVisible(true);
    ui->graphicsView_2->setVisible(true);
}

void MainWindow::on_twoPlayer_clicked()
{

    ui->playerOne->setVisible(true);
     ui->playerOneScore->setVisible(true);

     ui->playerTwo->setVisible(true);
      ui->playerTwoScore->setVisible(true);

      HideLabels();
      int height = 21, width = 33;
      int x = 230, y = 50;
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);
    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/versus.txt",true);
    ui->graphicsView->setScene(game);

    game->start();
}

void MainWindow::on_levelOne_clicked()
{
     PlayMusic();
      HideLabels();
    int height = 21, width = 33;
   int x = 230, y = 50;
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level1.txt", false);
    ui->graphicsView->setScene(game);

    game->start();
}


void MainWindow::on_levelTwo_clicked()
{
     PlayMusic();
      HideLabels();
    int height = 17, width = 55;
    int x = 18, y = 68;
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);

    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level2.txt", false);
    ui->graphicsView->setScene(game);

    game->start();
}


void MainWindow::on_levelThree_clicked()
{
     PlayMusic();
      HideLabels();
    int height = 24, width = 28;
    int x = 50, y = 50;
    int w = (width * GameItem::Width);
    int h = (height * GameItem::Width);
    ui->graphicsView->setGeometry(x, y, w, h);
    game = new Game(x, y, width, height, ":/game_objects/map_objects/level3.txt", false);
    ui->graphicsView->setScene(game);
    game->start();
}

void MainWindow::updateBallCount(){
    ui->score->setText(QString::number(game->ballsLeft));
    if(game->versus){
        ui->playerOneScore->setText(QString::number(game->pacman->pointsGrabbed));
        ui->playerTwoScore->setText(QString::number(game->pacmanTwo->pointsGrabbed));
    }
}
void MainWindow::on_takeBreak_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.youtube.com/watch?v=dQw4w9WgXcQ&ab_channel=RickAstley"));
}

