#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QPair>
#include "gameobject.h"


/* Changeable game options */
#define BALL_SCORE      10          // score of balls
#define POWERBALL_SCORE 30          // score of powerballs
#define GHOST_SCORE     50          // score of ghosts
#define INTERVAL        10          // move interval of pacman
#define VERSUSINTERVAL  6
#define NORMAL_INTERVAL 10          // move interval of normal ghosts
#define PANNIC_INTERVAL 15          // move interval of pannic ghosts
#define RUNNING_INTERVAL 5          // move interval of running ghosts
#define PANNIC_TIME     1000        // interval number of pannic ghosts
#define FLASH_INTERVAL 200          // flash interval of powerballs

/* Game control class */
class Game : public QGraphicsScene
{
    Q_OBJECT

public:
    int geo_x, geo_y;
    int map_height, map_width;      // game map (20 x 29 in this app)
    Game(int, int, int, int, QString,bool);
    ~Game();
    void start();
    void stop();
    void pacman_next_direction(GameObject::Dir);
    void pacmanTwo_next_direction(GameObject::Dir);
    int get_score();

    GameObject ***map;              // the map of pacman game
    GameObject *gate;               // pointer of the gate of cage of ghosts
    Pacman *pacman;
    Pacman *pacmanTwo;           // pointer of pacman
      // pointers of ghosts
    Ghost *ghost[Ghost::GhostNum];  // pointers of ghosts

    QVector<GameObject*> powerball; // pointers of powerball
    bool versus;

    friend class Pacman;


private slots:
    void pacman_handler();
    void pacmanTwo_handler();
    void powerball_flash();
    void ghost_handler(int);

private:
    //int map_height, map_width;      // game map (20 x 29 in this app)
    int map_size;                   // map_width * map_height
    int ball_num, eat_num, score;
                   // geometric coordinate


    QTimer *pacman_timer;
    QTimer *pacmanTwo_timer;
    QTimer *powerball_flash_timer;
    QTimer *ghost_timer[Ghost::GhostNum];
    bool flash_tick;

};

#endif // GAME_H
