#include "cwidgetlist.h"

CWidgetList::CWidgetList(CGraphicsWidget *a_pParent)
    :CGraphicsWidget(a_pParent)
{
    m_EOrient = VERTICAL;
    m_iWidgetSpacingX = 10;
    m_iWidgetSpacingY = 10;
    m_pWidgetListHead = NULL;
    m_iWidgetCounter = 0;
    m_blMouseEventPropFlag = true;
    m_blHasOutline = true;
    m_blCollapse = false;
    m_iPageLength = 5;
    m_iPageCurrPos = 1;

    CTextWidget* l_pLabel = new CTextWidget(false, this);
    l_pLabel->SetWidgetOutline(false);
    l_pLabel->SetText("Widgets List");
    l_pLabel->SetFont(QFont("Courier New", 12));
    l_pLabel->setPos(0, 0);
    m_iHeaderWidth = l_pLabel->boundingRect().width() * 1.5;
    m_iHeaderHeight = l_pLabel->boundingRect().height();
    m_pHeaderWidget = l_pLabel;

    this->InitBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}
\
CWidgetList::~CWidgetList()
{
    this->ClearList();
}

void CWidgetList::ResetWidget()
{
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    while(l_pWidgetNode)
    {
        this->SLOT_RemoveWidget(l_pWidgetNode->m_pWidget);
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    this->ClearList();

    this->UpdateBoundingRect();
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
    m_iWidgetCounter = 0;
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

            this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
        }
    }
}

void CWidgetList::SetHeaderWidget(CGraphicsWidget *a_pHeaderWidget)
{
    //remove old header widget
    this->RemoveWidgetFromScene(m_pHeaderWidget);

    //set new header widget
    m_pHeaderWidget = a_pHeaderWidget;
    m_pHeaderWidget->setParentItem(this);
    m_pHeaderWidget->setPos(0, 0);
    m_iHeaderWidth = m_pHeaderWidget->boundingRect().width() * 1.5;
    m_iHeaderHeight = m_pHeaderWidget->boundingRect().height();

    //update
    this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    update(this->boundingRect());
}

CGraphicsWidget* CWidgetList::GetHeaderWidget()
{
    return m_pHeaderWidget;
}

void CWidgetList::SetHeaderSize(int a_iWidth, int a_iHeight)
{
    m_iHeaderWidth = a_iWidth;
    m_iHeaderHeight = a_iHeight;

    this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
}

CWidgetNode* CWidgetList::GetWidgetList()
{
    return m_pWidgetListHead;
}

