#ifndef PROVARIQUADRO_H
#define PROVARIQUADRO_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene> // ???
#include <QPointer>
#include "handleitem.h"
#include "arrow.h"
//class Arrow;
class ProvaRiquadro : public QGraphicsObject
{
    Q_OBJECT
     

   
public:
    enum { ProvaRiquadro_type = UserType + 1 };
    int type() const
    {// Enable the use of qgraphicsitem_cast with this item.
       return ProvaRiquadro_type;
    }
    ProvaRiquadro();
    void setLayer(int i);
    QRectF boundingRect() const;
    QRectF rect();
    void setArrowTarget(); //serve per deselezionare quando viene rilasciato dal click crea arrow. 
    void setRect(QRectF rect);
    QGraphicsTextItem * text;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    std::map<ProvaRiquadro*,/* QGraphicsLineItem**/ Arrow* > starting_lines,arriving_lines; 
//    void update_lines();
    void erase_lines();
    void redraw_lines();
    //stores the points where the arriving lines start (starting_points), and where the starting lines arrive (arriving_points)
   // void setFocus(bool value);
signals:
    void riquadroCliccatoSx();
    void riquadroCliccatoDx();
    void riquadroMosso();
    void riquadroDoubleClick();
    
public slots:
    void provaselected();
protected:
   // virtual QVariant itemChange(GraphicsItemChange change, const QVariant& value);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void advance();
private:
    QBrush brush;
    QRectF rekt;
    bool being_moved, arrow_target;
};

#endif // PROVARIQUADRO_H
