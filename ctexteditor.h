#ifndef CTEXTEDITOR_H
#define CTEXTEDITOR_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QPainter>
#include <QString>
#include <QKeyEvent>

class CTextEditor : public QGraphicsTextItem
{
    Q_OBJECT

public:
    enum EditMode{LABEL,/*label mode, uneditable*/\
                  SINGLELINE,/*single line mode, edit in a single line*/\
                  MULTILINE/*multiline mode, edit in multiple lines*/};
    CTextEditor(QGraphicsItem* a_pParent);
    void SetEditMode(EditMode a_EditMode);
    void FinishEditting();

    //override from QGraphicsTextItem
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    //override from QGraphicsTextItem
    void keyPressEvent(QKeyEvent *event);
    void focusOutEvent(QFocusEvent *event);

signals:
    void SIGNAL_EditFinished();

private:
    EditMode m_EditMode;
};

#endif // CTEXTEDITOR_H
