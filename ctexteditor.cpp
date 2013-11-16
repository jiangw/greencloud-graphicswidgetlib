#include "ctexteditor.h"

CTextEditor::CTextEditor(QGraphicsItem *a_pParent)
    :QGraphicsTextItem(a_pParent)
{
    this->SetEditMode(LABEL);
}

void CTextEditor::SetEditMode(EditMode a_EditMode)
{
    switch(a_EditMode)
    {
    case SINGLELINE:
        m_EditMode = SINGLELINE;
        this->setTextInteractionFlags(Qt::TextEditorInteraction);
        break;
    case MULTILINE:
        m_EditMode = MULTILINE;
        this->setTextInteractionFlags(Qt::TextEditorInteraction);
        break;
    default:
        m_EditMode = LABEL;
        this->setTextInteractionFlags(Qt::NoTextInteraction);
    }
}


void CTextEditor::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->fillRect(this->boundingRect(), Qt::white);

    painter->restore();

    QGraphicsTextItem::paint(painter, option, widget);
}

void CTextEditor::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        this->clearFocus();
        emit this->SIGNAL_EditFinished();
    }
    else if(event->key() == Qt::Key_Return && SINGLELINE == m_EditMode)
    {
        this->clearFocus();
        emit this->SIGNAL_EditFinished();
    }
    else
    {
        QGraphicsTextItem::keyPressEvent(event);
    }
}

void CTextEditor::focusOutEvent(QFocusEvent *event)
{
    QGraphicsTextItem::focusOutEvent(event);

    if(LABEL != m_EditMode)
    {
        this->clearFocus();
        emit this->SIGNAL_EditFinished();
    }
}
