#include "game.h"
#define W (GameObject::Width)

Pacman::Pacman() : GameObject(
    GameObject::Pacman, QPixmap(":/game_objects/pacman/pacman.png"))
{

    dir = Stop;
    next_dir = Stop;
    anim_index = 2;

}

void Pacman::moveup()
{


    setY(static_cast<int>(y()) - 1);
}

void Pacman::moveleft()
{


    setX(static_cast<int>(x()) - 1);
}

void Pacman::movedown()
{


    setY(static_cast<int>(y()) + 1);
}

void Pacman::moveright()
{


    setX(static_cast<int>(x()) + 1);
}


void Pacman::eat_ball(int __y, int __x)
{
    GameObject *obj = game->map[__y][__x];
    switch (obj->get_type()) {
    case Ball:
        game->score += obj->get_score();
        game->ball_num--;
        break;
    case PowerBall:
        game->score += obj->get_score();
        game->ball_num--;
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

    /* Pacman eat a ball, and
     * fill the previous block with blank. */
    QPixmap blankpix;
    game->map[_y][_x] = new GameObject(GameObject::Wall, blankpix);
    game->map[__y][__x] = this;
    delete obj;

}


bool Pacman::overlapable(int i, int j)
{
    if (i < 0 || j < 0) {
        return false;
    }

    if (i >= game->map_height || j >= game->map_width) {
        return false;
    }

    switch (game->map[i][j]->get_type()) {
    case Wall:
        game->stat = Game::Lose;
    case Gate:
        return false;
    default:
        return true;
    }
}


void Pacman::move()
{
    int pac_x = static_cast<int>(x());
    int pac_y = static_cast<int>(y());
    int __x = (pac_x - game->geo_x) / W;            // x coordinate in map
    int __y = (pac_y - game->geo_y) / W;            // y coordinate in map
    int x_remainder = (pac_x - game->geo_x) % W;    // remainder x pixel to fit a block
    int y_remainder = (pac_y - game->geo_y) % W;    // remainder y pixel to fit a block
    Dir next_dir = get_next_dir();


    if (x_remainder == 0) {
        if (y_remainder == 0) {

            eat_ball(__y, __x);


            _x = __x;
            _y = __y;

            if (game->ball_num == 0) {
                game->stat = Game::Win;
                return;
            }
        }

        switch (next_dir) {
        case Stop:
            dir = next_dir;
            break;
        case Up:
            if (overlapable(_y - 1, _x)) {
                dir = next_dir;
            }
            break;
        case Down:
            if (overlapable(_y + 1, _x)) {
                dir = next_dir;
            }
            break;
        case Left:
            if (y_remainder == 0 && overlapable(_y, _x - 1)) {
                dir = next_dir;
            }
            break;
        case Right:
            if (y_remainder == 0 && overlapable(_y, _x + 1)) {
                dir = next_dir;
            }
            break;
        }
    } else if (y_remainder == 0) {
        switch (next_dir) {
        case Stop:
            dir = next_dir;
            break;
        case Left:
            if (overlapable(_y, _x - 1)) {
                dir = next_dir;
            }
            break;
        case Right:
            if (overlapable(_y, _x + 1)) {
                dir = next_dir;
            }
            break;
        default:
            break;
        }
    }


    switch (dir) {
    case Stop:
        break;
    case Up:
        if (y_remainder == 0 && !overlapable(_y - 1, _x)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            moveup();
        }
        break;
    case Down:
        if (y_remainder == 0 && !overlapable(_y + 1, _x)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            movedown();
        }
        break;
    case Left:
        if (x_remainder == 0 && !overlapable(_y, _x - 1)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            moveleft();
        }
        break;
    case Right:
        if (x_remainder == 0 && !overlapable(_y, _x + 1)) {
            dir = Stop;
            next_dir = Stop;
        } else {
            moveright();
        }
        break;
    }
}
