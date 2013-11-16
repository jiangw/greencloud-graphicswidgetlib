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

void CGraphicsWidget::InitBoundingRect()
{
    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CGraphicsWidget::UpdateBoundingRect(int a_iWidth, int a_iHeight)
{
    this->prepareGeometryChange();
    m_CBR.setWidth(a_iWidth);
    m_CBR.setHeight(a_iHeight);
}

void CGraphicsWidget::UpdateBoundingRect()
{
    this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

QRectF CGraphicsWidget::boundingRect() const
{
    return m_CBR;
}

void CGraphicsWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef PF_TEST
    std::cout << "Mouse Press." << std::endl;
#endif

    m_CMouseLastPos = event->pos();
}

void CGraphicsWidget::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef PF_TEST
    std::cout << "Mouse Release." << std::endl;
#endif

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
//        this->setCursor(QCursor(Qt::ArrowCursor));
    }
}

void CGraphicsWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
#ifdef PF_TEST
    std::cout << "Mouse Move." << std::endl;
#endif
    if(QLineF(event->pos(), m_CMouseLastPos).length() \
            > CGraphicsWidget::s_dMouseMoveDistThreshold)
    {
//        this->setCursor(QCursor(Qt::ClosedHandCursor));
        this->MouseDragMove(event->pos());
    }
}
