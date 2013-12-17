#include "cgraphicswidget.h"

qreal CGraphicsWidget::s_dMouseMoveDistThreshold = 3;

CGraphicsWidget::CGraphicsWidget(CGraphicsWidget *a_pParent)
    :QGraphicsItem(a_pParent)
{
    m_blMouseDragFlag = true;
    m_blFreezed = false;
}

void CGraphicsWidget::InitBoundingRect(int a_iWidth, int a_iHeight)
{
    m_CBR.setRect(0, 0, a_iWidth, a_iHeight);
}

void CGraphicsWidget::InitBoundingRect()
{
    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CGraphicsWidget::UpdateBoundingRect(int a_iWidth, int a_iHeight)
{
    this->prepareGeometryChange();
    m_CBR.setWidth(a_iWidth);
    m_CBR.setHeight(a_iHeight);
    emit this->SIGNAL_WidgetSizeChanged();
}

void CGraphicsWidget::UpdateBoundingRect()
{
    this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CGraphicsWidget::FreezeWidget(bool a_blFreezed)
{
    m_blFreezed = a_blFreezed;
    if(m_blFreezed)
    {
        this->setVisible(false);
    }
    else
    {
        this->setVisible(true);
    }
}

bool CGraphicsWidget::IsFreezed()
{
    return m_blFreezed;
}

QRectF CGraphicsWidget::boundingRect() const
{
    return m_CBR;
}

void CGraphicsWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_CMouseLastPos = event->pos();
}

void CGraphicsWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(QLineF(event->pos(), m_CMouseLastPos).length() \
            <= CGraphicsWidget::s_dMouseMoveDistThreshold) //mouse did not move
    {
        if(event->button() == Qt::LeftButton)
        { //left button clicked
            emit this->SIGNAL_LeftButtonClicked();
            emit this->SIGNAL_LeftButtonClicked(event->pos());
            this->LeftButtonClicked(event->pos());
        }
        else if(event->button() == Qt::RightButton)
        { //right button clicked
            emit this->SIGNAL_RightButtonClicked();
            emit this->SIGNAL_RightButtonClicked(event->pos());
            this->RightButtonClicked(event->pos());
        }
    }
    else
    {
        if(!this->contains(event->pos()))
        {
            emit this->SIGNAL_MouseDragRelease(this->mapToScene(event->pos()), this);
        }
        this->MouseDragRelease(event->pos());
    }
}

void CGraphicsWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_blMouseDragFlag)
    {
        if(QLineF(event->pos(), m_CMouseLastPos).length() \
                > CGraphicsWidget::s_dMouseMoveDistThreshold)
        {
            this->MouseDragMove(event->pos());
        }
    }
    else
    {
        event->ignore();
    }
}

void CGraphicsWidget::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    emit this->SIGNAL_MouseDoubleClicked();
    emit this->SIGNAL_MouseDoubleClicked(event->pos());
}

void CGraphicsWidget::wheelEvent(QGraphicsSceneWheelEvent *event)
{
    this->WheelScroll(event->delta() / 120);
    emit this->SIGNAL_WheelScroll(event->delta() / 120);
}
