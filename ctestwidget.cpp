#include "ctestwidget.h"

CTestWidget::CTestWidget(int a_iWidth, int a_iHeight, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_iWidth = a_iWidth;
    m_iHeight = a_iHeight;

//    QPixmap l_CPixmap;
//    if(l_CPixmap.load("/home/jiang/GreenClouD/icon_edit.png"))
//    {
//        m_CBrush.setTexture(l_CPixmap.scaled(m_iWidth, m_iHeight));
//    }
//    else
//    {
//        std::cout << "Cannot load image." << std::endl;
//    }

    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    m_qstrMsg = "Test Widget";

    m_pSvgRender = new QSvgRenderer(QString("/home/jiang/GreenClouD/icon_edit.svg"), this);
//    QPixmap l_CPixmap(80, 80);
//    l_CPixmap.fill();
//    QPainter l_CPainter(&l_CPixmap);
//    m_pSvgRender->render(&l_CPainter);
//    m_CBrush.setTexture(l_CPixmap);
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
//    painter->drawRect(this->boundingRect());
//    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_qstrMsg);
//    painter->fillRect(this->boundingRect(), m_CBrush);
    m_pSvgRender->render(painter, this->boundingRect());

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
