#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QVector>


/* Predefine the game object */
class Game;


/* Base class of ghosts, pacman */
class GameObject : public QGraphicsPixmapItem
{
public:
    enum ObjectType {Ball, Wall, Gate, Pacman,PacmanTwo,Ghost, Blank, PowerBall};
    enum Dir {Up = 0, Down = 1, Left = 2, Right = 3, Stop = 4};
    static const int Width = 20;      // game object size by pixel

    GameObject(ObjectType, QPixmap);
    ~GameObject();
    ObjectType get_type();
    int get_x();
    int get_y();
    int get_score();
    void set_score(int);
    void set_dir(Dir);
    void set_next_dir(Dir);
    Dir get_dir();
    Dir get_next_dir();

    friend class Game;
    friend class Ghost;

protected:
    int _x, _y;                 // coordinate in map
    Dir dir;                    // current moving direction
    Dir next_dir;               // next direction by w, a, s, d key
    ObjectType type;
    int score;
};
/* Pacman */
class Pacman : public GameObject
{
public:
    Pacman();
    void move();
    Game *game;                 // the pacman game obje
    void eat_ball(int, int);
    bool overlapable(int, int); // check if pacman can go to map[i][j]


friend class Game;

};


/* Ghost */
class Ghost : public GameObject
{
public:
    enum Status {Normal, Panic, Running};
    const static int GhostNum = 4;
    Game *game;                 // the pacman game object

    Ghost(int);
    void move();

    friend class Game;
    friend class Pacman;

private:
    void moveup();
    void movedown();
    void moveleft();
    void moveright();
    void chase_pacman();

    bool overlapable(int, int);                 // check if ghost can go to map[i][j]

    Status status;
    QVector<QPixmap> anim[5];                   // animations


};



#endif // GAMEOBJECT_H