int CWidgetList::IndexOf(CGraphicsWidget *a_pWidget)
{
    int l_iWidgetIdx = -1;
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    int i = 0;
    while(l_pWidgetNode)
    {
        if(l_pWidgetNode->m_pWidget == a_pWidget)
        {
            l_iWidgetIdx = i;
            break;
        }
        i++;
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    return l_iWidgetIdx;
}

void CWidgetList::PropagateMouseEventToChildren(bool a_blFlag)
{
    m_blMouseEventPropFlag = a_blFlag;
}

int CWidgetList::WidgetWidth()
{
    int l_iWidth = 0;
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    while(l_pWidgetNode)
    {
        CGraphicsWidget* l_pWidget = l_pWidgetNode->m_pWidget;
        if(l_pWidget->isVisible())
        {
            if(HORIZONTAL == m_EOrient)
            {
                l_iWidth += l_pWidget->boundingRect().width() + m_iWidgetSpacingX;
            }
            else
            {
                if(l_pWidget->boundingRect().width() > l_iWidth)
                {
                    l_iWidth = l_pWidget->boundingRect().width() + m_iWidgetSpacingX;
                }
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
        if(l_pWidget->isVisible())
        {
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

    painter->drawLine(QPointF(0, m_iHeaderHeight),\
                      QPointF(this->boundingRect().width(), m_iHeaderHeight));
    if(m_blHasOutline)//draw outline
    {
        painter->drawRect(0, m_iHeaderHeight, this->boundingRect().width(),\
                          this->boundingRect().height() - m_iHeaderHeight);
    }
    if(m_iWidgetCounter > m_iPageLength)//draw scrollbar
    {
        QRectF l_CRectBack, l_CRectFront;
        if(HORIZONTAL == m_EOrient)
        {
            l_CRectBack.setRect(m_iWidgetSpacingX, m_iHeaderHeight,\
                            this->boundingRect().width() - m_iWidgetSpacingX, 8);
            l_CRectFront.setX((m_iPageCurrPos - 1) * l_CRectBack.width() / m_iWidgetCounter\
                              + l_CRectBack.x());
            l_CRectFront.setY(l_CRectBack.y() + 1);
            l_CRectFront.setWidth(l_CRectBack.width() / m_iWidgetCounter);
            l_CRectFront.setHeight(l_CRectBack.height() - 3);

            painter->drawLine(l_CRectBack.topLeft().x(), l_CRectBack.topLeft().y() + 3,\
                              l_CRectBack.topRight().x(), l_CRectBack.topLeft().y() + 3);
        }
        else
        {
            l_CRectBack.setRect(0, m_iHeaderHeight + m_iWidgetSpacingY,\
                            8,\
                            this->boundingRect().height() - m_iHeaderHeight - m_iWidgetSpacingY);
            l_CRectFront.setX(l_CRectBack.x() + 1);
            l_CRectFront.setY((m_iPageCurrPos - 1) * l_CRectBack.height() / m_iWidgetCounter\
                              + l_CRectBack.y());
            l_CRectFront.setWidth(l_CRectBack.width() - 3);
            l_CRectFront.setHeight(l_CRectBack.height() / m_iWidgetCounter);

            painter->drawLine(l_CRectBack.topLeft().x() + 3, l_CRectBack.topLeft().y(),\
                              l_CRectBack.bottomLeft().x() + 3, l_CRectBack.bottomLeft().y());
        }
        painter->fillRect(l_CRectFront, Qt::black);
    }
}

void CWidgetList::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(m_blMouseEventPropFlag)
    {
        event->ignore();
    }
    else
    {
        CGraphicsWidget::mousePressEvent(event);
    }
}

void CWidgetList::WheelScroll(int a_iSteps)
{
    if(a_iSteps >= 0) //scroll up or left
    {
        m_iPageCurrPos -= a_iSteps;
    }
    else //scroll down or right
    {
        m_iPageCurrPos += abs(a_iSteps);
    }
    this->SetPagePos(m_iPageCurrPos);
}

void CWidgetList::AddWidget(CGraphicsWidget* a_pNewWidget)
{
    if(NULL != a_pNewWidget)
    {
        m_iWidgetCounter++;

        a_pNewWidget->setFlag(QGraphicsItem::ItemStacksBehindParent);
        a_pNewWidget->setParentItem(this);
        CWidgetNode* l_pNewNode = new CWidgetNode();
        l_pNewNode->m_pWidget = a_pNewWidget;
        l_pNewNode->m_pNext = NULL;
        connect(a_pNewWidget, SIGNAL(SIGNAL_RemoveWidget(CGraphicsWidget*)),\
                this, SLOT(SLOT_RemoveWidget(CGraphicsWidget*)));
        connect(a_pNewWidget, SIGNAL(SIGNAL_WidgetSizeChanged()),\
                this, SLOT(SLOT_WidgetSizeChangeProc()));

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
            this->SetNewWidgetPos(l_pPrevWidget, l_pNewWidget);
        }

        m_iPageCurrPos = m_iWidgetCounter;
        this->PageUpdate();
    }
}

void CWidgetList::SLOT_AddWidget(CGraphicsWidget *a_pNewWidget)
{
    this->AddWidget(a_pNewWidget);
}

void CWidgetList::SetNewWidgetPos(CGraphicsWidget *a_pPrev, CGraphicsWidget *a_pNew)
{
    if(HORIZONTAL == m_EOrient)
    {
        a_pNew->setPos(a_pPrev->pos().x()\
                             + a_pPrev->boundingRect().width()\
                             + m_iWidgetSpacingX,\
                             a_pPrev->pos().y());
    }
    else
    {
        a_pNew->setPos(a_pPrev->pos().x(),\
                             a_pPrev->pos().y()\
                             + a_pPrev->boundingRect().height()\
                             + m_iWidgetSpacingY);
    }
}

void CWidgetList::RemoveWidget(CGraphicsWidget* a_pDelWidget)
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
        m_iWidgetCounter--;
        CGraphicsWidget* l_pPrevWidget = NULL;
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
            l_pPrevWidget = l_pCurrWidget;
            l_pWidgetNode = l_pWidgetNode->m_pNext;
        }

        delete l_pDelNode;
        this->RemoveWidgetFromScene(a_pDelWidget);

        this->UpdateBoundingRect(this->WidgetWidth(), this->WidgetHeight());
    }
}

void CWidgetList::SetWidgetOutline(bool a_blHasOutline)
{
    m_blHasOutline = a_blHasOutline;
    update(this->boundingRect());
}

