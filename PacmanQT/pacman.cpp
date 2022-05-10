#include "game.h"
#define W (GameItem::Width)

Pacman::Pacman() : GameItem(
    GameItem::Pacman, QPixmap(":/game_objects/pacman/heppy.png"))
{

}
void Pacman::eat_ball(int __y, int __x)
{
    GameItem *obj = game->map[__y][__x];
    switch (obj->get_type()) {
    case Ball:
        game->ballsLeft--;
        pointsGrabbed++;
        break;
    case PowerBall:
        game->ballsLeft--;
        for (int i = 0; i < game->powerball.size(); i++) {
            if (game->powerball.at(i) == obj) {
                game->powerball.remove(i);
                break;
            }
        }
        break;
    default:
        return;
    }

    QPixmap blankpix;
    if(game->versus){
        game->map[_y][_x] = new GameItem(GameItem::Wall, blankpix);
    }else{
        game->map[_y][_x] = new GameItem(GameItem::Blank, blankpix);
    }
    game->map[__y][__x] = this;
    delete obj;

}


bool Pacman::wallCollision(int i, int j)
{

    if ((i < 0 || j < 0) || (i >= game->map_height || j >= game->map_width)) {
        return false;
    }

    switch (game->map[i][j]->get_type()) {
    case Wall:
    case Gate:
        return false;
    default:
        return true;
    }
}


void Pacman::move(int temp)
{

    if(!lost){


    int PacmanX = (x());
    int PacmanY = (y());
    int __x = (PacmanX - game->map_x) / W;
    int __y = (PacmanY - game->map_y) / W;
    int x_remainder = (PacmanX - game->map_x) % W;
    int y_remainder = (PacmanY - game->map_y) % W;

if (x_remainder == 0 && y_remainder == 0) {
        _x = __x;
        _y = __y;
    }


    if(temp == 1){

            if (wallCollision(_y - 1, _x)) {
                 if(__y >= 1){
               setY((y()) - 1);
                 }
            }


    }
    if(temp == 2){

        if (wallCollision(_y, _x - 1)) {
           setX((x()) - 1);
        }



    }
    if(temp == 3){
        if (wallCollision(_y + 1, _x)) {
            if(__y <= game->map_height){
           setY((y()) + 1);
             }
        }

    }
    if(temp == 4){

            if (wallCollision(_y, _x + 1)) {
               setX((x()) + 1);
            }


    }

    if (x_remainder == 0) {
        if (y_remainder == 0) {
            eat_ball(__y, __x);
            _x = __x;
            _y = __y;
        }
}
    }
}


