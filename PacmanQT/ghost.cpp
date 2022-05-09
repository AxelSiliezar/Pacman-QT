#include "game.h"
#include<QDebug>

#include <QRandomGenerator>

#define W (GameObject::Width)


Ghost::Ghost(int comp) : GameObject( GameObject::Ghost, QPixmap())
{
    is_released = false;
    status = Normal;
    dir = Dir(QRandomGenerator::global()->generate() % 4);

    //qInfo() << ("comp recievd was: %d", comp);
    qDebug ("comp %d : ",comp);


    switch (comp) { // [Amazon, Costco, Target, IKEA]
    case 0:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/amazon.png"));
        setPixmap(QPixmap(":/game_objects/ghosts/amazon.png"));
        qInfo() << "Loaded & set amazon";
        //0 = loaded, 1 = not loaded correctly
        if(QPixmap(":/game_objects/ghosts/amazon.png").isNull()){
            qInfo() << "Sike, it's NULL" ;
        }


        break;
    case 1:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/costco.png"));
        setPixmap(QPixmap(":/game_objects/ghosts/costco.png"));
        qInfo() << "Loaded & set Costco";
        if(QPixmap(":/game_objects/ghosts/costco.png").isNull()){
            qInfo() << "Sike, it's NULL" ;
        }
        break;
    case 2:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/actuallyTarget.png"));
        setPixmap(QPixmap(":/game_objects/ghosts/actuallyTarget.png"));
        qInfo() << "Loaded & set Target";
        if(QPixmap(":/game_objects/ghosts/actuallyTarget.png").isNull()){
            qInfo() << "Sike, it's NULL" ;
        }
        break;
    case 3:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/realikea.png"));
        setPixmap(QPixmap(":/game_objects/ghosts/realikea.png"));
        qInfo() << "Loaded & set Ikea";
        if(QPixmap(":/game_objects/ghosts/realikea.png").isNull()){
            qInfo() << "Sike, it's NULL" ;
        }


        break;
    }
}

void Ghost::moveup()
{
    setY(static_cast<int>(y()) - 1);
}

void Ghost::moveleft()
{
    setX(static_cast<int>(x()) - 1);
}

void Ghost::movedown()
{
    setY(static_cast<int>(y()) + 1);
}

void Ghost::moveright()
{
    setX(static_cast<int>(x()) + 1);
}

bool Ghost::overlapable(int i, int j)
{

    switch (game->map[i][j]->get_type()) {
    case Wall:
        qDebug("Can not cross!");
        return false;
    case Gate:
        if (is_released == false && release_time == 0) {
            return true;
        } else if (status == Running) {
            return true;
        } else {
            return false;
        }
    default:
        return true;
    }
}

