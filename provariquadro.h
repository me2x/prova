#ifndef PROVARIQUADRO_H
#define PROVARIQUADRO_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene> // ???
#include <QPointer>
#include "handleitem.h"

class ProvaRiquadro : public QGraphicsObject
{
    Q_OBJECT
public:
    ProvaRiquadro();
    QRectF boundingRect() const;
    QRectF rect();
    void setRect(QRectF rect);
    QGraphicsTextItem * text;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    std::map<ProvaRiquadro*, QGraphicsLineItem*> starting_lines,arriving_lines; 
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
    QRectF rekt;
    bool being_moved;
};

#endif // PROVARIQUADRO_H
