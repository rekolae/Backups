#include "mygraphicsscene.hh"


namespace Student{

myGraphicsScene::myGraphicsScene(QWidget * /*parent*/)
{

}


myGraphicsScene::~myGraphicsScene()
= default;


void myGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    x_ = event->scenePos().x();
    y_ = event->scenePos().y();
    event->accept();
    pixelToCube();
}


void myGraphicsScene::pixelToCube()
{
    int shortestDistance = 200;
    int cube_x;
    int cube_y;
    int cube_z;

    //Calculates the center of every hex and compares the click position to those.
    for(int x = -mapWidth_; x<=mapWidth_;++x){
        for(int y = -mapWidth_; y<=mapWidth_;++y){
            for(int z = -mapWidth_; z<=mapWidth_;++z){
                if(x+y+z == 0){
                    int sceneSizeXmiddle = 550;
                    int sceneSizeYmiddle = 500;
                    int x_pixel = sceneSizeXmiddle + (52 *z) + (26 * y) + (78*x);
                    int y_pixel = sceneSizeYmiddle + (45 * -y)+ (45* -x);

                    int distance = sqrt(abs(x_ - x_pixel) * abs(x_ - x_pixel) +
                            abs(y_ - y_pixel) *abs(y_ - y_pixel));

                    //Check in current distance is shorter than previous
                    if(distance < shortestDistance){
                        shortestDistance = distance;
                        cube_x = x;
                        cube_y = y;
                        cube_z = z;
                    }
                }
            }
        }
    }

    Common::CubeCoordinate cubeCord(cube_x,cube_y,cube_z);
    if(shortestDistance < 31){
        emit cubeClicked(cubeCord);
    }
};

}

