#include "game.h"
#include "chasing_strategy.cpp"
#include <QRandomGenerator>
#define W (GameObject::Width)

Ghost::Ghost(int clr) : GameObject(
    GameObject::Ghost, QPixmap())
{

}


Ghost::Color Ghost::get_color()
{

}

void Ghost::moveup()
{

}

void Ghost::moveleft()
{

}

void Ghost::movedown()
{

}

void Ghost::moveright()
{

}


bool Ghost::overlapable(int i, int j)
{

}


void Ghost::setdir_randomly()
{

}

void Ghost::go_out_cage()
{

}


void Ghost::chase_pacman()
{

}


void Ghost::dodge_pacman()
{

}

void Ghost::go_to_cage()
{

}


void Ghost::move()
{

}
