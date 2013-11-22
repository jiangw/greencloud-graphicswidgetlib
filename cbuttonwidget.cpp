#include "cbuttonwidget.h"

const int CButtonWidget::s_iButtonMinWidth = 50;
const int CButtonWidget::s_iButtonMinHeight = 24;

CButtonWidget::CButtonWidget(QString a_qstrText, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_qstrText = a_qstrText;
    m_iStrWidthExt = 8;
    m_iStrHeightExt = 4;
    m_iTextFontSize = 14;
    m_CButtonFont.setFamily("Courier New");
    m_CButtonFont.setPointSize(m_iTextFontSize);
    QFontMetrics l_CFontMetric(m_CButtonFont);
    QRectF l_CStrRect = l_CFontMetric.boundingRect(m_qstrText);
    m_iStrWidth = l_CStrRect.width();
    m_iStrHeight = l_CStrRect.height();

    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CButtonWidget::SetText(QString a_qstrText)
{
    m_qstrText = a_qstrText;
    QFontMetrics l_CFontMetric(m_CButtonFont);
    QRectF l_CStrRect = l_CFontMetric.boundingRect(m_qstrText);
    m_iStrWidth = l_CStrRect.width();
    m_iStrHeight = l_CStrRect.height();

    this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CButtonWidget::SetTextFontSize(int a_iSize)
{
    m_CButtonFont.setPointSize(a_iSize);
    this->SetText(m_qstrText);
}

int CButtonWidget::WidgetWidth()
{
    int l_iWidth = m_iStrWidth + m_iStrWidthExt;
    return l_iWidth > CButtonWidget::s_iButtonMinWidth ?\
                l_iWidth : CButtonWidget::s_iButtonMinWidth;
}

int CButtonWidget::WidgetHeight()
{
    int l_iHeight = m_iStrHeight + m_iStrHeightExt;
    return l_iHeight > CButtonWidget::s_iButtonMinHeight ?\
                l_iHeight : CButtonWidget::s_iButtonMinHeight;
}

void CButtonWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(QPen(QBrush(Qt::black), 2));
    painter->setFont(m_CButtonFont);
    //draw outline
    painter->drawRoundedRect(this->boundingRect(), 5, 5);
    //draw text
    painter->drawText(this->boundingRect(), Qt::AlignCenter, m_qstrText);

    painter->restore();
}

void CButtonWidget::LeftButtonClicked(QPointF a_CMousePos)
{
    Q_UNUSED(a_CMousePos)

    emit this->SIGNAL_ButtonTriggered();
}