void Ghost::chase_pacman()
{
    // false if the adjacent block is a wall
    bool okdir[5] = {false, false, false, false, false};
    QVector<Dir> oklist;
    if (overlapable(_y, _x + 1)) {
        okdir[Right] = true;
        oklist.push_back(Right);
    }
    if (overlapable(_y, _x - 1)) {
        okdir[Left] = true;
        oklist.push_back(Left);
    }
    if (overlapable(_y + 1, _x)) {
        okdir[Down] = true;
        oklist.push_back(Down);
    }
    if (overlapable(_y - 1, _x)) {
        okdir[Up] = true;
        oklist.push_back(Up);
    }
    qDebug() << "inside chasing";
    Dir backward_dir;
    switch (dir) {
    case Up:
        backward_dir = Down;
        break;
    case Down:
        backward_dir = Up;
        break;
    case Left:
        backward_dir = Right;
        break;
    case Right:
        backward_dir = Left;
        break;
    case Stop:
        backward_dir = Stop;
        break;
    }

    // Change direction only when ghost is
    // not at an intersection in order to
    // avoid oscillation.
    if (oklist.size() > 2) {

        int dist_x = game->pacman->get_x() - this->get_x();
        int dist_y = game->pacman->get_y() - this->get_y();

        if (dist_y > 0) {
            if (okdir[Down] && dir != Up) {
                dir = Down;
            } else {
                if (dist_x >= 0) {
                    if (okdir[Right]) {
                        dir = Right;
                    } else if (okdir[Left]) {
                        dir = Left;
                    }
                } else {
                    if (okdir[Left]) {
                        dir = Left;
                    } else if (okdir[Right]) {
                        dir = Right;
                    }
                }
            }
        } else if (dist_y < 0) {
            if (okdir[Up] && dir != Down) {
                dir = Up;
            } else {
                if (dist_x >= 0) {
                    if (okdir[Right]) {
                        dir = Right;
                    } else if (okdir[Left]) {
                        dir = Left;
                    }
                } else {
                    if (okdir[Left]) {
                        dir = Left;
                    } else if (okdir[Right]) {
                        dir = Right;
                    }
                }
            }
        } else if (dist_x > 0) {
            if (okdir[Right] && dir != Left) {
                dir = Right;
            } else {
                if (okdir[Up]) {
                    dir = Up;
                } else if(okdir[Down]) {
                    dir = Down;
                }
            }
        } else if (dist_x < 0) {
            if (okdir[Left] && dir != Right) {
                dir = Left;
            } else {
                if (okdir[Up]) {
                    dir = Up;
                } else if(okdir[Down]) {
                    dir = Down;
                }
            }
        }
    } else if (oklist.size() == 2) {
        if (okdir[dir] == false) {
            // ghost is on a corner
            if (oklist[0] == backward_dir) {
                dir = oklist[1];
            } else {
                dir = oklist[0];
            }
        }
    }
}


