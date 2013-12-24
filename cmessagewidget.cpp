#include "cmessagewidget.h"

CMessageWidget::CMessageWidget(QGraphicsScene* a_pScene)
    :CGraphicsWidget(NULL)
{
    m_pScene = a_pScene;
    if(NULL != m_pScene)
    {
        m_iWidgetWidth = m_pScene->sceneRect().width();
        m_iWidgetHeight = m_pScene->sceneRect().height();

        m_CMsgBoxPos.setX(5);
        m_CMsgBoxPos.setY(5);
        m_iMsgBoxMinWidth = 200;
        m_iMsgBoxMinHeight = 90;
        m_iMsgBoxWidth = m_iMsgBoxMinWidth;
        m_iMsgBoxHeight = m_iMsgBoxMinHeight;
        m_CBackground.setStyle(Qt::SolidPattern);
        m_CBackground.setColor(QColor(30, 30, 30, 100));
        m_CQuestionFont.setFamily("STIX");
        m_CQuestionFont.setPointSize(14);
        m_CQuestionFont.setBold(true);
        m_CInfoFont.setFamily("WenQuanYi Zen Hei");
        m_CInfoFont.setPointSize(12);

        this->SetInfo("Information: ");
        this->SetQuestion("Question");

        this->InitBoundingRect();

        m_pOK = new CButtonWidget("OK", this);
        m_pOK->SetTextFontSize(10);
        m_pCancel = new CButtonWidget("Cancel", this);
        m_pCancel->SetTextFontSize(10);

        connect(m_pOK, SIGNAL(SIGNAL_ButtonTriggered()),\
                this, SLOT(SLOT_OkEmit()));
        connect(m_pCancel, SIGNAL(SIGNAL_ButtonTriggered()),\
                this, SLOT(SLOT_CancelEmit()));

        this->SetMsgType(MS_INFO);

        this->setPos(m_pScene->sceneRect().x(), m_pScene->sceneRect().y());
        m_pScene->addItem(this);
    }
}

void CMessageWidget::SetMsgType(EMessageType a_EMsgType)
{
    m_EMsgType = a_EMsgType;
    this->UpdateButtonsPos();
}

void CMessageWidget::SetInfo(QString a_qstrInfo)
{
    m_qstrMsgBoxInfo = a_qstrInfo;
    update(m_CMsgBoxPos.x(), m_CMsgBoxPos.y(), m_iMsgBoxWidth, m_iMsgBoxHeight);
}

void CMessageWidget::SetQuestion(QString a_qstrQuestion)
{
    m_qstrMsgBoxQuestion = a_qstrQuestion;
    update(m_CMsgBoxPos.x(), m_CMsgBoxPos.y(), m_iMsgBoxWidth, m_iMsgBoxHeight);
}

void CMessageWidget::SetMsgBoxPos(int x, int y)
{
    m_CMsgBoxPos.setX(x + (0 - m_pScene->sceneRect().x()));
    m_CMsgBoxPos.setY(y + (0 - m_pScene->sceneRect().y()));
    this->UpdateButtonsPos();
    update(this->boundingRect());
}

void CMessageWidget::SetMsgBoxWidth(int a_iWidth)
{
    m_iMsgBoxWidth = a_iWidth;
    if(m_iMsgBoxWidth < m_iMsgBoxMinWidth)
    {
        m_iMsgBoxWidth = m_iMsgBoxMinWidth;
    }
    this->UpdateButtonsPos();
    update(this->boundingRect());
}

void CMessageWidget::SetMsgBoxHeight(int a_iHeight)
{
    m_iMsgBoxHeight = a_iHeight;
    if(m_iMsgBoxHeight < m_iMsgBoxMinHeight)
    {
        m_iMsgBoxHeight = m_iMsgBoxMinHeight;
    }
    this->UpdateButtonsPos();
    update(this->boundingRect());
}

void CMessageWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->save();
    painter->setRenderHint(QPainter::Antialiasing);

    painter->fillRect(this->boundingRect(), m_CBackground);

    painter->setPen(QPen(QBrush(Qt::black), 3));
    painter->fillRect(m_CMsgBoxPos.x(), m_CMsgBoxPos.y(),\
                      m_iMsgBoxWidth, m_iMsgBoxHeight,\
                      QBrush(Qt::white));
    painter->drawRect(m_CMsgBoxPos.x(), m_CMsgBoxPos.y(),\
                      m_iMsgBoxWidth, m_iMsgBoxHeight);

    painter->setFont(m_CInfoFont);
    painter->drawText(m_CMsgBoxPos.x() + 2, m_CMsgBoxPos.y(), m_iMsgBoxWidth - 4, 20,\
                      Qt::AlignLeft, m_qstrMsgBoxInfo);
    painter->setFont(m_CQuestionFont);
    painter->drawText(m_CMsgBoxPos.x() + 2, m_CMsgBoxPos.y() + 20,\
                      m_iMsgBoxWidth - 4,\
                      m_iMsgBoxHeight - 20 - m_pOK->boundingRect().height() - 5,\
                      Qt::AlignCenter, m_qstrMsgBoxQuestion);

    painter->restore();
}

void CMessageWidget::SLOT_OkEmit()
{
    emit this->SIGNAL_Ok();
    m_pScene->removeItem(this);
}

void CMessageWidget::SLOT_CancelEmit()
{
    emit this->SIGNAL_Cancel();
    m_pScene->removeItem(this);
}

void CMessageWidget::UpdateButtonsPos()
{
    switch(m_EMsgType)
    {
    case MS_YESNO:
        m_pOK->setPos(m_CMsgBoxPos.x() + m_iMsgBoxWidth / 2 - m_pOK->boundingRect().width() - 5,\
                      m_CMsgBoxPos.y() + m_iMsgBoxHeight - m_pOK->boundingRect().height() - 5);
        m_pCancel->setPos(m_pOK->pos().x() + m_pOK->boundingRect().width() + 10,\
                          m_pOK->pos().y());
        m_pCancel->setVisible(true);
        break;
    default:
        m_pOK->setPos(m_CMsgBoxPos.x() + m_iMsgBoxWidth / 2 - m_pOK->boundingRect().width() / 2,\
                      m_CMsgBoxPos.y() + m_iMsgBoxHeight - m_pOK->boundingRect().height() - 5);
        m_pCancel->setVisible(false);
        break;
    }
}
