#ifndef CGRAPHICSWIDGET_H
#define CGRAPHICSWIDGET_H

#include <QObject>
#include <QGraphicsItem>
#include <QRectF>
#include <QPointF>
#include <QLineF>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QCursor>

#include <iostream>

class CGraphicsWidget : public QObject, public QGraphicsItem
{
    Q_OBJECT

public:
    CGraphicsWidget(CGraphicsWidget* a_pParent);
    virtual void ResetWidget(){}
    void InitBoundingRect(int a_iWidth, int a_iHeight);
    void InitBoundingRect(); //overloaded function
    void UpdateBoundingRect(int a_iWidth, int a_iHeight);
    void UpdateBoundingRect(); //overloaded function
    virtual int WidgetWidth() = 0;
    virtual int WidgetHeight() = 0;
    virtual QString WidgetClassName()\
    {return "CGraphicsWidget";} //return the class name of this widget
    virtual void Hightlight(bool a_blHightlight)\
    {Q_UNUSED(a_blHightlight)}//highlight widget
    void MouseDragSwitch(bool a_blMouseDrag)\
    {m_blMouseDragFlag = a_blMouseDrag;}

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
    virtual void WheelScroll(int a_iSteps)\
    {Q_UNUSED(a_iSteps)}
    //override from QGraphicsItem
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    void wheelEvent(QGraphicsSceneWheelEvent *event);

signals:
    void SIGNAL_LeftButtonClicked();
    void SIGNAL_LeftButtonClicked(QPointF a_CMousePos);
    void SIGNAL_RightButtonClicked();
    void SIGNAL_RightButtonClicked(QPointF a_CMousePos);
    void SIGNAL_MouseDoubleClicked();
    void SIGNAL_MouseDoubleClicked(QPointF a_CMousePos);
    void SIGNAL_MouseDragRelease(QPointF a_CMouseScenePos, CGraphicsWidget* a_pWhoAmI);
    void SIGNAL_WheelScroll(int a_iSteps); //a_iSteps > 0 forward, else backward

    void SIGNAL_RemoveWidget(CGraphicsWidget* a_pRemoveWidget);

    void SIGNAL_WidgetSizeChanged();

private:
    QRectF m_CBR;
    QPointF m_CMouseLastPos;
    bool m_blMouseDragFlag;//true(default): enable mouse drag, false: disable mouse drag
};

#endif // CGRAPHICSWIDGET_H
