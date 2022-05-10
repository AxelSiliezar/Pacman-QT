#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPair>
#include "GameItem.h"


<<<<<<< Updated upstream
/* Changeable game options */
#define BALL_SCORE      10          // score of balls
#define POWERBALL_SCORE 30          // score of powerballs
#define JURYBOX_SCORE   60
#define GHOST_SCORE     50          // score of ghosts
#define INTERVAL        10          // move interval of pacman
#define VERSUSINTERVAL  6
#define NORMAL_INTERVAL 10          // move interval of normal ghosts
#define PANNIC_INTERVAL 15          // move interval of pannic ghosts
#define RUNNING_INTERVAL 5          // move interval of running ghosts
#define PANNIC_TIME     1000        // interval number of pannic ghosts
#define FLASH_INTERVAL 200          // flash interval of powerballs
=======

#define BALL_SCORE      10
#define POWERBALL_SCORE 30
#define GHOST_SCORE     50
#define NORMAL_INTERVAL 10
#define PANNIC_INTERVAL 15
#define RUNNING_INTERVAL 5
#define PANNIC_TIME     1000
#define FLASH_INTERVAL 200
>>>>>>> Stashed changes

/* Game control class */
class Game : public QGraphicsScene
{
    Q_OBJECT

public:
<<<<<<< Updated upstream
    std::string status = {"win", "lose"};
    int geo_x, geo_y;
    int map_height, map_width;      // game map (20 x 29 in this app)
=======
    int map_x, map_y;
    int map_height, map_width;
>>>>>>> Stashed changes
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
    std::string stat = status;

    friend class Pacman;


private slots:
    void ghostTimer(int);
    void powerball_flash();


private:

    int map_size;
    int ball_num, eat_num, score;


    QTimer *powerball_flash_timer;
    QTimer *ghost_timer[Ghost::GhostNum];
    bool flash_tick;

};

#endif
