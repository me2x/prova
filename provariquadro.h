#ifndef PROVARIQUADRO_H
#define PROVARIQUADRO_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene> // ???
#include <QPointer>

class ProvaRiquadro : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    ProvaRiquadro();
    QRectF boundingRect() const;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0);
    std::map<ProvaRiquadro*, QGraphicsLineItem*> starting_lines,arriving_lines; //stores the points where the arriving lines start (starting_points), and where the starting lines arrive (arriving_points)
signals:
    void riquadroCliccatoSx();
    void riquadroCliccatoDx();
    void riquadroMosso();
protected:
    
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent* event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event);
    void advance();

};

#endif // PROVARIQUADRO_H
