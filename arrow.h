#ifndef ARROW_H
#define ARROW_H

#include <qt4/QtGui/qgraphicsitem.h>
//#include "provariquadro.h"
class ProvaRiquadro;

class Arrow //:  QGraphicsItem
{
public:
    Arrow(ProvaRiquadro* from, ProvaRiquadro* to, int fromport, int toport); //get data. draw first.
    void update(); //delete old qgraphicsitem, create new ones.
    
    QGraphicsLineItem* line,*sx_line,*dx_line;
    QGraphicsTextItem* label_start,*label_stop;
   //virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
   // virtual QRectF boundingRect() const;
private:

    int start_port,stop_port;
    ProvaRiquadro* start_point;
    ProvaRiquadro* arrival_point;
};

#endif // ARROW_H
