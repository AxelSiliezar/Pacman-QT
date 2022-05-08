#include "game.h"
#include <QRandomGenerator>

#define W (GameObject::Width)


Ghost::Ghost(int comp) : GameObject( GameObject::Ghost, QPixmap())
{
    anim_index = 0;
    is_released = false;
    dir = Dir(QRandomGenerator::global()->generate() % 4);
    status = Normal;

    switch (comp) { // [Amazon, Costco, Target, IKEA]
    case 0:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/amazon.png"));

        break;
    case 1:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/amazon.png"));
        break;
    case 2:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/amazon.png"));
        break;
    case 3:
        anim[Right].push_back(QPixmap(":/game_objects/ghosts/amazon.png"));
        break;
    }


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




