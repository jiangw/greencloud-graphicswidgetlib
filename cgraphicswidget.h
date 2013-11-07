#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPointF>
#include <QLineF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>

class CGraphicsWidget : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CGraphicsWidget(QGraphicsItem* a_pParent);
    virtual int WidgetWidth() = 0;
    virtual int WidgetHeight() = 0;
    void InitBoundingRect(int a_iWidth, int a_iHeight);

    static qreal s_dMouseMoveDistThreshold;

    //override from QGraphicsItem
    QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) = 0;

protected:
    //override from QGraphicsItem
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void SIGNAL_LeftButtonClicked();
    void SIGNAL_LeftButtonClicked(QPointF a_CMousePos);

private:
    QRectF m_CBR;
    QPointF m_CMouseLastPos;
};

#endif // CGRAPHICSWIDGET_H
