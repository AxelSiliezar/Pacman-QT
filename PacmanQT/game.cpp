#include "game.h"
#include <QString>
#include <QFile>
#include <QRandomGenerator>
#define W (GameItem::Width)
#include "mainwindow.h"

// interval number before ghosts going out the cage
int GHOST_RELEASE_TIME[] = {0, 200, 400, 600};
class MainWindow;
Game::Game(int x, int y, int map_w, int map_h, QString map_src, bool twoPlayer)
    : QGraphicsScene(x, y, W * map_w, W * map_h)
{

    map_x = x;
    map_y = y;
    versus = twoPlayer;

    map_size = map_w * map_h;
    map_width = map_w;
    map_height = map_h;
    map = new GameItem**[map_height];
    for (int i = 0; i < map_height; i++) {
        map[i] = new GameItem*[map_width];
        for (int j = 0; j < map_width; j++)
            map[i][j] = nullptr;
    }


    ballsLeft = eat_num = score = 0;
    int ghostCount = 0;
    QPixmap wallpix(":/game_objects/map_objects/wall.png");
    QPixmap redWallpix(":/game_objects/map_objects/redWall.png");
    QPixmap yellowWallpix(":/game_objects/map_objects/yellow.png");
    QPixmap ballpix(":/game_objects/map_objects/dot.png");
    QPixmap powerballpix(":/game_objects/map_objects/power_ball.png");
    QPixmap gatepix(":/game_objects/map_objects/gate.png");
    QPixmap jurybox(":/game_objects/map_objects/redWall.png");
    QPixmap blankpix;
    QFile mapfile(map_src);
    mapfile.open(QIODevice::ReadOnly|QIODevice::Text);

    pacman = new Pacman();
    if(versus){
    pacmanTwo = new Pacman();
    }
    qDebug() << versus;
    for (int i = 0; i < map_h; i++) {
        QByteArray line = mapfile.readLine();
        for (int j = 0; j < map_w; j++) {
            int tmp_x = x + (j * W);
            int tmp_y = y + (i * W);
            switch (line[j]) {
            case '1':
                    map[i][j] = new GameItem(GameItem::Wall, wallpix);
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                break;
            case 'y':
                if(versus){
                   map[i][j] = new GameItem(GameItem::Wall, yellowWallpix);
                }else{
                    map[i][j] = new GameItem(GameItem::Wall, yellowWallpix);
                }

                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                break;
            case '0':
                map[i][j] = new GameItem(GameItem::Ball, ballpix);
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                ballsLeft++;
                break;
            case '4':
                map[i][j] = new GameItem(GameItem::PowerBall, powerballpix);
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                powerball.push_back(map[i][j]);
                ballsLeft++;
                break;
            case '3':
                map[i][j] = new GameItem(GameItem::Blank, blankpix);
                break;
            case '2':
                gate = new GameItem(GameItem::Gate, gatepix);
                gate->_x = j;
                gate->_y = i;
                gate->setPos(tmp_x, tmp_y);
                addItem(gate);
                map[i][j] = gate;
                break;
            case 'p':
                pacman = new Pacman();
                pacman->game = this;
                pacman->setZValue(2);
                pacman->setPos(tmp_x, tmp_y);
                addItem(pacman);
                map[i][j] = pacman;
                break;
            case 'g':
                if(!versus){

                map[i][j] = new GameItem(GameItem::Blank, blankpix);
                ghost[ghostCount] = new Ghost(ghostCount);
                ghost[ghostCount]->game = this;
                ghost[ghostCount]->setZValue(2);
                ghost[ghostCount]->_x = j;
                ghost[ghostCount]->_y = i;
                ghost[ghostCount]->setPos(tmp_x, tmp_y);
                addItem(ghost[ghostCount]);
                ghostCount++;
                }
                break;
            case 'x':
                if(versus){
                pacmanTwo = new Pacman();
                pacmanTwo->game = this;
                pacmanTwo->setZValue(2);
                pacmanTwo->setPos(tmp_x, tmp_y);
                addItem(pacmanTwo);
                map[i][j] = pacmanTwo;
                }
                break;
            }



        }
    }


}


void Game::start()
{
    int temp = 0;

    powerball_flash_timer = new QTimer(this);
    connect(powerball_flash_timer, SIGNAL(timeout()), this , SLOT(powerball_flash()));
    powerball_flash_timer->start(FLASH_INTERVAL);


    if(!versus){
    for (int i = 0; i < Ghost::GhostNum; i++) {
        ghost_timer[i] = new QTimer(this);
        connect(ghost_timer[i], &QTimer::timeout, [=](){ghostTimer(i);} );
        ghost_timer[i]->start(NORMAL_INTERVAL);
    }
    }
}


void Game::stop()
{
    pacman->lost = true;
    if(!versus){
    for (int i = 0; i < Ghost::GhostNum; i++) {
        ghost_timer[i]->stop();
    }
    }
}


void Game::powerball_flash()
{
    if (powerball.empty()) {
        powerball_flash_timer->stop();
        return;
    }

    if (flash_tick) {
        for (int i = 0; i < powerball.size(); i++) {
            powerball.at(i)->hide();
        }
        flash_tick = 0;
    } else {
        for (int i = 0; i < powerball.size(); i++) {
            powerball.at(i)->show();
        }
        flash_tick = 1;
    }
}



void Game::ghostTimer(int temp)
{
    if(!versus){


    ghost[temp]->ghostRandomScript();
}
}


int Game::get_score()
{
    return score;
}

Game::~Game()
{
    for (int i = 0; i < map_height; i++) {
        for (int j = 0; j < map_width; j++) {
            if (map[i][j] != nullptr)
                delete map[i][j];
        }
        delete[] map[i];
    }
    delete[] map;
    delete powerball_flash_timer;
    if(!versus){


    for (int i = 0; i < Ghost::GhostNum; i++) {
        delete ghost_timer[i];
    }
    }
}
