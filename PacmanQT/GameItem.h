#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>


/* Predefine the game object */
class Game;


/* Base class of ghosts, pacman */
class GameItem : public QGraphicsPixmapItem
{
public:
    enum ObjectType {Ball, Wall, Gate, Pacman,PacmanTwo,Ghost, Blank, PowerBall};
    static const int Width = 20;

    GameItem(ObjectType, QPixmap);
    ~GameItem();
    ObjectType get_type();
    int get_x();
    int get_y();
    int get_score();
    void set_score(int);

    friend class Game;
    friend class Ghost;

protected:
    int _x, _y;

    ObjectType type;
    int score;
};
/* Pacman */
class Pacman : public GameItem
{
public:
    bool lost = false;
    Pacman();
    void move(int);
    Game *game;
    void eat_ball(int, int);
    bool wallCollision(int, int);


friend class Game;

};


class Ghost : public GameItem
{
public:
    int last = 0;
    const static int GhostNum = 4;
    Game *game;

    Ghost(int);
    void ghostRandomScript();

    bool wallCollision(int, int);

    friend class Game;
    friend class Pacman;

};



#endif
