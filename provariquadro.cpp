#include "provariquadro.h"
#include <iostream>
#include <QGraphicsWidget>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>
#include <qitemselectionmodel.h>
#include "handleitem.h"

ProvaRiquadro::ProvaRiquadro()
{
    setFlag(ItemIsMovable);
    setFlag(ItemIsSelectable);
    text = new QGraphicsTextItem(this);
    //->text->setTextInteractionFlags(Qt::TextEditorInteraction);
    text->setPos(5,5);
    text->setPlainText("Test");
    rekt = QRect (0,0,60,30);
    brush = QBrush(Qt::gray);
    arrow_target = false;
    HandleItem *topHandle = new HandleItem( this, (this->scene()), Qt::red, HandleItem::TopHandle );
    HandleItem *rightHandle = new HandleItem( this, this->scene(), Qt::red, HandleItem::RightHandle );
    HandleItem *leftHandle = new HandleItem( this, this->scene(), Qt::red, HandleItem::LeftHandle );
    HandleItem *bottomHandle = new HandleItem( this, this->scene(), Qt::red, HandleItem::BottomHandle );
    HandleItem *centerHandle = new HandleItem( this, this->scene(), Qt::red, HandleItem::CenterHandle, QList<HandleItem*>() << topHandle << rightHandle << leftHandle << bottomHandle );
    topHandle->setParentItem(this);
    rightHandle->setParentItem(this);
    leftHandle->setParentItem(this);
    bottomHandle->setParentItem(this);
    centerHandle->setParentItem(this);
  
 //   this->scene()->addItem(topHandle);
    //QItemSelectionModel::selectionChanged(const QItemSelection & selected, const QItemSelection & deselected);
   
}
void ProvaRiquadro::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "mouseDoubleClickEvent"<<std::endl;
    this->setSelected(false);
    emit riquadroDoubleClick();
   // QGraphicsItem::mouseDoubleClickEvent(event);
}
void ProvaRiquadro::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
  //  advance();
    being_moved=true;
    std::cout << "mousemoveEvent"<<std::endl;
    std::cerr<<"selected items are: "<<this->scene()->selectedItems().size()<<std::endl;
    erase_lines();
    event->accept();
    QGraphicsItem::mouseMoveEvent(event);
    //std::cout <<"bugseeker"<<std::endl;
    redraw_lines();
    
   // this->setSelected(false);
 
    emit riquadroMosso();
}
void ProvaRiquadro::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    std::cout << "mouseClickEvent("<<event->pos().x()<<","<<event->pos().y()<<")"<<std::endl;
    std::cout <<"rect top right is: "<<rect().topRight().x()<<","<<rect().topRight().y() << " and left bot is: "<<rect().bottomLeft().x()<<","<<rect().bottomLeft().y()<<std::endl;
    this->setSelected(true);
    std::cout<<this->text->toPlainText().toStdString()<<std::endl;
    QPointF p = mapToScene(event->pos());
    QPoint p1 = QCursor::pos();
    std::cout<<p.x()<<","<<p.y()<<std::endl;
    std::cout<<p1.x()<<","<<p1.y()<<std::endl;
    std::cout<<"widget"<<this->parentWidget()<<std::endl;
    std::cout<<"object"<<this->parentObject()<<std::endl;
    this->setObjectName("cliked rectangle");
    if(event->button() == Qt::LeftButton)
    {
#if 0
        std::cerr<<"selected items are: "<<this->scene()->selectedItems().size()<<std::endl;
           foreach(QGraphicsItem* selectedItem, this->scene()->selectedItems())
        { 
            std::cout<<selectedItem->type()<<std::endl;
            if (selectedItem->type() == QGraphicsItem::UserType)
            {
                ProvaRiquadro* tmp = (ProvaRiquadro*)selectedItem;
                std::cout << tmp->text->toPlainText().toStdString()<<std::endl;
                //tmp->setSelected(false);
            }
            // perform action with selectedItem
        }
        this->setSelected(false);
        std::cerr<<"selected items are: "<<this->scene()->selectedItems().size()<<std::endl;
        std::cout << "no more seeleected"<<std::endl;
#endif
        emit riquadroCliccatoSx();
    }
    else if (event->button() == Qt::RightButton)
        emit riquadroCliccatoDx();
    //QGraphicsItem::mousePressEvent(event);
}
void ProvaRiquadro::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{

    std::cout << "mousereleeaseEvent"<<std::endl;
    QGraphicsItem::mouseReleaseEvent(event);
    //event->accept();
    std::cout<<"selected items are: "<<this->scene()->selectedItems().size()<<std::endl;
    if(being_moved || arrow_target)
    {
    this->setSelected(false);
    std::cout<<"selected items are: "<<this->scene()->selectedItems().size()<<std::endl;
    being_moved = false;
    arrow_target = false;
    }
    
    std::cout<<"release end"<<std::endl;
}
void ProvaRiquadro::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
QRectF rec = boundingRect();

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
return rekt;
}
QRectF ProvaRiquadro::rect() 
{
return rekt;
}
void ProvaRiquadro::setRect(QRectF rect)
{
rekt = rect;
//paint();//??????????
}
void ProvaRiquadro::provaselected()
{
    if(this->isSelected())
        std::cout <<"provaselected: "<< this->text->toPlainText().toStdString() <<" is selected"<<std::endl;
    else
        std::cout <<"provaselected: "<< this->text->toPlainText().toStdString() <<" is not selected"<<std::endl;
}
/*QVariant ProvaRiquadro::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant& value)
{
    text->setPos(rekt.center());
    return QGraphicsItem::itemChange(change, value);
}
*/
/*
QVariant ProvaRiquadro::itemChange(GraphicsItemChange change, const QVariant & value){
    text->setPos(rekt.center());
}*/
/*
void ProvaRiquadro::update_lines(){
    
    
        QPen blackpen = QPen(Qt::black);
    for (std::map<ProvaRiquadro*,Arrow*>::iterator it = arriving_lines.begin(); it!= arriving_lines.end();++it)
    {
        //draw new line.
        std::cout <<"bugseeker2"<<std::endl;
        ProvaRiquadro* tmp = (*it).first;
        tmp->scene()->removeItem(tmp->starting_lines.at(this)); 
        QPointF* starting_point = new QPointF(tmp->x()+tmp->boundingRect().center().x(),
                                             tmp->y()+tmp->boundingRect().bottom());
        QPointF* arrival_point = new QPointF (this->x()+this->boundingRect().center().x(),
                                             this->y()+this->boundingRect().top());
        QLineF newline(*starting_point,*arrival_point);
        QGraphicsLineItem* curr_line_item = this->scene()->addLine(newline,blackpen);
      
        
        this->arriving_lines.at(tmp) = curr_line_item;
        tmp->starting_lines.at(this) = curr_line_item;
        
    }
    for (std::map<ProvaRiquadro*,Arrow*>::iterator it = starting_lines.begin(); it!= starting_lines.end();++it)
    {
        //draw new line.
        std::cout <<"bugseeker3"<<std::endl;
        ProvaRiquadro* tmp = (*it).first;
        tmp->scene()->removeItem(tmp->arriving_lines.at(this)); 
        QPointF* starting_point = new QPointF(tmp->x()+tmp->boundingRect().center().x(),
                                             tmp->y()+tmp->boundingRect().bottom());
        QPointF* arrival_point = new QPointF (this->x()+this->boundingRect().center().x(),
                                             this->y()+this->boundingRect().top());
        QLineF newline(*starting_point,*arrival_point);
        QGraphicsLineItem* curr_line_item = this->scene()->addLine(newline,blackpen);
      
        
        this->starting_lines.at(tmp) = curr_line_item;
        tmp->arriving_lines.at(this) = curr_line_item;
       
    }
}
*/
void ProvaRiquadro::setLayer(int i)
{
    switch (i)
    {
        case 0:
        {
            brush = QBrush(Qt::yellow);
            break;
        }
        case 1:
        {
            brush = QBrush(Qt::magenta);
            break;
        }
        case 2:
        {
            brush = QBrush(Qt::cyan);
            break;
        }
        case 3:
        {
            brush = QBrush(Qt::blue);
            break;
        }
        case 4:
        {
            brush = QBrush(Qt::green);
            break;
        }
        default:
        {
            brush = QBrush(Qt::gray);
            break;
        }
    }
}
void ProvaRiquadro::erase_lines()
{

}
void ProvaRiquadro::redraw_lines()
{
    std::cout<<"enteer redraw lines function"<<std::endl;
    for (std::map<ProvaRiquadro*,Arrow*>::iterator it = starting_lines.begin(); it!= starting_lines.end();++it)
    {
        Arrow* tmp = (*it).second;
        std::cout<<"tmp assigned: "<<tmp<<std::endl;
        tmp->update();
    }
      for (std::map<ProvaRiquadro*,Arrow*>::iterator it = arriving_lines.begin(); it!= arriving_lines.end();++it)
    {
        Arrow* tmp = (*it).second;
        std::cout<<"tmp assigned: "<<tmp<<std::endl;
        tmp->update();
    }
    
    
}
void ProvaRiquadro::setArrowTarget()
{
    std::cout<<"target set"<<std::endl;
    arrow_target=true;
}
