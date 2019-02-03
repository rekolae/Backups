#ifndef MYGRAPHICSSCENE_HH
#define MYGRAPHICSSCENE_HH

#include "cubecoordinate.hh"

#include <QGraphicsScene>
#include <QPointF>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <iostream>
#include <cmath>


namespace Student{

class myGraphicsScene : public QGraphicsScene
{
   Q_OBJECT

public:

    /**
     * @brief myGraphicsScene Constructor.
     * @param parent Parent widget.
     */
    explicit myGraphicsScene(QWidget *parent = nullptr);
    ~myGraphicsScene();


signals:

    /**
     * @brief cubeClicked Signal emited when scene is clicked.
     * @param cubeCord coordinated of the click.
     */
    void cubeClicked(Common::CubeCoordinate cubeCord);

protected:

    /**
     * @brief mousePressEvent Converts mouse click position in to cubecoordinates.
     * @param event Mouse click.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:

    /**
     * @brief pixelToCube Convert mouse position to cubecoordinate
     */
    void pixelToCube();

    double x_;
    double y_;

    int mapWidth_ = 10;
};
}

#endif // MYGRAPHICSSCENE_HH
