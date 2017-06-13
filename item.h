#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>

class item : public QWidget
{
    Q_OBJECT
public:
    explicit item(QWidget *parent = 0);

    void setKey(int key_);
    QString getKey();

    void setText(QString text_);
    QString getText();

    void setTime(QString time_);
    QString getTime();

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

    int Key;
    QString text;
    QString time;
    bool isStar;

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void itemIsStarChanged(QString text, bool isStar_);
    void itemClicked(QString text);

public slots:
    void clicked_button_star();
};

#endif // ITEM_H
