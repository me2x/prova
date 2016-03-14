#include "provariquadro.h"
#include <iostream>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
ProvaRiquadro::ProvaRiquadro()
{
   setFlag(ItemIsMovable);
   
}
void ProvaRiquadro::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "mouseDoubleClickEvent"<<std::endl;
    QGraphicsItem::mouseDoubleClickEvent(event);
}
void ProvaRiquadro::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  //  advance();
    std::cout << "mousemoveEvent"<<std::endl;
    QGraphicsItem::mouseMoveEvent(event);
    emit riquadroMosso();
}
void ProvaRiquadro::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "mouseClickEvent("<<event->pos().x()<<","<<event->pos().y()<<")"<<std::endl;
    
    
    
    QPointF p = mapToScene(event->pos());
    QPoint p1 = QCursor::pos();
    std::cout<<p.x()<<","<<p.y()<<std::endl;
    std::cout<<p1.x()<<","<<p1.y()<<std::endl;
    std::cout<<"widget"<<this->parentWidget()<<std::endl;
    std::cout<<"object"<<this->parentObject()<<std::endl;
    this->setObjectName("cliked rectangle");
    if(event->button() == Qt::LeftButton)
        emit riquadroCliccatoSx();
    else if (event->button() == Qt::RightButton)
        emit riquadroCliccatoDx();
    //QGraphicsItem::mousePressEvent(event);
}
void ProvaRiquadro::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "mousereleeaseEvent"<<std::endl;
    QGraphicsItem::mouseReleaseEvent(event);
}
void ProvaRiquadro::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
QRectF rec = boundingRect();
QBrush brush(Qt::gray);
painter->fillRect(rec,brush);
painter->drawRect(rec);
}
void ProvaRiquadro::advance()
{
QPointF location = this->pos();
std::cout<<"("<<location.x() << "," << location.y()<<")"<<std::endl;
//line update.
}
QRectF ProvaRiquadro::boundingRect() const
{
return QRect (0,0,20,20);
}
