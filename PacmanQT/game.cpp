#include "game.h"
#include <QString>
#include <QFile>
#include <QRandomGenerator>
#define W (GameObject::Width)


// interval number before ghosts going out the cage
int GHOST_RELEASE_TIME[] = {0, 200, 400, 600};

Game::Game(int x, int y, int map_w, int map_h, QString map_src, bool twoPlayer)
    : QGraphicsScene(x, y, W * map_w, W * map_h)
{

    geo_x = x;
    geo_y = y;
    stat = Playing;
    versus = twoPlayer;
    /* Initialize map pointers */
    map_size = map_w * map_h;
    map_width = map_w;
    map_height = map_h;
    map = new GameObject**[map_height];
    for (int i = 0; i < map_height; i++) {
        map[i] = new GameObject*[map_width];
        for (int j = 0; j < map_width; j++)
            map[i][j] = nullptr;
    }

    /* Initialize map graphics */
    ball_num = eat_num = score = 0;
    int ghostCount = 0;
    QPixmap wallpix(":/game_objects/map_objects/wall.png");
    QPixmap redWallpix(":/game_objects/map_objects/redWall.png");
    QPixmap yellowWallpix(":/game_objects/map_objects/yellow.png");
    QPixmap ballpix(":/game_objects/map_objects/dot.png");
    QPixmap powerballpix(":/game_objects/map_objects/power_ball.png");
    QPixmap gatepix(":/game_objects/map_objects/gate.png");
    QPixmap blankpix;
    QFile mapfile(map_src);
    mapfile.open(QIODevice::ReadOnly|QIODevice::Text);

    pacman = new Pacman();
    pacmanTwo = new PacmanTwo();
    for (int i = 0; i < map_h; i++) {
        QByteArray line = mapfile.readLine();
        for (int j = 0; j < map_w; j++) {
            int tmp_x = x + (j * W);
            int tmp_y = y + (i * W);
            switch (line[j]) {
            case '1':
                if(versus){
                   map[i][j] = new GameObject(GameObject::Wall, redWallpix);
                }else{
                    map[i][j] = new GameObject(GameObject::Wall, wallpix);
                }

                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                break;
            case 'y':
                if(versus){
                   map[i][j] = new GameObject(GameObject::Wall, yellowWallpix);
                }else{
                    map[i][j] = new GameObject(GameObject::Wall, yellowWallpix);
                }

                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                break;
            case '0':
                if(versus){
                  map[i][j] = new GameObject(GameObject::Ball, wallpix);
                }else{
                  map[i][j] = new GameObject(GameObject::Ball, ballpix);
                }
                map[i][j]->set_score(BALL_SCORE);
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                ball_num++;
                break;
            case '4':
                map[i][j] = new GameObject(GameObject::PowerBall, powerballpix);
                map[i][j]->set_score(POWERBALL_SCORE);
                map[i][j]->setPos(tmp_x, tmp_y);
                addItem(map[i][j]);
                powerball.push_back(map[i][j]);
                ball_num++;
                break;
            case '3':
                map[i][j] = new GameObject(GameObject::Blank, blankpix);
                break;
            case '2':
                gate = new GameObject(GameObject::Gate, gatepix);
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
                //map[i][j] = new GameObject(GameObject::Blank, blankpix);
                ghost[ghostCount] = new Ghost(ghostCount);
                ghost[ghostCount]->game = this;
                ghost[ghostCount]->setZValue(2);
                ghost[ghostCount]->release_time = GHOST_RELEASE_TIME[ghostCount];
                ghost[ghostCount]->_x = j;
                ghost[ghostCount]->_y = i;
                ghost[ghostCount]->set_score(GHOST_SCORE);
                ghost[ghostCount]->setPos(tmp_x, tmp_y);
                addItem(ghost[ghostCount]);
                ghostCount++;
                map[i][j] = ghost[ghostCount];
            case 'x':
                pacmanTwo = new PacmanTwo();
                pacmanTwo->game = this;
                pacmanTwo->setZValue(2);
                pacmanTwo->setPos(tmp_x, tmp_y);
                addItem(pacmanTwo);
                map[i][j] = pacmanTwo;
                break;


            }

            //add case to create ghosts
            if (map[i][j]) {
                map[i][j]->_x = j;
                map[i][j]->_y = i;
            }
        }
    }


}


void Game::start()
{
    int temp = 0;

    if(versus){
        temp = VERSUSINTERVAL;
    }else{
        temp = INTERVAL;
    }
    powerball_flash_timer = new QTimer(this);
    connect(powerball_flash_timer, SIGNAL(timeout()), this , SLOT(powerball_flash()));
    powerball_flash_timer->start(FLASH_INTERVAL);

    pacman_timer = new QTimer(this);
    connect(pacman_timer, SIGNAL(timeout()), this , SLOT(pacman_handler()));
    pacman_timer->start(temp);

    if(versus){
        pacmanTwo_timer = new QTimer(this);
        connect(pacmanTwo_timer, SIGNAL(timeout()), this , SLOT(pacmanTwo_handler()));
        pacmanTwo_timer->start(temp);
    }


    for (int i = 0; i < Ghost::GhostNum; i++) {
        ghost_timer[i] = new QTimer(this);
        connect(ghost_timer[i], &QTimer::timeout, [=](){ghost_handler(i);} );
        ghost_timer[i]->start(NORMAL_INTERVAL);
    }
}


void Game::stop()
{
    pacman_timer->stop();

    if(versus){
        pacmanTwo_timer->stop();
    }

    powerball_flash_timer->stop();
//    for (int i = 0; i < Ghost::ghostCount; i++) {
//        ghost_timer[i]->stop();
//    }
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

void Game::pacman_handler()
{
    pacman->move();
    if (stat == Win) {
        stop();
    }
    if (stat == Lose) {
        stop();
    }
}
void Game::pacmanTwo_handler()
{
    pacmanTwo->move();
    if (stat == Win) {
        stop();
    }
    if (stat == Lose) {
        stop();
    }
}

void Game::ghost_handler(int ghostCountd)
{
   ghost[ghostCountd]->move();
    if (stat == Lose) {
       stop();
    }
}


void Game::pacman_next_direction(GameObject::Dir d)
{
    pacman->set_next_dir(d);
}
void Game::pacmanTwo_next_direction(GameObject::Dir d)
{
    pacmanTwo->set_next_dir(d);
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
    delete pacman_timer;
    delete pacmanTwo_timer;
    delete powerball_flash_timer;
//    for (int i = 0; i < Ghost::ghostCount; i++) {
//        delete ghost_timer[i];
//    }
}
