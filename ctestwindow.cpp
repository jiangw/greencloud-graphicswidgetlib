#include "ctestwindow.h"

CTestWindow::CTestWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setGeometry(0, 0, 500, 300);

    m_pScene = new QGraphicsScene(this);
    m_pScene->setSceneRect(0, 0, 400, 200);
    m_pScene->setBackgroundBrush(QBrush(CGraphicsWidget::green));
    m_pView = new QGraphicsView(this);
    m_pView->setScene(m_pScene);

    this->setCentralWidget(m_pView);
}

CTestWindow::~CTestWindow()
{
    
}

void CTestWindow::SLOT_ButtonTriggeredProc()
{
    m_pButtonWidget->SetText("OK");
}

void CTestWindow::SLOT_ShowMsgBox()
{
    CMessageWidget* l_pNewMsgBox = new CMessageWidget(m_pScene);
    l_pNewMsgBox->SetInfo("You are using me.");
    l_pNewMsgBox->SetQuestion("How are your?");
    l_pNewMsgBox->SetMsgBoxPos(30, 30);
}
