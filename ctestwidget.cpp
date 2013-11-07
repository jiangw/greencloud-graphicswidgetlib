#include "ctestwidget.h"

CTestWidget::CTestWidget(int a_iWidth, int a_iHeight, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;

    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    m_qstrMsg = "Test Widget";

    connect(this, SIGNAL(SIGNAL_LeftButtonClicked()),
            this, SLOT(SLOT_LeftButtonClickProc()));
}

int CTestWidget::WidgetWidth()
{
    return m_iWidth;
}

int CTestWidget::WidgetHeight()
{
    return m_iHeight;
}

void CTestWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(this->boundingRect());
    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_qstrMsg);

    painter->restore();
}

void CTestWidget::SLOT_LeftButtonClickProc()
{
    m_qstrMsg = "Left button clicked";
    update(this->boundingRect());
}
