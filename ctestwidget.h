#ifndef CTESTWIDGET_H
#define CTESTWIDGET_H

#include "cgraphicswidget.h"

#include <QString>
#include <QBrush>
#include <QPixmap>
#include <QtSvg>
#include <QSvgRenderer>
#include <QPainter>

class CTestWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CTestWidget(int a_iWidth, int a_iHeight, CGraphicsWidget* a_pParent);
    void SetWidgetName(QString a_qstrName);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    QString WidgetClassName()\
    {return "CTestWidget";}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void LeftButtonClicked(QPointF a_CMousePos);
    void MouseDragMove(QPointF a_CMousePos);
    void MouseDragRelease(QPointF a_CMousePos);

public slots:
    void SLOT_MouseDragDropProc(QPointF a_CMouseScenePos, CGraphicsWidget* a_pWhoAmI);

private:
    QString m_qstrMsg;
    QString m_qstrWidgetName;
    int m_iWidth, m_iHeight;
    QBrush m_CBrush;
    QSvgRenderer* m_pSvgRender;
};

#endif // CTESTWIDGET_H
