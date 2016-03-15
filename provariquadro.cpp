#include "provariquadro.h"
#include <iostream>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
ProvaRiquadro::ProvaRiquadro()
{
    setFlag(ItemIsMovable);
    text = new QGraphicsTextItem(this);
    //->text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setPos(5,5);
    text->setPlainText("Test");
   
}
void ProvaRiquadro::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "mouseDoubleClickEvent"<<std::endl;
    emit riquadroDoubleClick();
    QGraphicsItem::mouseDoubleClickEvent(event);
}
void ProvaRiquadro::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  //  advance();
    std::cout << "mousemoveEvent"<<std::endl;
    QGraphicsItem::mouseMoveEvent(event);
    QPen blackpen = QPen(Qt::black);
    for (std::map<ProvaRiquadro*,QGraphicsLineItem*>::iterator it = arriving_lines.begin(); it!= arriving_lines.end();++it)
    {
        //draw new line.
        ProvaRiquadro* tmp = (*it).first;
        tmp->scene()->removeItem(tmp->starting_lines.at(this)); //???????
        QPointF* starting_point = new QPointF(tmp->x()+tmp->boundingRect().center().x(),
                                             tmp->y()+tmp->boundingRect().bottom());
        QPointF* arrival_point = new QPointF (this->x()+this->boundingRect().center().x(),
                                             this->y()+this->boundingRect().bottom());
        QLineF newline(*starting_point,*arrival_point);
        QGraphicsLineItem* curr_line_item = this->scene()->addLine(newline,blackpen);
      
        
        this->arriving_lines.at(tmp) = curr_line_item;
        tmp->starting_lines.at(this) = curr_line_item;
    }
    for (std::map<ProvaRiquadro*,QGraphicsLineItem*>::iterator it = starting_lines.begin(); it!= starting_lines.end();++it)
    {
        //draw new line.
        ProvaRiquadro* tmp = (*it).first;
        tmp->scene()->removeItem(tmp->arriving_lines.at(this)); //???????
        QPointF* starting_point = new QPointF(tmp->x()+tmp->boundingRect().center().x(),
                                             tmp->y()+tmp->boundingRect().bottom());
        QPointF* arrival_point = new QPointF (this->x()+this->boundingRect().center().x(),
                                             this->y()+this->boundingRect().bottom());
        QLineF newline(*starting_point,*arrival_point);
        QGraphicsLineItem* curr_line_item = this->scene()->addLine(newline,blackpen);
      
        
        this->starting_lines.at(tmp) = curr_line_item;
        tmp->arriving_lines.at(this) = curr_line_item;
        
    }
    
    
    
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
return QRect (0,0,60,30);
}
