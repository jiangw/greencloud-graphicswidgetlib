#ifndef CWIDGETLIST_H
#define CWIDGETLIST_H

#include "cgraphicswidget.h"

class CWidgetNode
{
public:
    CGraphicsWidget* m_pWidget;
    CWidgetNode* m_pNext;
};

class CWidgetList : public CGraphicsWidget
{
    Q_OBJECT

public:
    enum EListOrientation{HORIZONTAL, VERTICAL};

    CWidgetList(CGraphicsWidget* a_pParent);
    ~CWidgetList();
    void ClearList();
    void SetListOrientation(EListOrientation a_EOrientation);
    void SetListTitle(QString a_qstrTitle);
    void SetHeaderSize(int a_iWidth, int a_iHeight);
    CWidgetNode* GetWidgetList();

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    QString WidgetClassName();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void SLOT_AddWidget(CGraphicsWidget* a_pNewWidget);
    void SLOT_RemoveWidget(CGraphicsWidget* a_pDelWidget);

signals:
    void SIGNAL_RemoveWidgetFromScene(CGraphicsWidget* a_pDelWidget);

private:
    EListOrientation m_EOrient;
    int m_iWidgetSpacingX, m_iWidgetSpacingY; //space between each two widgets along X and Y dims
    int m_iHeaderWidth, m_iHeaderHeight;

    CWidgetNode* m_pWidgetListHead;
    QString m_qstrTitle;
};

#endif // CWIDGETLIST_H
