#ifndef ITEM_H
#define ITEM_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>

class item : public QWidget
{
    Q_OBJECT
public:
    explicit item(QWidget *parent = 0);

    void setKey(int key_);
    QString getKey();

    void setText(QString text_);
    QString getText();

    void setStar(bool isStar_);
    bool getIsStar();

private:
    const int textMaxLong = 180;
    const int keyMax = 5;
    QLabel *label_text;
    QPushButton *button_star;
    QLabel *label_star;
    QLabel *label_key;
    QPushButton *button_webSearch;
    QPushButton *button_copy;
    QPushButton *button_delete;
    QHBoxLayout *hBoxLayout;
    QHBoxLayout *hBoxLayout2;
    QVBoxLayout *vBoxLayout;
    QHBoxLayout *hBoxLayout_frame;
    QFrame *frame_buttons;

    int Key;
    QString text;
    bool isStar;

    const QString baiduSearchAPI="https://www.baidu.com/s?wd=";

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);

signals:
    void itemIsStarChanged(QString text, bool isStar_);
    void itemClicked(QString text);
    void itemCopy(QString text);
    void itemWebSearch(QString text);
    void itemDelete(QString text);

public slots:
    void clicked_button_star();
    void clicked_button_webSearch();
    void clicked_button_copy();
    void clicked_button_delete();
    void focusOn();
    void focusLost();
};

#endif // ITEM_H
