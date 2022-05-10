#ifndef GAMEITEM_H
#define GAMEITEM_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>



class Game;



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


    friend class Game;
    friend class Ghost;

protected:
    int _x, _y;
    ObjectType type;
    int score;
};

class Pacman : public GameItem
{
public:
    bool lost = false;
    int pointsGrabbed = 0;
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
