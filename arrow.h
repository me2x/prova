#ifndef ARROW_H
#define ARROW_H

#include <qt4/QtGui/qgraphicsitem.h>
//#include "provariquadro.h"
#include <memory>
class ProvaRiquadro;

class Arrow //:  QGraphicsItem
{
public:
    Arrow(ProvaRiquadro* from, ProvaRiquadro* to, int fromport, int toport,std::shared_ptr<std::map<QGraphicsLineItem*,Arrow*> >arrows); //get data. draw first.
    void update(); //delete old qgraphicsitem, create new ones.
    //ptr to scene arrows map. when update arrow that map has to be updated too.
    std::shared_ptr<std::map<QGraphicsLineItem*,Arrow*> >arrows;
    
    QGraphicsLineItem* line,*sx_line,*dx_line;
    QGraphicsTextItem* label_start,*label_stop;
    ProvaRiquadro* start_point;
    ProvaRiquadro* arrival_point;
   //virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
   // virtual QRectF boundingRect() const;
private:

    int start_port,stop_port;
    
};

#endif // ARROW_H
