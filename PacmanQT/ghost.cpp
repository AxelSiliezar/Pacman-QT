#include "game.h"
#include <QRandomGenerator>

#define W (GameObject::Width)


Ghost::Ghost(int clr) : GameObject( GameObject::Ghost, QPixmap())
{
    color = (Color)clr;
    anim_index = 0;
    is_released = false;
    dir = Dir(QRandomGenerator::global()->generate() % 4);
    status = Normal;

    switch (color) {
    case Red:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/redright1.png"));
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/redright2.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/redup1.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/redup2.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/redleft1.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/redleft2.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/reddown1.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/reddown2.png"));
        break;
    case Yellow:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/yellowright1.png"));
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/yellowright2.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/yellowup1.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/yellowup2.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/yellowleft1.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/yellowleft2.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/yellowdown1.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/yellowdown2.png"));
        break;
    case Green:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/greenright1.png"));
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/greenright2.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/greenup1.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/greenup2.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/greenleft1.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/greenleft2.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/greendown1.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/greendown2.png"));
        break;
    case Pink:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/pinkright1.png"));
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/pinkright2.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/pinkup1.png"));
        anim[Up].push_back(QPixmap(":/game_objects/ghosts/pinkup2.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/pinkleft1.png"));
        anim[Left].push_back(QPixmap(":/game_objects/ghosts/pinkleft2.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/pinkdown1.png"));
        anim[Down].push_back(QPixmap(":/game_objects/ghosts/pinkdown2.png"));
        break;
    }

    panic_anim.push_back(QPixmap(":/game_objects/ghosts/bl1.png"));
    panic_anim.push_back(QPixmap(":/game_objects/ghosts/bl2.png"));
    running_anim.push_back(QPixmap(":/game_objects/ghosts/run.png"));
    setPixmap(anim[Right][0]);
}

void Ghost::move(){
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




