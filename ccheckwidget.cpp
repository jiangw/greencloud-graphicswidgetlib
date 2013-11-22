#include "ccheckwidget.h"

CCheckWidget::CCheckWidget(CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidgetSize = 18;
    m_blChecked = false;
    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CCheckWidget::SetChecked(bool a_blIsChecked)
{
    m_blChecked = a_blIsChecked;
}

void CCheckWidget::BoundingWithWidget(CGraphicsWidget *a_pBoundingWidget)
{
    m_pBoundingWidget = a_pBoundingWidget;
}

int CCheckWidget::WidgetWidth()
{
    return m_iWidgetSize;
}

int CCheckWidget::WidgetHeight()
{
    return m_iWidgetSize;
}

void CCheckWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    //draw outline
    painter->setPen(QPen(QBrush(Qt::black), 2));
    painter->drawRect(this->boundingRect());
    //draw selection box if item is selected
    if(m_blChecked)
    {
        QRectF l_CSelBox(this->boundingRect().x() + 3, this->boundingRect().y() + 3,\
                         this->boundingRect().width() - 6, this->boundingRect().height() - 6);
        painter->fillRect(l_CSelBox, Qt::SolidPattern);
    }

    painter->restore();
}

void CCheckWidget::LeftButtonClicked(QPointF a_CMousePos)
{
    Q_UNUSED(a_CMousePos)

    m_blChecked = !m_blChecked;
    update(this->boundingRect());
}
