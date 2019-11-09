#ifndef ICONMAKER_HH
#define ICONMAKER_HH

#include <iostream>
#include <QLabel>
#include <QPainter>
#include <QPolygonF>
#include <QPointF>
#include <QGraphicsPolygonItem>
#include <QBrush>
#include <memory>


namespace Student{

class IconMaker : public std::enable_shared_from_this<IconMaker>
{
public:

    /**
     * @brief IconMaker Constructor.
     */
    IconMaker();

    /**
     * @brief makePawnIcon Creates icons for player's pawns.
     * @param id Id of the player whose icons are being created.
     * @return Icon for the players pawns.
     */
    QGraphicsPolygonItem* makePawnIcon(int id);

    /**
     * @brief makeActorIcon Creates icons for actors.
     * @param type Type of the actor.
     * @return Icon for the actor.
     */
    QLabel* makeActorIcon(const std::string& type);
};
}
#endif // ICONMAKER_HH

