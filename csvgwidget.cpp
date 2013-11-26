#include "csvgwidget.h"

CSvgWidget::CSvgWidget(QString a_qstrSvgFile, int a_iWidgetWidth, int a_iWidgetHeight,\
                       CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidgetWidth;
    m_iHeight = a_iWidgetHeight;
    m_qstrFileName = a_qstrSvgFile;
    this->InitBoundingRect(m_iWidth, m_iHeight);

    m_pSvgRender = new QSvgRenderer(a_qstrSvgFile, this);
}

int CSvgWidget::WidgetWidth()
{
    return m_iWidth;
}

int CSvgWidget::WidgetHeight()
{
    return m_iHeight;
}

void CSvgWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    m_pSvgRender->render(painter, this->boundingRect());

    painter->restore();
}
