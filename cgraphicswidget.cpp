#include "cgraphicswidget.h"

qreal CGraphicsWidget::s_dMouseMoveDistThreshold = 3;

CGraphicsWidget::CGraphicsWidget(CGraphicsWidget *a_pParent)
    :QGraphicsItem(a_pParent)
{
}

void CGraphicsWidget::InitBoundingRect(int a_iWidth, int a_iHeight)
{
    m_CBR.setRect(0, 0, a_iWidth, a_iHeight);
}

void CGraphicsWidget::UpdateBoundingRect(int a_iWidth, int a_iHeight)
{
    this->prepareGeometryChange();
    m_CBR.setWidth(a_iWidth);
    m_CBR.setHeight(a_iHeight);
}

QRectF CGraphicsWidget::boundingRect() const
{
    return m_CBR;
}

void CGraphicsWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_CMouseLastPos = event->pos();
    }
}

void CGraphicsWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(QLineF(event->pos(), m_CMouseLastPos).length() \
                < CGraphicsWidget::s_dMouseMoveDistThreshold)
        {
            emit this->SIGNAL_LeftButtonClicked();
            emit this->SIGNAL_LeftButtonClicked(event->pos());
            this->LeftButtonClicked(event->pos());
        }
    }
}
