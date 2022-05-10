#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPair>
#include "GameItem.h"


#define BALL_SCORE      10
#define POWERBALL_SCORE 30
#define GHOST_SCORE     50
#define NORMAL_INTERVAL 10
#define PANNIC_INTERVAL 15
#define RUNNING_INTERVAL 5
#define PANNIC_TIME     1000
#define FLASH_INTERVAL 200

/* Game control class */
class Game : public QGraphicsScene
{
    Q_OBJECT

public:

    int map_x, map_y;
    int map_height, map_width;
    int ball_num;
    Game(int, int, int, int, QString,bool);
    ~Game();
    void start();
    void stop();
    int get_score();

    GameItem ***map;
    GameItem *gate;
    Pacman *pacman;
    Pacman *pacmanTwo;

    Ghost *ghost[Ghost::GhostNum];

    QVector<GameItem*> powerball;
    bool versus;


    friend class Pacman;
    friend class MainWindow;


private slots:
    void ghostTimer(int);
    void powerball_flash();


private:

    int map_size;
    int eat_num, score;


    QTimer *powerball_flash_timer;
    QTimer *ghost_timer[Ghost::GhostNum];
    bool flash_tick;

};

#endif
