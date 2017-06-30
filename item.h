#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include <QDate>
#include <QDateTime>
#include <QTimer>

class item : public QWidget
{
    Q_OBJECT
public:
    explicit item(QWidget *parent = 0);

    void setKey(int key_);
    QString getKey();

    void setText(QString text_);
    QString getText();

    void setTime(QDateTime time_);
    QDateTime getTime();

    void setStar(bool isStar_);
    bool getIsStar();

private:
    const int textMaxLong = 17;
    const int keyMax = 5;
    QLabel *label_text;
    QLabel *label_time;
    QPushButton *button_star;
    QLabel *label_star;
    QLabel *label_key;
    QHBoxLayout *hBoxLayout;
    QHBoxLayout *hBoxLayout2;
    QVBoxLayout *vBoxLayout;
    QTimer *timer = new QTimer(this);

    int Key;
    QString text;
    QDateTime time;
    bool isStar;

    QString getMyDate(QDateTime date);

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void itemIsStarChanged(QString text, bool isStar_);
    void itemClicked(QString text);

public slots:
    void clicked_button_star();
    void refreshDate();
};

#endif // ITEM_H
