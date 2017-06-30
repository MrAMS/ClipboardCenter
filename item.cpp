#include "item.h"
#include <QDebug>

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

    timer->start(15*1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(refreshDate()));
}

void item::setKey(int key_)
{
    Key = key_;
    if(key_==0)
        return;
    if(key_<=keyMax)
    {
        label_key->setText("<img src=\":/kCtrl\"  alt=\"Ctrl\" /><img src=\":/k"+QString::number(key_)+"\"  alt=\""+QString::number(key_)+"\" />");
        label_key->setToolTip("<b>Shortcut key:</b><br />    Ctrl+"+QString::number(key_));
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

void item::setTime(QDateTime time_)
{
    time = time_;
    label_time->setText("<i><font color = #C0C0C0><h6>"+getMyDate(time_)+"</h6></font></i>");
    label_time->setToolTip("<b>Time:</b><br />    "+time.toString("yyyy-MM-dd dddd hh:mm"));
}

QDateTime item::getTime()
{
    return time;
}

void item::setStar(bool isStar_)
{
    isStar = isStar_;
    if(isStar_)
    {
        button_star->setStyleSheet("QPushButton{padding:5px;border:none;background-color:transparent;}QPushButton:!hover{image: url(:/st1_16px);}QPushButton:hover{image: url(:/st2_16px);}");
        button_star->setToolTip("<b>Star:</b><br />     Remove from favorites list");
    }
    else
    {
        button_star->setStyleSheet("QPushButton{padding:5px;border:none;background-color:transparent;}QPushButton:hover{image: url(:/st1_16px);}QPushButton:!hover{image: url(:/st2_16px);}");
        button_star->setToolTip("<b>Star:</b><br />     Add to favorites list");
    }
    button_star->setAttribute(Qt::WA_TranslucentBackground);
}

bool item::getIsStar()
{
    return isStar;
}

QString item::getMyDate(QDateTime date)
{
    QDateTime dateTime_now = QDateTime::currentDateTime();
    QDate time = date.date();
    QDate now = dateTime_now.date();
    if((time.year()==now.year()) and (time.month()==now.month()))
    {
        if(time.day() == now.day())
        {
            QTime time_time = date.time();
            QTime time_now = dateTime_now.time();
            int hour = time_now.hour()-time_time.hour();
            if(hour==0)
            {
                int minute = time_now.minute()-time_time.minute();
                if(minute == 0)
                    return "A moment ago";
                else{
                    if(minute==1)
                        return QString::number(minute)+" minute ago";
                    else
                        return QString::number(minute)+" minutes ago";
            }
            }else{
                if(hour==1)
                    return QString::number(hour)+" hour ago";
                else
                    return QString::number(hour)+" hours ago";
            }
        }else{
            int days = time.daysTo(now);
            if(days==1)
                return QString::number(days)+" day ago";
            else
                return QString::number(days)+" days ago";
        }
    }else
        return date.toString("yyyy-MM-dd dddd hh:mm");
}

void item::refreshDate()
{
    label_time->setText("<i><font color = #C0C0C0><h6>"+getMyDate(time)+"</h6></font></i>");
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
