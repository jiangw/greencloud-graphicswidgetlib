#include "ctextwidget.h"

CTextWidget::CTextWidget(bool a_blEditable, CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_blSizeFixed = false;
    m_blHasOutline = true;
    m_blHasUnderline = false;
    m_iFontSize = 12;
    m_iTextWidthExt = 10;
    m_iTextHeightExt = 9;
    m_iWidgetFixedHeight = -1;
    m_iWidgetFixedWidth = -1;
    m_iWidgetMinimHeight = 0;
    m_iWidgetMinimWidth = 0;

    m_CTipFont.setFamily("Arial");
    m_CTipFont.setItalic(true);
    m_CTipFont.setPointSize(m_iFontSize);
    m_CTipPen.setColor(Qt::darkGray);

    m_CTextFont.setFamily("Arial");
    m_CTextFont.setPointSize(m_iFontSize);
    m_CTextPen.setColor(Qt::black);

    m_pTextEditor = new CTextEditor(this);
    m_pTextEditor->setFont(m_CTextFont);
    m_pTextEditor->setPos(0, 0);
    m_pTextEditor->setVisible(false);
    connect(m_pTextEditor, SIGNAL(SIGNAL_EditFinished()),\
            this, SLOT(SLOT_EditFinishProc()));
    this->SetEditable(a_blEditable);

    m_qstrTip = "Text Widget";
    QFontMetrics l_CFontMetrics(m_CTipFont);
    QRectF l_CBR = l_CFontMetrics.boundingRect(m_qstrTip);
    m_iTextWidth = l_CBR.width();
    m_iTextHeight = l_CBR.height();
    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

void CTextWidget::SetEditable(bool a_blEditable)
{
    m_blEditable = a_blEditable;
    m_pTextEditor->SetEditMode(CTextEditor::SINGLELINE);
}

void CTextWidget::SetFontSize(int a_iFontSize)
{
    m_CTipFont.setPointSize(a_iFontSize);
    m_CTextFont.setPointSize(a_iFontSize);
    this->TextChanged();
}

void CTextWidget::SetFont(QFont a_CFont)
{
    m_CTextFont = a_CFont;
    this->TextChanged();
}

void CTextWidget::SetInputTip(QString a_qstrTip)
{
    m_qstrTip = a_qstrTip;
    this->TextChanged();
}

void CTextWidget::SetFixedSize(int a_iFixedWidth, int a_iFixedHeight)
{
    m_blSizeFixed = true;
    m_iWidgetFixedWidth = a_iFixedWidth;
    m_iWidgetFixedHeight = a_iFixedHeight;

    this->UpdateBoundingRect();
}

void CTextWidget::SetMinimWidth(int a_iMinWidth)
{
    m_iWidgetMinimWidth = a_iMinWidth;

    this->UpdateBoundingRect();
}

void CTextWidget::SetMinimHeight(int a_iMinHeight)
{
    m_iWidgetMinimHeight = a_iMinHeight;

    this->UpdateBoundingRect();
}

void CTextWidget::SetWidgetOutline(bool a_blHasOutline)
{
    m_blHasOutline = a_blHasOutline;
    update(this->boundingRect());
}

void CTextWidget::SetWidgetUnderline(bool a_blHasUnderline)
{
    m_blHasUnderline = a_blHasUnderline;
    update(this->boundingRect());
}

void CTextWidget::SetText(QString a_qstrText)
{
    m_qstrText = a_qstrText;
    this->TextChanged();
}

QString CTextWidget::GetText()
{
    return m_qstrText;
}

void CTextWidget::SetTextColor(gColor a_EColor)
{
    m_CTextPen.setColor(a_EColor);
    update(this->boundingRect());
}

void CTextWidget::SetHorizontalExt(int a_iHoriExt)
{
    if(a_iHoriExt < 0)
    {
        a_iHoriExt = 0;
    }
    m_iTextWidthExt = a_iHoriExt;
    this->UpdateBoundingRect();
}

void CTextWidget::SetVerticalExt(int a_iVertExt)
{
    if(a_iVertExt < 0)
    {
        a_iVertExt = 0;
    }
    m_iTextHeightExt = a_iVertExt;
    this->UpdateBoundingRect();
}

void CTextWidget::TakeInput()
{
    m_pTextEditor->setPlainText(m_qstrText);
    QTextCursor l_CTextCursor = m_pTextEditor->textCursor();
    l_CTextCursor.movePosition(QTextCursor::End);
    m_pTextEditor->setTextCursor(l_CTextCursor);
    m_pTextEditor->setVisible(true);
    m_pTextEditor->setFocus();
}

void CTextWidget::ResetWidget()
{
    m_qstrText.clear();
    this->TextChanged();
}

int CTextWidget::WidgetWidth()
{
    int l_iWidth = m_iTextWidth + m_iTextWidthExt;
    if(m_iWidgetMinimWidth > 0) //has minimum width specification
    {
        if(l_iWidth < m_iWidgetMinimWidth)
        {
            l_iWidth = m_iWidgetMinimWidth;
        }
    }
    if(m_blSizeFixed) //has fixed size, this will violate all the operations above
    {
        l_iWidth = m_iWidgetFixedWidth;
    }
    return  l_iWidth;
}

int CTextWidget::WidgetHeight()
{
    int l_iHeight = m_iTextHeight + m_iTextHeightExt;
    if(m_iWidgetMinimHeight > 0) //has minimum height specification
    {
        if(l_iHeight < m_iWidgetMinimHeight)
        {
            l_iHeight = m_iWidgetMinimHeight;
        }
    }
    if(m_blSizeFixed) //has fixed size, this will violate all the operations above
    {
        l_iHeight = m_iWidgetFixedHeight;
    }
    return l_iHeight;
}

void CTextWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    if(m_blHasOutline)
    {
        painter->drawRoundedRect(this->boundingRect(), 5, 5);
    }
    if(m_blHasUnderline)
    {
        painter->save();

        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(QPen(QBrush(Qt::black), 2));
        painter->drawLine(0, this->boundingRect().height() - 3, this->boundingRect().width(),\
                          this->boundingRect().height() - 3);

        painter->restore();
    }
    QString l_qstrText;
    if(0 == this->GetTextType())
    {
        l_qstrText = m_qstrTip;
        painter->setFont(m_CTipFont);
        painter->setPen(m_CTipPen);
    }
    else
    {
        l_qstrText = m_qstrText;
        painter->setFont(m_CTextFont);
        painter->setPen(m_CTextPen);
    }
    painter->drawText(this->boundingRect(), Qt::AlignCenter, l_qstrText);

    painter->restore();
}

