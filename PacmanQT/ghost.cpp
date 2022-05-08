#include "game.h"
#include<QDebug>

#include <QRandomGenerator>

#define W (GameObject::Width)


Ghost::Ghost(int comp) : GameObject( GameObject::Ghost, QPixmap())
{
    is_released = false;
    status = Normal;

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




