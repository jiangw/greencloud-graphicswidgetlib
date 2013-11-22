#include "cimgwidget.h"

CImgWidget::CImgWidget(int a_iWidth, int a_iHeight, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;

    this->InitBoundingRect();
}

CImgWidget::CImgWidget(QString a_qstrImgFileName, int a_iWidth, int a_iHeight,\
                       CGraphicsWidget* a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;

    QPixmap l_CPixmap(a_qstrImgFileName);
    m_CBackgroundBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight));

    this->InitBoundingRect();
}

void CImgWidget::SetImg(QString a_qstrImgFileName)
{
    QPixmap l_CPixmap(a_qstrImgFileName);
    m_CBackgroundBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight));
    update(this->boundingRect());
}

void CImgWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QBrush(Qt::black), 4));

    painter->drawRect(this->boundingRect());
    if(!m_CBackgroundBrush.texture().isNull())
    {
        painter->fillRect(this->boundingRect(), m_CBackgroundBrush);
    }

    painter->restore();
}
