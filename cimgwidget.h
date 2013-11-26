#ifndef CIMGWIDGET_H
#define CIMGWIDGET_H

#include "cgraphicswidget.h"

#include <QPixmap>
#include <QBrush>

class CImgWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    CImgWidget(int a_iWidth, int a_iHeight, CGraphicsWidget *a_pParent);
    CImgWidget(QString a_qstrImgFileName, int a_iWidth, int a_iHeight,\
               CGraphicsWidget* a_pParent);
    void SetImg(QString a_qstrImgFileName);
    void ClearImg();
    QString GetFileName()\
    {return m_qstrFileName;}

    //override from CGraphicsWidget
    int WidgetWidth()\
    {return m_iWidth;}
    int WidgetHeight()\
    {return m_iHeight;}
    QString WidgetClassName()\
    {return "CImgWidget";}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void Hightlight(bool a_blHightlight);

protected:
    //override from CGraphicsWidget
    void MouseDragMove(QPointF a_CMousePos);
    void MouseDragRelease(QPointF a_CMousePos);

private:
    int m_iWidth, m_iHeight;
    QBrush m_CBackgroundBrush;
    QString m_qstrFileName;
    bool m_blHightlight;
};

#endif // CIMGWIDGET_H
