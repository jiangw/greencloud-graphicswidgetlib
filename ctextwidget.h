#ifndef CTEXTWIDGET_H
#define CTEXTWIDGET_H

#include "cgraphicswidget.h"
#include "ctexteditor.h"

#include <QFont>
#include <QFontMetrics>
#include <QTextDocument>
#include <QTextCursor>

class CTextWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CTextWidget(bool a_blEditable, CGraphicsWidget* a_pParent);
    void SetEditable(bool a_blEditable);
    void SetFontSize(int a_iFontSize);
    void SetFont(QFont a_CFont);
    void SetInputTip(QString a_qstrTip);
    void SetFixedSize(int a_iFixedWidth, int a_iFixedHeight);
    void SetMinimWidth(int a_iMinWidth);
    void SetMinimHeight(int a_iMinHeight);
    void SetWidgetOutline(bool a_blHasOutline);
    void SetWidgetUnderline(bool a_blHasUnderline);
    void SetText(QString a_qstrText);
    QString GetText();
    void SetTextColor(CGraphicsWidget::gColor a_EColor);
    void SetHorizontalExt(int a_iHoriExt);
    void SetVerticalExt(int a_iVertExt);
    void TakeInput();

    //override from CGraphicsWidget
    void ResetWidget();
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    //override from CGraphicsWidget
    void LeftButtonClicked(QPointF a_CMousePos);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void SLOT_EditFinishProc();

signals:
    void SIGNAL_EditFinished();

private:
    int GetTextType(); //get text type(1:text 0:tip)

    void TextChanged(); //update bounding rect when text changed

    bool m_blSizeFixed;
    bool m_blHasOutline;
    bool m_blHasUnderline;
    int m_iTextWidth, m_iTextHeight, m_iTextWidthExt, m_iTextHeightExt;
    int m_iWidgetFixedWidth, m_iWidgetFixedHeight;
    int m_iWidgetMinimWidth, m_iWidgetMinimHeight;

    CTextEditor* m_pTextEditor;
    bool m_blEditable;
    QString m_qstrTip, m_qstrText;
    int m_iFontSize;
    QFont m_CTipFont;
    QPen m_CTipPen;
    QFont m_CTextFont;
    QPen m_CTextPen;
};

#endif // CTEXTWIDGET_H
