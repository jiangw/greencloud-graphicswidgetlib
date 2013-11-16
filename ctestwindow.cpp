#include "ctestwindow.h"

CTestWindow::CTestWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 300, 300);

    m_pScene = new QGraphicsScene(this);
    m_pScene->setSceneRect(0, 0, 200, 200);
    m_pScene->setBackgroundBrush(Qt::gray);
    m_pView = new QGraphicsView(this);
    m_pView->setScene(m_pScene);

    m_pWidgetList = new CWidgetList(NULL);
    m_pWidgetList->setPos(5, 5);
    m_pScene->addItem(m_pWidgetList);

    CTextWidget* l_pNewTextWidget1 = new CTextWidget(true, NULL);
    l_pNewTextWidget1->SetText("Text Widget 1");
    m_pScene->addItem(l_pNewTextWidget1);
    m_pWidgetList->SLOT_AddWidget(l_pNewTextWidget1);

    CTextWidget* l_pNewTextWidget2 = new CTextWidget(true, NULL);
    l_pNewTextWidget2->SetText("Text Widget 2");
    l_pNewTextWidget2->SetWidgetOutline(false);
    m_pScene->addItem(l_pNewTextWidget2);
    m_pWidgetList->SLOT_AddWidget(l_pNewTextWidget2);

    CTextWidget* l_pNewTextWidget3 = new CTextWidget(true, NULL);
    l_pNewTextWidget3->SetText("Text Widget 3");
    m_pScene->addItem(l_pNewTextWidget3);
    m_pWidgetList->SLOT_AddWidget(l_pNewTextWidget3);

//    m_pWidgetList->SLOT_RemoveWidget(l_pNewTextWidget3);
//    m_pWidgetList->SetListOrientation(CWidgetList::HORIZONTAL);
//    m_pWidgetList->SetListOrientation(CWidgetList::VERTICAL);

    this->setCentralWidget(m_pView);
}

CTestWindow::~CTestWindow()
{
    
}

void CTestWindow::SLOT_ButtonTriggeredProc()
{
    m_pButtonWidget->SetText("OK");
}
