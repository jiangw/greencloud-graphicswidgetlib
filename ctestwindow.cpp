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

//    m_pImgWidget = new CImgWidget("/home/jiang/Projects/Qt/GreenClouD/test.jpg",\
//                                  150, 150, NULL);
    m_pImgWidget = new CImgWidget(150, 150, NULL);
    m_pImgWidget->SetImg("/home/jiang/Projects/Qt/GreenClouD/test.jpg");
    m_pImgWidget->setPos(10, 10);
    m_pScene->addItem(m_pImgWidget);

    this->setCentralWidget(m_pView);
}

CTestWindow::~CTestWindow()
{
    
}

void CTestWindow::SLOT_ButtonTriggeredProc()
{
    m_pButtonWidget->SetText("OK");
}
