#include "game.h"

GameItem::GameItem(ObjectType t, QPixmap pixmap)
    : QGraphicsPixmapItem(pixmap)
{
    type = t;
}

GameItem::ObjectType GameItem::get_type()
{
    return type;
}

int GameItem::get_x()
{
    return _x;
}

int GameItem::get_y()
{
    return _y;
}



GameItem::~GameItem()
{
}
