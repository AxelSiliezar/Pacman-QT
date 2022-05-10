#include "game.h"
#include<QDebug>

#include <QRandomGenerator>

#define W (GameItem::Width)


Ghost::Ghost(int comp) : GameItem( GameItem::Ghost, QPixmap())
{


    switch (comp) {
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


void Ghost::ghostRandomScript(){
    int gh_x = (x());
    int gh_y = (y());
    int ghostX = (gh_x - game->map_x) / W;           // block x coordinate in map
    int ghostY = (gh_y - game->map_y) / W;           // block y coordinate in map
    int xDiff = (gh_x - game->map_x) % W;   // remainder x pixel to fit a block
    int yDiff = (gh_y - game->map_y) % W;   // remainder y pixel to fit a block

    if (xDiff == 0 && yDiff == 0) {
            _x = ghostX;
            _y = ghostY;
        }

    if(game->pacman->get_x() == ghostX && game->pacman->get_y()==ghostY){
                game->stop();
        }

    if(last == 0){
        if(wallCollision(_y, _x - 1)){
                        setX(static_cast<int>(x()) - 1);

                  }else{
                last = QRandomGenerator::global()->generate() % 4;
        }
    }

    if(last == 1){
        if(wallCollision(_y - 1, _x)){
               if(ghostY >= 1){
                 setY(static_cast<int>(y()) - 1);

               }else{
                   last = QRandomGenerator::global()->generate() % 4;
           }
           }else{
            last = QRandomGenerator::global()->generate() % 4;
    }
    }
    if(last == 2){
        if(wallCollision(_y, _x + 1)){
                           setX(static_cast<int>(x()) + 1);

                     }else{
            last = QRandomGenerator::global()->generate() % 4;
    }
    }
    if(last == 3){
        if(wallCollision(_y+1, _x)){
                               if(ghostY <= game->map_height){
                                   setY(static_cast<int>(y()) + 1);

                               }else{
                                   last = QRandomGenerator::global()->generate() % 3;
                           }
                           }else{
            last = QRandomGenerator::global()->generate() % 4;
    }
    }


    if(game->pacman->get_x() == ghostX && game->pacman->get_y()==ghostY){
                game->stop();
        }


}

bool Ghost::wallCollision(int i, int j)
{

    switch (game->map[i][j]->get_type()) {
    case Wall:
        return false;
    default:
        return true;
    }
}


