#include "cwidgetlist.h"

CWidgetList::CWidgetList(CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_EOrient = VERTICAL;
    m_iWidgetSpacingX = 10;
    m_iWidgetSpacingY = 10;
    m_iHeaderWidth = 200;
    m_iHeaderHeight = 25;
    m_pWidgetListHead = NULL;
    m_qstrTitle = "Widgets List";

    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}
\
CWidgetList::~CWidgetList()
{
    this->ClearList();
}

void CWidgetList::ClearList()
{
    CWidgetNode* l_pNextNode;
    while(m_pWidgetListHead)
    {
        l_pNextNode = m_pWidgetListHead->m_pNext;
        delete m_pWidgetListHead;
        m_pWidgetListHead = l_pNextNode;
    }
}

void CWidgetList::SetListOrientation(EListOrientation a_EOrientation)
{
    if(m_EOrient != a_EOrientation)
    {
        m_EOrient = a_EOrientation;

        if(NULL != m_pWidgetListHead)
        {
            CWidgetNode* l_pPrevNode = m_pWidgetListHead;
            CWidgetNode* l_pCurrNode = m_pWidgetListHead->m_pNext;
            if(VERTICAL == m_EOrient)
            {
                while(l_pCurrNode)
                {
                    l_pCurrNode->m_pWidget->setPos(l_pPrevNode->m_pWidget->pos().x(),\
                                                   l_pPrevNode->m_pWidget->pos().y()\
                                                   + l_pPrevNode->m_pWidget->boundingRect().height()\
                                                   + m_iWidgetSpacingY);

                    l_pPrevNode = l_pCurrNode;
                    l_pCurrNode = l_pCurrNode->m_pNext;
                }
            }
            else
            {
                while(l_pCurrNode)
                {
                    l_pCurrNode->m_pWidget->setPos(l_pPrevNode->m_pWidget->pos().x()\
                                                   + l_pPrevNode->m_pWidget->boundingRect().width()\
                                                   + m_iWidgetSpacingX,\
                                                   l_pPrevNode->m_pWidget->pos().y());

                    l_pPrevNode = l_pCurrNode;
                    l_pCurrNode = l_pCurrNode->m_pNext;
                }
            }

            prepareGeometryChange();
            this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
        }
    }
}

void CWidgetList::SetListTitle(QString a_qstrTitle)
{
    m_qstrTitle = a_qstrTitle;
    update(0, 0, m_iHeaderWidth, m_iHeaderHeight);
}

