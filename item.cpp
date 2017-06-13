#include "item.h"

item::item(QWidget *parent) : QWidget(parent)
{
    label_text = new QLabel();
    label_text->setAttribute(Qt::WA_TranslucentBackground);
    label_text->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    label_time = new QLabel();
    label_time->setAttribute(Qt::WA_TranslucentBackground);
    label_time->setAttribute(Qt::WA_TranslucentBackground);
    button_star = new QPushButton();
    button_star->setAttribute(Qt::WA_TranslucentBackground);
    button_star->setStyleSheet("QPushButton{border:none;background-color:transparent;}QPushButton:!hover{image: url(:/st1_16px);}QPushButton:hover{image: url(:/st2_16px);}");
    connect(button_star, SIGNAL(clicked()), this, SLOT(clicked_button_star()));
    label_key = new QLabel();
    label_key->setAttribute(Qt::WA_TranslucentBackground);
    hBoxLayout = new QHBoxLayout();
    hBoxLayout2 = new QHBoxLayout();
    vBoxLayout = new QVBoxLayout();
    hBoxLayout->addWidget(label_text);
    hBoxLayout->addWidget(button_star);
    vBoxLayout->addLayout(hBoxLayout);
    hBoxLayout2->addWidget(label_key);
    hBoxLayout2->addWidget(label_time);
    vBoxLayout->addLayout(hBoxLayout2);
    setLayout(vBoxLayout);
    setAttribute(Qt::WA_TranslucentBackground);
}

void item::setKey(int key_)
{
    Key = key_;
    if(key_+1<=keyMax)
    {
        label_key->setText("<img src=\":/kCtrl\"  alt=\"Ctrl\" /><img src=\":/k"+QString::number(key_+1)+"\"  alt=\""+QString::number(key_+1)+"\" />");
    }
}

void item::setText(QString text_)
{
    text = text_;
    if(text.length()>textMaxLong)
    {
        text_ = text_.left(20)+"...";
    }
    label_text->setText("<h3>"+text_+"</h3>");
    label_text->setToolTip("<b>Text:</b><br />    "+text);
}

QString item::getText()
{
    return text;
}

void item::setTime(QString time_)
{
    time = time_;
    label_time->setText("<i><font color = #C0C0C0><h6>"+time_+"</h6></font></i>");
    label_time->setToolTip("<b>Time:</b> "+time);
}

QString item::getTime()
{
    return time;
}

void item::setStar(bool isStar_)
{
    isStar = isStar_;
    if(isStar_)
        button_star->setStyleSheet("QPushButton{padding:5px;border:none;background-color:transparent;}QPushButton:!hover{image: url(:/st1_16px);}QPushButton:hover{image: url(:/st2_16px);}");
    else
        button_star->setStyleSheet("QPushButton{padding:5px;border:none;background-color:transparent;}QPushButton:hover{image: url(:/st1_16px);}QPushButton:!hover{image: url(:/st2_16px);}");
    button_star->setAttribute(Qt::WA_TranslucentBackground);

}

bool item::getIsStar()
{
    return isStar;
}

void item::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit itemClicked(text);
}

void item::clicked_button_star()
{
    setStar(!getIsStar());
    emit itemIsStarChanged(text, getIsStar());
}
