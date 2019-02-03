#include "iconmaker.hh"


namespace Student{

IconMaker::IconMaker()
= default;


QGraphicsPolygonItem* IconMaker::makePawnIcon(int id)
{
    //Specify cornerpoints of the icon.
    QPolygonF polyPoints;
        polyPoints.append(QPointF(0.0, 0.0));
        polyPoints.append(QPointF(0.0, 15.0));
        polyPoints.append(QPointF(15.0, 0.0));
        polyPoints.append(QPointF(15.0, 15.0));

    QBrush brush;

    if (id == 0){
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::yellow);
    }

    else if (id == 1){
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::green);
    }

    else if (id == 2){
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::cyan);
    }

    else{
        brush.setStyle(Qt::SolidPattern);
        brush.setColor(Qt::red);
    }

    auto* pawnIcon = new QGraphicsPolygonItem(polyPoints);
    pawnIcon->setBrush(brush);

    return pawnIcon;
}


QLabel* IconMaker::makeActorIcon(const std::string& type)
{

    QLabel* actorIcon = new QLabel;
    QPalette palette;
    palette.setColor(QPalette::Window, Qt::blue);

    if (type == "kraken"){
        actorIcon->setText("K");
        palette.setColor(QPalette::WindowText, Qt::white);
    }

    else if (type == "boat"){
        actorIcon->setText("B");
        palette.setColor(QPalette::WindowText, Qt::white);
    }

    else if (type == "vortex"){
        actorIcon->setText("V");
        palette.setColor(QPalette::WindowText, Qt::white);
    }

    else if (type == "dolphin"){
        actorIcon->setText("D");
        palette.setColor(QPalette::WindowText, Qt::white);
    }

    else if (type == "shark"){
        actorIcon->setText("S");
        palette.setColor(QPalette::WindowText, Qt::white);
    }

    else if (type == "seamunster"){
        actorIcon->setText("M");
        palette.setColor(QPalette::WindowText, Qt::white);
    }

    actorIcon->setAutoFillBackground(true);
    actorIcon->setPalette(palette);
    return actorIcon;
}
}
