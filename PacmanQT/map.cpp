//#include "map.h"
//#include <QString>
//#include <QFile>
//#include <QRandomGenerator>
//Map::Map(int x, int y, int map_w, int map_h, QString map_src)
//    : QGraphicsScene(x, y, 20 * map_w, 20 * map_h)
//{
//    geo_x = x;
//    geo_y = y;


//    /* Initialize map pointers */
//    map_width = map_w;
//    map_height = map_h;
//    map = GameObject**[map_height];
//    for (int i = 0; i < map_height; i++) {
//        map[i] = new GameObject*[map_width];
//        for (int j = 0; j < map_width; j++)
//            map[i][j] = nullptr;
//    }
//    QPixmap wallpix(":/game_objects/map_objects/wall.png");
//    QPixmap ballpix(":/game_objects/map_objects/dot.png");
//    QPixmap powerballpix(":/game_objects/map_objects/power_ball.png");
//    QPixmap gatepix(":/game_objects/map_objects/gate.png");
//    QPixmap blankpix;
//    QFile mapfile(map_src);
//    mapfile.open(QIODevice::ReadOnly|QIODevice::Text);

//    pacman = new Pacman();

//    for (int i = 0; i < map_h; i++) {
//        QByteArray line = mapfile.readLine();
//        for (int j = 0; j < map_w; j++) {
//            int tmp_x = x + (j * W);
//            int tmp_y = y + (i * W);
//            switch (line[j]) {
//            case '1':
//                map[i][j] = new GameObject(GameObject::Wall, wallpix);
//                map[i][j]->setPos(tmp_x, tmp_y);
//                addItem(map[i][j]);
//                break;
//            case '0':
//                map[i][j] = new GameObject(GameObject::Ball, ballpix);
//                map[i][j]->set_score(BALL_SCORE);
//                map[i][j]->setPos(tmp_x, tmp_y);
//                addItem(map[i][j]);
//                ball_num++;
//                break;
//            case '4':
//                map[i][j] = new GameObject(GameObject::PowerBall, powerballpix);
//                map[i][j]->set_score(POWERBALL_SCORE);
//                map[i][j]->setPos(tmp_x, tmp_y);
//                addItem(map[i][j]);
//                powerball.push_back(map[i][j]);
//                ball_num++;
//                break;
//            case '3':
//                map[i][j] = new GameObject(GameObject::Blank, blankpix);
//                break;
//            case '2':
//                gate = new GameObject(GameObject::Gate, gatepix);
//                gate->_x = j;
//                gate->_y = i;
//                gate->setPos(tmp_x, tmp_y);
//                addItem(gate);
//                map[i][j] = gate;
//                break;
//            case 'p':
//                pacman = new Pacman();
//                pacman->game = this;
//                pacman->setZValue(2);
//                pacman->setPos(tmp_x, tmp_y);
//                addItem(pacman);
//                map[i][j] = pacman;
//                break;
//            case 'x':
//                pacman = new Pacman();
//                pacman->game = this;
//                pacman->setZValue(2);
//                pacman->setPos(tmp_x, tmp_y);
//                addItem(pacman);
//                map[i][j] = pacman;
//                break;

//            }
//            if (map[i][j]) {
//                map[i][j]->_x = j;
//                map[i][j]->_y = i;
//            }
//        }
//    }
//}
