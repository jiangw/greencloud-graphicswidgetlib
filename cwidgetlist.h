#ifndef CWIDGETLIST_H
#define CWIDGETLIST_H

#include "cgraphicswidget.h"
#include "ctextwidget.h"

#include <QGraphicsScene>

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
    void ResetWidget();
    void ClearList();
    void SetListOrientation(EListOrientation a_EOrientation);
    void SetHeaderSize(int a_iWidth, int a_iHeight);
    void SetHeaderWidget(CGraphicsWidget* a_pHeaderWidget);
    CGraphicsWidget* GetHeaderWidget();
    CWidgetNode* GetWidgetList();
    void PropagateMouseEventToChildren(bool a_blFlag);
    void AddWidget(CGraphicsWidget* a_pNewWidget);
    void SetNewWidgetPos(CGraphicsWidget* a_pPrev, CGraphicsWidget* a_pNew);
    void RemoveWidget(CGraphicsWidget* a_pDelWidget);
    void SetWidgetOutline(bool a_blHasOutline);
    bool Collapse();
    void SetCollapse(bool a_blCollapse);

    //override from CGraphicsWidget
    int WidgetWidth();
    int WidgetHeight();
    QString WidgetClassName();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void SLOT_AddWidget(CGraphicsWidget* a_pNewWidget);
    void SLOT_RemoveWidget(CGraphicsWidget* a_pDelWidget);
    void SLOT_WidgetSizeChangeProc();

signals:
    void SIGNAL_RemoveWidgetFromScene(CGraphicsWidget* a_pDelWidget);

private:
    void RemoveWidgetFromScene(CGraphicsWidget* a_pDelWidget);

    EListOrientation m_EOrient;
    int m_iWidgetSpacingX, m_iWidgetSpacingY; //space between each two widgets along X and Y dims
    int m_iHeaderWidth, m_iHeaderHeight;

    CWidgetNode* m_pWidgetListHead;
    CGraphicsWidget* m_pHeaderWidget;
    bool m_blMouseEventPropFlag; //true(default): propagate to children. false: do not propagate

    bool m_blHasOutline;
    bool m_blCollapse;
};

#endif // CWIDGETLIST_H