void Ghost::move(){

    int gh_x = static_cast<int>(x());
    int gh_y = static_cast<int>(y());
    int __x = (gh_x - game->geo_x) / W;           // block x coordinate in map
    int __y = (gh_y - game->geo_y) / W;           // block y coordinate in map
    int x_remainder = (gh_x - game->geo_x) % W;   // remainder x pixel to fit a block
    int y_remainder = (gh_y - game->geo_y) % W;   // remainder y pixel to fit a block

    if (x_remainder == 0 && y_remainder == 0) {
        // update ghost's coordinate in map
        _x = __x;
        _y = __y;
    }

    //qDebug ("pacman x, y : %d %d ",game->pacman->get_x(),game->pacman->get_y() );
    //qDebug ("ghost x and y: %d %d ", __x,__y);
   // qDebug("game height: %d", game->map_height); height matters when going DOWN
    //qDebug ("map endpoints : %d %d", game->geo_x, game->geo_y);
    //qDebug ("distance to pacman : %d %d ",game->pacman->get_x()-__x,game->pacman->get_y()-__y);
    /*
    int path = rand() % 4 + 1; //Generate a direction (UP,DOWN,LEFT,RIGHT) [1,2,3,4]
    qDebug("path randomly chosen is %d!", path);

    if(path == 1 && overlapable(__y-1, __x)){
        //check if up is overlapable, move up if it is the case
        moveup();

    }
    if (path == 2 && overlapable(__y+1, __x)){
        movedown();

    }
    if(path == 3 && overlapable(__y, __x - 1)){
        moveleft();

    }
    if(path == 4 && overlapable(__y, __x - 1)){
        moveright();
    }
    */

    int path = rand() % 2 + 1; //Generate a direction 1 -> GO ONLY UP OR DOWN, 2-> ONLY LEFT OR RIGHT

    if(game->pacman->get_x() == __x && game->pacman->get_y()==__y){
        //Ghost and Pacman X,Y are equal (collision)
        if (status == Normal) {
            qDebug("Game over?");
            qDebug("Coords of collision: %d %d", __x, __y);
            game->stat = Game::Lose;
        }
    }
    qDebug("path randomly chosen is %d!", path);

    if(path == 1){ //ONLY UP OR DOWN
        if(game->pacman->get_y()-__y > 0 && overlapable(_y+1, _x)){
            if(__y <= game->map_height){
                qDebug("ayo down");
                //i >= game->map_height
                movedown();
            }
        }
        else if(game->pacman->get_y()-__y < 0 && overlapable(_y - 1, _x)){ //in pos y direction (up)



            if(__y >= 1){
              qDebug("ayo up");
              moveup();
            }
        }
        else{
            qDebug("Ghost is in a pipe");
        }
    }
    else if(path == 2){
        if(game->pacman->get_x()-__x < 0 && overlapable(_y, _x - 1)){ //in neg x direction (left)
            qDebug("ayo left");
            moveleft();
        }
        else if(game->pacman->get_x()-__x > 0 && overlapable(_y, _x + 1)){ //in pos x direction (right)
            qDebug("ayo right");
            moveright();
        }
    }
/*
    if(abs(game->pacman->get_x()-__x) <= abs(game->pacman->get_y()-__y) && (overlapable(_y, _x - 1) || overlapable(_y, _x + 1) )  ){//x direction is closest and not stuck
        if(game->pacman->get_x()-__x < 0 && overlapable(_y, _x - 1)){ //in neg x direction (left)
            qDebug("go left dawg");
            moveleft();
        }
        if(game->pacman->get_x()-__x > 0 && overlapable(_y, _x + 1)){ //in pos x direction (right)
            qDebug("go right dawg");
            moveright();
        }

        if(game->pacman->get_y()-__y < 0 && overlapable(_y+1, _x)){ //in neg y direction (down)
            qDebug("go down dawg!");
            movedown();
        }
        if(game->pacman->get_y()-__y > 0 && overlapable(_y-1, _x)){ //in pos y direction (up)
            qDebug("go up dawg!");
            if(__y > 3){
              moveup();

            }

        }

    }
    else if(abs(game->pacman->get_x()-__x) > abs(game->pacman->get_y()-__y) && (overlapable(_y + 1, _x) || overlapable(_y - 1, _x))){
        if(game->pacman->get_y()-__y < 0 && overlapable(_y+1, _x)){

            qDebug("go down dawg");
            movedown();
        }
        else if(game->pacman->get_y()-__y > 0 && overlapable(_y - 1, _x)){ //in pos y direction (up)

            qDebug("go up dawg");
            moveup();
        }
    }

*/



        /* When ghost completely fits a block,
         * decide whether to change direction.*/
        if (x_remainder == 0 && y_remainder == 0) {
            // update ghost's coordinate in map
            _x = __x;
            _y = __y;
        }
        /*
            is_released = true;
            if (is_released) {
                if(overlapable(_y, _x + 1)){//Right is not a wall
                    qDebug() << "Going RIGHT?";

                }

            }
            qDebug() << "Hm?";
            */
            /*
            switch (dir) {
                case Stop:
                    break;
                case Up:
                    qDebug() << "Going UP";

                    setY(static_cast<int>(y()) - 1);
                    break;
                case Down:
                    qDebug() << "Going DOWN";

                    setY(static_cast<int>(y()) + 1);
                    break;
                case Left:
                    qDebug() << "Going LEFT";

                    setX(static_cast<int>(x()) - 1);
                    break;
                case Right:
                    qDebug() << "Going RIGHT";
                    setX(static_cast<int>(x()) + 1);
                    break;
                }

               */

    if (collidesWithItem(game->pacman, Qt::IntersectsItemShape)){
            if (status == Normal) {
                game->stat = Game::Lose;
            } else if (status == Panic) {
                setPixmap(QPixmap(":/rsc2/run.png"));
               // game->score += score;
                status = Running;
                release_time = 200;
                is_released = false;
                //game->ghost_timer[color]->setInterval(RUNNING_INTERVAL);
            }
        }

}





