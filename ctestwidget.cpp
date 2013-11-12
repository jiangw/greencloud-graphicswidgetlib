#include "ctestwidget.h"

CTestWidget::CTestWidget(int a_iWidth, int a_iHeight, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;

    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    m_qstrMsg = "Test Widget";
}

void CTestWidget::SetWidgetName(QString a_qstrName)
{
    m_qstrWidgetName = a_qstrName;
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

void CTestWidget::LeftButtonClicked(QPointF a_CMousePos)
{
    m_qstrMsg = "Left button clicked";
    update(this->boundingRect());
}

void CTestWidget::MouseDragMove(QPointF a_CMousePos)
{
    m_qstrMsg = "Mouse drag move";
    update(this->boundingRect());
}

void CTestWidget::MouseDragRelease(QPointF a_CMousePos)
{
    this->prepareGeometryChange();
    m_qstrMsg = "Mouse drag release";
//    if(!this->contains(a_CMousePos))
//    {
//        QPointF l_CCenter = this->mapToScene(a_CMousePos);
//        this->setPos(l_CCenter.x() - this->boundingRect().width() / 2, \
//                     l_CCenter.y() - this->boundingRect().height() / 2);
//    }
}

void CTestWidget::SLOT_MouseDragDropProc(QPointF a_CMouseScenePos, CGraphicsWidget *a_pWhoAmI)
{
    if(this->contains(this->mapFromScene(a_CMouseScenePos)))
    {
        if(qstrcmp(a_pWhoAmI->WidgetClassName().toAscii(), "CTestWidget") == 0)
        {
            m_qstrMsg = "Mouse drag drop";
            update(this->boundingRect());
        }
    }
}