void CTextWidget::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_blEditable)
    {
        CGraphicsWidget::mousePressEvent(event);
    }
    else
    {
        event->ignore();
    }
}

void CTextWidget::LeftButtonClicked(QPointF a_CMousePos)
{
    Q_UNUSED(a_CMousePos)

    if(m_blEditable)
    {
        this->TakeInput();
    }
}

void CTextWidget::SLOT_EditFinishProc()
{
    m_pTextEditor->setVisible(false);
    m_qstrText = m_pTextEditor->document()->toPlainText();
    this->TextChanged();
    emit this->SIGNAL_EditFinished();
}

int CTextWidget::GetTextType()
{
    if(!m_qstrText.isEmpty() && !m_qstrText.isNull())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void CTextWidget::TextChanged()
{
    QString l_qstrText;
    QFont l_CFont;
    if(0 == this->GetTextType())
    {
        l_qstrText = m_qstrTip;
        l_CFont = m_CTipFont;
    }
    else
    {
        l_qstrText = m_qstrText;
        l_CFont = m_CTextFont;
    }

    QFontMetrics l_CFontMetrics(l_CFont);
    QRectF l_CBR = l_CFontMetrics.boundingRect(l_qstrText);

    m_iTextWidth = l_CBR.width();
    m_iTextHeight = l_CBR.height();

    this->UpdateBoundingRect();
}
