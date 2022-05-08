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

bool Ghost::overlapable(int i, int j)
{
    if (i < 0 || j < 0) {
        return false;
    }

    if (i >= game->map_height || j >= game->map_width) {
        return false;
    }

    switch (game->map[i][j]->get_type()) {
    case Wall:
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
    qDebug ("pacman x, y : %d %d ",game->pacman->get_x(),game->pacman->get_y() );



        if (status != Running && release_time > 0) {
            release_time--;
        } else if (status == Panic) {
            panic_time--;
            if (panic_time <= 0) {
                status = Normal;
            }
        }


        int gh_x = static_cast<int>(x());
        int gh_y = static_cast<int>(y());
        int __x = (gh_x - game->geo_x) / W;           // block x coordinate in map
        int __y = (gh_y - game->geo_y) / W;           // block y coordinate in map
        int x_remainder = (gh_x - game->geo_x) % W;   // remainder x pixel to fit a block
        int y_remainder = (gh_y - game->geo_y) % W;   // remainder y pixel to fit a block

        /* When ghost completely fits a block,
         * decide whether to change direction. */
        if (x_remainder == 0 && y_remainder == 0) {
            // update ghost's coordinate in map
            _x = __x;
            _y = __y;
            if (is_released) {
                /* Chase pacman. */
                switch (status) {
                case Normal:
                    chase_pacman();

                    break;
                case Panic:
                    //dodge_pacman();
                    break;
                default:
                    break;
                }
            } else {
                if (release_time == 0) {
                    /* Time to go out the cage. */
                    //go_out_cage();
                    if (game->map[_y][_x]->get_type() == Gate) {
                        // If arriving at gate, turn into release.
                        is_released = true;
                    }
                } else {
                    if (status == Running) {
                        if (_x == game->gate->get_x() && _y == game->gate->get_y() + 1) {
                            status = Normal;
                        } else {
                            /* Go back to cage. */
                            //go_to_cage();
                        }
                    } else {
                        /* Keep staying in the cage. */
                        //setdir_randomly();
                    }
                }
            }


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





}
