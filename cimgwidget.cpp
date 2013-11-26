#include "cimgwidget.h"

CImgWidget::CImgWidget(int a_iWidth, int a_iHeight, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;
    m_blHightlight = false;

    QPixmap l_CPixmap(":/icon/brush_add");
    m_CBackgroundBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight,\
                                                   Qt::IgnoreAspectRatio,\
                                                   Qt::SmoothTransformation));

    this->InitBoundingRect();
}

CImgWidget::CImgWidget(QString a_qstrImgFileName, int a_iWidth, int a_iHeight,\
                       CGraphicsWidget* a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;
    m_qstrFileName = a_qstrImgFileName;

    QPixmap l_CPixmap(a_qstrImgFileName);
    if(l_CPixmap.isNull())
    {
        l_CPixmap.load(":/icon/brush_add");
    }
    m_CBackgroundBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight,\
                                                   Qt::IgnoreAspectRatio,\
                                                   Qt::SmoothTransformation));

    this->InitBoundingRect();
}

void CImgWidget::SetImg(QString a_qstrImgFileName)
{
    m_qstrFileName = a_qstrImgFileName;
    QPixmap l_CPixmap(a_qstrImgFileName);
    if(l_CPixmap.isNull())
    {
        l_CPixmap.load(":/icon/brush_add");
    }
    m_CBackgroundBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight,\
                                                   Qt::IgnoreAspectRatio,\
                                                   Qt::SmoothTransformation));
    update(this->boundingRect());
}

void CImgWidget::ClearImg()
{
    m_qstrFileName.clear();

    QPixmap l_CPixmap(":/icon/brush_add");
    m_CBackgroundBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight));
    update(this->boundingRect());
}

void CImgWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    if(m_blHightlight)
    {
        painter->setPen(QPen(QBrush(Qt::green), 4));
    }
    else
    {
        painter->setPen(QPen(QBrush(Qt::black), 4));
    }

    QRectF l_CRect(this->boundingRect().x() + 2, this->boundingRect().y() + 2,\
                   this->boundingRect().width() - 4, this->boundingRect().height() - 4);
    painter->drawRect(l_CRect);
    if(!m_CBackgroundBrush.texture().isNull())
    {
        painter->fillRect(l_CRect, m_CBackgroundBrush);
    }

    painter->restore();
}

void CImgWidget::Hightlight(bool a_blHightlight)
{
    m_blHightlight = a_blHightlight;
    update(this->boundingRect());
}

void CImgWidget::MouseDragMove(QPointF /*a_CMousePos*/)
{
    QPixmap l_CPixmap(m_qstrFileName);
    if(l_CPixmap.isNull())
    {
        l_CPixmap.load(":/img/defaultcover");
    }
    this->setCursor(QCursor(l_CPixmap.scaled(64, 64, Qt::IgnoreAspectRatio,\
                                                           Qt::SmoothTransformation)));
}

void CImgWidget::MouseDragRelease(QPointF /*a_CMousePos*/)
{
    this->setCursor(Qt::ArrowCursor);
}
