#include "ctestwindow.h"

CTestWindow::CTestWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 300, 300);

    m_pScene = new QGraphicsScene(this);
    m_pScene->setSceneRect(0, 0, 200, 200);
    m_pView = new QGraphicsView(this);
    m_pView->setScene(m_pScene);

    m_pTestWidget = new CTestWidget(m_pScene->width(), m_pScene->height(), NULL);
    m_pScene->addItem(m_pTestWidget);

    this->setCentralWidget(m_pView);
}

CTestWindow::~CTestWindow()
{
    
}
