#ifndef CSVGWIDGET_H
#define CSVGWIDGET_H

#include "cgraphicswidget.h"

#include <QtSvg>
#include <QSvgRenderer>
#include <QString>

class CSvgWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CSvgWidget(QString a_qstrSvgFile, int a_iWidgetWidth, int a_iWidgetHeight,\
               CGraphicsWidget* a_pParent);
    QString GetFileName()\
    {return m_qstrFileName;}

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    int m_iWidth, m_iHeight;
    QSvgRenderer* m_pSvgRender;
    QString m_qstrFileName;
};

#endif // CSVGWIDGET_H
