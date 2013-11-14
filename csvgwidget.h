#ifndef CSVGWIDGET_H
#define CSVGWIDGET_H

#include "cgraphicswidget.h"

#include <QtSvg>
#include <QSvgRenderer>

class CSvgWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CSvgWidget(QString a_qstrSvgFile, int a_iWidgetWidth, int a_iWidgetHeight,\
               CGraphicsWidget* a_pParent);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int m_iWidth, m_iHeight;
    QSvgRenderer* m_pSvgRender;
};

#endif // CSVGWIDGET_H
