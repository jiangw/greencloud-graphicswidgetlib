#ifndef CTESTWINDOW_H
#define CTESTWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "ctestwidget.h"
#include "ccheckwidget.h"
#include "cbuttonwidget.h"
#include "csvgwidget.h"
#include "ctexteditor.h"
#include "ctextwidget.h"
#include "cwidgetlist.h"
#include "cimgwidget.h"
#include "cmessagewidget.h"

class CTestWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    CTestWindow(QWidget *parent = 0);
    ~CTestWindow();

public slots:
    void SLOT_ButtonTriggeredProc();
    void SLOT_ShowMsgBox();

private:
    QGraphicsScene* m_pScene;
    QGraphicsView* m_pView;
    CTestWidget* m_pTestWidget;
    CTestWidget* m_pTestWidget1;
    CCheckWidget* m_pCheckWidget;
    CButtonWidget* m_pButtonWidget;
    CTextEditor* m_pTextEditor;
    CTextWidget* m_pTextWidget;
    CWidgetList* m_pWidgetList;
    CImgWidget* m_pImgWidget;
    CMessageWidget* m_pMsgWidget;
};

#endif // CTESTWINDOW_H
