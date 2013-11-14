#ifndef CBUTTONWIDGET_H
#define CBUTTONWIDGET_H

#include "cgraphicswidget.h"

#include <QFont>
#include <QFontMetrics>

class CButtonWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    static const int s_iButtonMinWidth;
    static const int s_iButtonMinHeight;

    CButtonWidget(QString a_qstrText, CGraphicsWidget* a_pParent);
    void SetText(QString a_qstrText);
    void SetTextFontSize(int a_iSize);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    //override from CGraphicsWidget
    void LeftButtonClicked(QPointF a_CMousePos);

signals:
    void SIGNAL_ButtonTriggered();

private:
    int m_iStrWidth, m_iStrHeight;
    int m_iStrWidthExt; //extra size extended from the bounding rect of m_qstrText
    int m_iStrHeightExt;
    QString m_qstrText;
    QFont m_CButtonFont;
    int m_iTextFontSize;
};

#endif // CBUTTONWIDGET_H
