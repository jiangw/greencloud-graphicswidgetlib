#include "ctestwindow.h"

CTestWindow::CTestWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 300, 300);

    m_pScene = new QGraphicsScene(this);
    m_pScene->setSceneRect(0, 0, 200, 200);
    m_pView = new QGraphicsView(this);
    m_pView->setScene(m_pScene);

    m_pTestWidget = new CTestWidget(200, 50, NULL);
    m_pTestWidget->SetWidgetName("A");
    m_pScene->addItem(m_pTestWidget);

    m_pTestWidget1 = new CTestWidget(200, 50, NULL);
    m_pTestWidget1->setPos(0, 100);
    m_pTestWidget1->SetWidgetName("B");
    m_pScene->addItem(m_pTestWidget1);

    connect(m_pTestWidget, SIGNAL(SIGNAL_MouseDragRelease(QPointF, CGraphicsWidget*)), \
            m_pTestWidget1, SLOT(SLOT_MouseDragDropProc(QPointF, CGraphicsWidget*)));

//    m_pCheckWidget = new CCheckWidget(NULL);
//    m_pCheckWidget->setPos(0, 60);
//    m_pScene->addItem(m_pCheckWidget);

    m_pButtonWidget = new CButtonWidget("Button triggered", NULL);
    m_pButtonWidget->setPos(0, 60);
    m_pScene->addItem(m_pButtonWidget);

    connect(m_pButtonWidget, SIGNAL(SIGNAL_ButtonTriggered()),\
            this, SLOT(SLOT_ButtonTriggeredProc()));

    this->setCentralWidget(m_pView);
}

CTestWindow::~CTestWindow()
{
    
}

void CTestWindow::SLOT_ButtonTriggeredProc()
{
    m_pButtonWidget->SetText("OK");
}
