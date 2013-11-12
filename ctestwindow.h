#ifndef CTESTWINDOW_H
#define CTESTWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "ctestwidget.h"

class CTestWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    CTestWindow(QWidget *parent = 0);
    ~CTestWindow();

private:
    QGraphicsScene* m_pScene;
    QGraphicsView* m_pView;
    CTestWidget* m_pTestWidget;
    CTestWidget* m_pTestWidget1;
};

#endif // CTESTWINDOW_H
