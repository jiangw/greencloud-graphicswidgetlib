#ifndef CCHECKWIDGET_H
#define CCHECKWIDGET_H

#include "cgraphicswidget.h"

class CCheckWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CCheckWidget(CGraphicsWidget* a_pParent);

    void SetChecked(bool a_blIsChecked);
    bool IsChecked()\
    {return m_blChecked;}
    void BoundingWithWidget(CGraphicsWidget* a_pBoundingWidget);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    //override from CGraphicsWidget
    void LeftButtonClicked(QPointF a_CMousePos);

signals:
    void SIGNAL_Checked();

private:
    int m_iWidgetSize;
    bool m_blChecked;
    CGraphicsWidget* m_pBoundingWidget;
};

#endif // CCHECKWIDGET_H
