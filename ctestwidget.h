#ifndef CTESTWIDGET_H
#define CTESTWIDGET_H

#include "cgraphicswidget.h"

#include <QString>

class CTestWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CTestWidget(int a_iWidth, int a_iHeight, CGraphicsWidget* a_pParent);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void SLOT_LeftButtonClickProc();

private:
    QString m_qstrMsg;
    int m_iWidth, m_iHeight;
};

#endif // CTESTWIDGET_H
