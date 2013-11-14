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

    CSvgWidget* l_pSvgWidget = new CSvgWidget("/home/jiang/GreenClouD/icon_edit.svg",\
                                              100, 100, NULL);
    m_pScene->addItem(l_pSvgWidget);

    this->setCentralWidget(m_pView);
}

CTestWindow::~CTestWindow()
{
    
}

void CTestWindow::SLOT_ButtonTriggeredProc()
{
    m_pButtonWidget->SetText("OK");
}