bool CWidgetList::Collapse()
{
    return m_blCollapse;
}

void CWidgetList::SetCollapse(bool a_blCollapse)
{
    m_blCollapse = a_blCollapse;
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    while(l_pWidgetNode)
    {
        l_pWidgetNode->m_pWidget->setVisible(!m_blCollapse);
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    this->UpdateBoundingRect();
}

void CWidgetList::SetPageLength(int a_iPageLen)
{
    if(a_iPageLen < 1)
    {
        a_iPageLen = 1;
    }
    m_iPageLength = a_iPageLen;

    this->PageUpdate();
}

void CWidgetList::SetPagePos(int a_iPagePos)
{
    if(a_iPagePos < 1)
    {
        a_iPagePos = 1;
    }
    if(a_iPagePos > m_iWidgetCounter)
    {
        a_iPagePos = m_iWidgetCounter;
    }

    m_iPageCurrPos = a_iPagePos;

    this->PageUpdate();
}

void CWidgetList::SLOT_RemoveWidget(CGraphicsWidget *a_pDelWidget)
{
    this->RemoveWidget(a_pDelWidget);
}

void CWidgetList::SLOT_WidgetSizeChangeProc()
{
    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    CWidgetNode* l_pWidgetNodePrev = NULL;
    while(l_pWidgetNode)
    {
        if(l_pWidgetNode != m_pWidgetListHead)
        {
            CGraphicsWidget* l_pPrev = l_pWidgetNodePrev->m_pWidget;
            CGraphicsWidget* l_pCurr = l_pWidgetNode->m_pWidget;
            this->SetNewWidgetPos(l_pPrev, l_pCurr);
        }

        l_pWidgetNodePrev = l_pWidgetNode;
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }
    this->UpdateBoundingRect();
}

void CWidgetList::RemoveWidgetFromScene(CGraphicsWidget *a_pDelWidget)
{
    if(NULL == this->scene())
    {
        a_pDelWidget->setVisible(false);
        emit this->SIGNAL_RemoveWidgetFromScene(a_pDelWidget);
    }
    else
    {
        this->scene()->removeItem(a_pDelWidget);
    }
}

void CWidgetList::PageUpdate()
{
    int l_iStartX = m_iWidgetSpacingX;
    int l_iStartY = m_iHeaderHeight + m_iWidgetSpacingY;

    CWidgetNode* l_pWidgetNode = m_pWidgetListHead;
    CWidgetNode* l_pPrevNode = NULL;
    int l_iPos = 1;
    int l_iFirstShowPos = -1;
    bool l_blShowWidget;
    while(l_pWidgetNode)
    {
        /*
        if(l_iPos < m_iPageCurrPos)
        {
            if(m_iWidgetCounter - l_iPos + 1 <= m_iPageLength)
            {
                l_blShowWidget = true;
            }
            else
            {
                l_blShowWidget = false;
            }
        }
        else if(l_iPos >= m_iPageCurrPos + m_iPageLength)
        {
            l_blShowWidget = false;
        }
        else
        {
            l_blShowWidget = true;
        }*/
        if(l_iPos <= m_iPageCurrPos)
        {
            if(m_iPageCurrPos - l_iPos + 1 <= m_iPageLength)
            {
                l_blShowWidget = true;
                if(-1 == l_iFirstShowPos)
                {
                    l_iFirstShowPos = l_iPos;
                }
            }
            else
            {
                l_blShowWidget = false;
            }
        }
        else
        {
            if(l_iPos - l_iFirstShowPos + 1 <= m_iPageLength)
            {
                l_blShowWidget = true;
            }
            else
            {
                l_blShowWidget = false;
            }
        }

        if(l_blShowWidget)
        {
            l_pWidgetNode->m_pWidget->setVisible(true);
            if(NULL == l_pPrevNode)
            {
                l_pWidgetNode->m_pWidget->setPos(l_iStartX, l_iStartY);
            }
            else
            {
                this->SetNewWidgetPos(l_pPrevNode->m_pWidget, l_pWidgetNode->m_pWidget);
            }
            l_pPrevNode = l_pWidgetNode;
        }
        else
        {
            l_pWidgetNode->m_pWidget->setVisible(false);
        }

        //highlight widget
        if(l_iPos == m_iPageCurrPos)
        {
            l_pWidgetNode->m_pWidget->Hightlight(true);
        }
        else
        {
            l_pWidgetNode->m_pWidget->Hightlight(false);
        }

        l_iPos++;
        l_pWidgetNode = l_pWidgetNode->m_pNext;
    }

    this->UpdateBoundingRect();
}
