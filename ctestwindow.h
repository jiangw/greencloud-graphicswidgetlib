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

class CTestWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    CTestWindow(QWidget *parent = 0);
    ~CTestWindow();

public slots:
    void SLOT_ButtonTriggeredProc();

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
};

#endif // CTESTWINDOW_H
