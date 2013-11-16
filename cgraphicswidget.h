#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

//#include "gconfig.h"
#define PF_TEST

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPointF>
#include <QLineF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#ifdef PF_TEST
#include <iostream>
#endif

class CGraphicsWidget : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CGraphicsWidget(CGraphicsWidget* a_pParent);
    void InitBoundingRect(int a_iWidth, int a_iHeight);
    void InitBoundingRect(); //overloaded function
    void UpdateBoundingRect(int a_iWidth, int a_iHeight);
    void UpdateBoundingRect(); //overloaded function
    virtual int WidgetWidth() = 0;
    virtual int WidgetHeight() = 0;
    virtual QString WidgetClassName()\
    {return "CGraphicsWidget";} //return the class name of this widget

    static qreal s_dMouseMoveDistThreshold;

    //override from QGraphicsItem
    QRectF boundingRect() const;

protected:
    virtual void LeftButtonClicked(QPointF a_CMousePos)\
    {Q_UNUSED(a_CMousePos)}
    virtual void RightButtonClicked(QPointF a_CMousePos)\
    {Q_UNUSED(a_CMousePos)}
    virtual void MouseDragMove(QPointF a_CMousePos)\
    {Q_UNUSED(a_CMousePos)}
    virtual void MouseDragRelease(QPointF a_CMousePos)\
    {Q_UNUSED(a_CMousePos)} //process mouse drag release event of the widget itself
    //override from QGraphicsItem
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

signals:
    void SIGNAL_LeftButtonClicked();
    void SIGNAL_LeftButtonClicked(QPointF a_CMousePos);
    void SIGNAL_RightButtonClicked();
    void SIGNAL_RightButtonClicked(QPointF a_CMousePos);
    void SIGNAL_MouseDragRelease(QPointF a_CMouseScenePos, CGraphicsWidget* a_pWhoAmI);

private:
    QRectF m_CBR;
    QPointF m_CMouseLastPos;
};

#endif // CGRAPHICSWIDGET_H