void CWidgetList::SetHeaderSize(int a_iWidth, int a_iHeight)
{
    m_iHeaderWidth = a_iWidth;
    m_iHeaderHeight = a_iHeight;

    prepareGeometryChange();
    this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

CWidgetNode* CWidgetList::GetWidgetList()
{
    return m_pWidgetListHead;
}

int CWidgetList::WidgetWidth()
{
    int l_iWidth = 0;
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    while(l_pWidgetNode)
    {
        CGraphicsWidget* l_pWidget = l_pWidgetNode->m_pWidget;
        if(HORIZONTAL == m_EOrient)
        {
            l_iWidth += l_pWidget->boundingRect().width() + m_iWidgetSpacingX;
        }
        else
        {
            if(l_pWidget->boundingRect().width() > l_iWidth)
            {
                l_iWidth = l_pWidget->boundingRect().width();
            }
        }
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    if(l_iWidth < m_iHeaderWidth)
    {
        l_iWidth = m_iHeaderWidth;
    }

    return l_iWidth;
}

int CWidgetList::WidgetHeight()
{
    int l_iHeight = 0;
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    while(l_pWidgetNode)
    {
        CGraphicsWidget* l_pWidget = l_pWidgetNode->m_pWidget;
        if(HORIZONTAL == m_EOrient)
        {
            if(l_pWidget->boundingRect().height() > l_iHeight)
            {
                l_iHeight = l_pWidget->boundingRect().height();
            }
        }
        else
        {
            l_iHeight += l_pWidget->boundingRect().height() + m_iWidgetSpacingY;
        }
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    return l_iHeight + m_iHeaderHeight;
}

QString CWidgetList::WidgetClassName()
{
    return "CWidgetList";
}

void CWidgetList::paint(QPainter *painter,\
                                     const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->drawText(5, 0, m_iHeaderWidth, m_iHeaderHeight, Qt::AlignLeft | Qt::AlignBottom,\
                      m_qstrTitle);
    painter->drawLine(QPointF(0, m_iHeaderHeight), QPointF(m_iHeaderWidth, m_iHeaderHeight));
    painter->drawRect(this->boundingRect());
}

void CWidgetList::SLOT_AddWidget(CGraphicsWidget* a_pNewWidget)
{
    if(NULL != a_pNewWidget)
    {
        a_pNewWidget->setParent(this);
        CWidgetNode* l_pNewNode = new CWidgetNode();
        l_pNewNode->m_pWidget = a_pNewWidget;
        l_pNewNode->m_pNext = NULL;

        CGraphicsWidget* l_pNewWidget = a_pNewWidget;

        if(NULL == m_pWidgetListHead)
        {
            m_pWidgetListHead = l_pNewNode;
            //set widget position
            l_pNewWidget->setPos(m_iWidgetSpacingX, m_iHeaderHeight + m_iWidgetSpacingY);
        }
        else
        {
            CWidgetNode* l_pTail = m_pWidgetListHead;
            while(l_pTail->m_pNext)
            {
                l_pTail = l_pTail->m_pNext;
            }
            l_pTail->m_pNext = l_pNewNode;

            //set widget position
            CGraphicsWidget* l_pPrevWidget = l_pTail->m_pWidget;
            if(HORIZONTAL == m_EOrient)
            {
                l_pNewWidget->setPos(l_pPrevWidget->pos().x()\
                                     + l_pPrevWidget->boundingRect().width()\
                                     + m_iWidgetSpacingX,\
                                     l_pPrevWidget->pos().y());
            }
            else
            {
                l_pNewWidget->setPos(l_pPrevWidget->pos().x(),\
                                     l_pPrevWidget->pos().y()\
                                     + l_pPrevWidget->boundingRect().height()\
                                     + m_iWidgetSpacingY);
            }
        }

        prepareGeometryChange();
        this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    }
}

void CWidgetList::SLOT_RemoveWidget(CGraphicsWidget* a_pDelWidget)
{
    CWidgetNode* l_pDelNode = NULL;
    CWidgetNode* l_pDelNodePrev = NULL;
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    while(l_pWidgetNode)
    {
        if(l_pWidgetNode->m_pWidget == a_pDelWidget)
        {
            l_pDelNode = l_pWidgetNode;
            break;
        }
        l_pDelNodePrev = l_pWidgetNode;
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    if(NULL != l_pDelNode)
    {
        CGraphicsWidget* l_pPrevWidget;
        if(l_pDelNode == m_pWidgetListHead) //first node
        {
            l_pDelNodePrev = m_pWidgetListHead->m_pNext;
            if(NULL != l_pDelNodePrev)
            {
                l_pPrevWidget = l_pDelNodePrev->m_pWidget;
                l_pPrevWidget->setPos(m_iWidgetSpacingX, m_iHeaderHeight + m_iWidgetSpacingY);
                l_pWidgetNode = l_pDelNodePrev->m_pNext;
            }
            else
            {
                l_pWidgetNode = NULL;
            }
            m_pWidgetListHead = l_pDelNodePrev; //the second node become the list head
        }
        else
        {
            l_pPrevWidget = l_pDelNodePrev->m_pWidget;
            l_pWidgetNode = l_pDelNode->m_pNext;
            //the previous node points to the next node of the deleted node
            l_pDelNodePrev->m_pNext = l_pWidgetNode;
        }
        while(l_pWidgetNode)
        {
            CGraphicsWidget* l_pCurrWidget = l_pWidgetNode->m_pWidget;
            if(HORIZONTAL == m_EOrient)
            {
                l_pCurrWidget->setPos(l_pPrevWidget->pos().x()\
                                      + l_pPrevWidget->boundingRect().width()\
                                      + m_iWidgetSpacingX,\
                                      l_pPrevWidget->pos().y());
            }
            else
            {
                l_pCurrWidget->setPos(l_pPrevWidget->pos().x(),\
                                      l_pPrevWidget->pos().y()\
                                      + l_pPrevWidget->boundingRect().height()\
                                      + m_iWidgetSpacingY);
            }
            l_pWidgetNode = l_pWidgetNode->m_pNext;
        }

        delete l_pDelNode;
        emit SIGNAL_RemoveWidgetFromScene(a_pDelWidget);

        prepareGeometryChange();
        this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    }
}