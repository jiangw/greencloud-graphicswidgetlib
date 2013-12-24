#ifndef CMESSAGEWIDGET_H
#define CMESSAGEWIDGET_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QBrush>

#include "cgraphicswidget.h"
#include "cbuttonwidget.h"

class CMessageWidget : public CGraphicsWidget
{
    Q_OBJECT

public:
    enum EMessageType{MS_INFO, MS_YESNO};
    CMessageWidget(QGraphicsScene *a_pScene);

    void SetMsgType(EMessageType a_EMsgType);
    void SetQuestion(QString a_qstrQuestion);
    void SetInfo(QString a_qstrInfo);
    void SetMsgBoxPos(int x, int y);
    void SetMsgBoxWidth(int a_iWidth);
    void SetMsgBoxHeight(int a_iHeight);
    int GetMsgBoxWidth(){return m_iMsgBoxWidth;}
    int GetMsgBoxHeight(){return m_iMsgBoxHeight;}

    //override from CGraphicsWidget
    int WidgetWidth(){return m_iWidgetWidth;}
    int WidgetHeight(){return m_iWidgetHeight;}
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public slots:
    void SLOT_OkEmit();
    void SLOT_CancelEmit();

signals:
    void SIGNAL_Ok();
    void SIGNAL_Cancel();

private:
    void UpdateButtonsPos();

    EMessageType m_EMsgType;
    QGraphicsScene* m_pScene;
    int m_iWidgetWidth, m_iWidgetHeight;
    int m_iMsgBoxMinWidth, m_iMsgBoxMinHeight;
    QBrush m_CBackground;
    int m_iMsgBoxWidth, m_iMsgBoxHeight;
    QPointF m_CMsgBoxPos;
    QString m_qstrMsgBoxQuestion, m_qstrMsgBoxInfo;
    QFont m_CQuestionFont, m_CInfoFont;
    CButtonWidget* m_pOK;
    CButtonWidget* m_pCancel;
};

#endif // CMESSAGEWIDGET_H
