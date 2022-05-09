#include "game.h"
#include<QDebug>

#include <QRandomGenerator>

#define W (GameObject::Width)


Ghost::Ghost(int comp) : GameObject( GameObject::Ghost, QPixmap())
{

    dir = Dir(QRandomGenerator::global()->generate() % 4);

    switch (comp) { // [Amazon, Costco, Target, IKEA]
    case 0:
        setPixmap(QPixmap(":/game_objects/ghosts/amazon.png"));
        break;
    case 1:
        setPixmap(QPixmap(":/game_objects/ghosts/costco.png"));
        break;
    case 2:
        setPixmap(QPixmap(":/game_objects/ghosts/actuallyTarget.png"));
        break;
    case 3:
        setPixmap(QPixmap(":/game_objects/ghosts/realikea.png"));
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
    default:
        return true;
    }
}

void Ghost::chase_pacman()
{

//    for(int i = 0; i< 5; i++){
//    setY(static_cast<int>(y()) - 1);
//    }
//    // false if the adjacent block is a wall
//    bool okdir[5] = {false, false, false, false, false};
//    QVector<Dir> oklist;
//    if (overlapable(_y, _x + 1)) {
//        okdir[Right] = true;
//        oklist.push_back(Right);
//    }
//    if (overlapable(_y, _x - 1)) {
//        okdir[Left] = true;
//        oklist.push_back(Left);
//    }
//    if (overlapable(_y + 1, _x)) {
//        okdir[Down] = true;
//        oklist.push_back(Down);
//    }
//    if (overlapable(_y - 1, _x)) {
//        okdir[Up] = true;
//        oklist.push_back(Up);
//    }

//    Dir backward_dir;
//    switch (dir) {
//    case Up:
//        backward_dir = Down;
//        break;
//    case Down:
//        backward_dir = Up;
//        break;
//    case Left:
//        backward_dir = Right;
//        break;
//    case Right:
//        backward_dir = Left;
//        break;
//    case Stop:
//        backward_dir = Stop;
//        break;
//    }


//    if (oklist.size() > 2) {

//        int dist_x = game->pacman->get_x() - this->get_x();
//        int dist_y = game->pacman->get_y() - this->get_y();

//        if (dist_y > 0) {
//            if (okdir[Down] && dir != Up) {
//                dir = Down;
//            } else {
//                if (dist_x >= 0) {
//                    if (okdir[Right]) {
//                        dir = Right;
//                    } else if (okdir[Left]) {
//                        dir = Left;
//                    }
//                } else {
//                    if (okdir[Left]) {
//                        dir = Left;
//                    } else if (okdir[Right]) {
//                        dir = Right;
//                    }
//                }
//            }
//        } else if (dist_y < 0) {
//            if (okdir[Up] && dir != Down) {
//                dir = Up;
//            } else {
//                if (dist_x >= 0) {
//                    if (okdir[Right]) {
//                        dir = Right;
//                    } else if (okdir[Left]) {
//                        dir = Left;
//                    }
//                } else {
//                    if (okdir[Left]) {
//                        dir = Left;
//                    } else if (okdir[Right]) {
//                        dir = Right;
//                    }
//                }
//            }
//        } else if (dist_x > 0) {
//            if (okdir[Right] && dir != Left) {
//                dir = Right;
//            } else {
//                if (okdir[Up]) {
//                    dir = Up;
//                } else if(okdir[Down]) {
//                    dir = Down;
//                }
//            }
//        } else if (dist_x < 0) {
//            if (okdir[Left] && dir != Right) {
//                dir = Left;
//            } else {
//                if (okdir[Up]) {
//                    dir = Up;
//                } else if(okdir[Down]) {
//                    dir = Down;
//                }
//            }
//        }
//    } else if (oklist.size() == 2) {
//        if (okdir[dir] == false) {
//            // ghost is on a corner
//            if (oklist[0] == backward_dir) {
//                dir = oklist[1];
//            } else {
//                dir = oklist[0];
//            }
//        }
//    }







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
    for(int i = 0; i< 5; i++){

        if(overlapable(_y, _x - 1)){
                    moveleft();
                }

    }
//    if (x_remainder == 0 && y_remainder == 0) {
//        // update ghost's coordinate in map
//        _x = __x;
//        _y = __y;
//    }

//    int path = rand() % 2 + 1; //Generate a direction 1 -> GO ONLY UP OR DOWN, 2-> ONLY LEFT OR RIGHT

//    if(game->pacman->get_x() == __x && game->pacman->get_y()==__y){
//        //Ghost and Pacman X,Y are equal (collision)
//            game->stop();
//    }


//    if(path == 1){ //ONLY UP OR DOWN
//        if(game->pacman->get_y()-__y > 0 && overlapable(_y+1, _x)){
//            if(__y <= game->map_height){
//                movedown();
//            }
//        }
//        else if(game->pacman->get_y()-__y < 0 && overlapable(_y - 1, _x)){ //in pos y direction (up)
//            if(__y >= 1){

//              moveup();
//            }
//        }

//    }
//    else if(path == 2){
//        if(game->pacman->get_x()-__x < 0 && overlapable(_y, _x - 1)){ //in neg x direction (left)

//            moveleft();
//        }
//        else if(game->pacman->get_x()-__x > 0 && overlapable(_y, _x + 1)){ //in pos x direction (right)

//            moveright();
//        }
//    }




//        if (x_remainder == 0 && y_remainder == 0) {

//            _x = __x;
//            _y = __y;
//        }


//    if (collidesWithItem(game->pacman, Qt::IntersectsItemShape)){
//                game->stop();
//        }

}





