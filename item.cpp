#include "item.h"

item::item(QWidget *parent) : QWidget(parent)
{
    label_text = new QLabel(this);
    label_text->setAttribute(Qt::WA_TranslucentBackground);
    label_text->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    /*label_time = new QLabel();
    label_time->setAttribute(Qt::WA_TranslucentBackground);
    label_time->setAttribute(Qt::WA_TranslucentBackground);
    label_time->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);*/
    button_star = new QPushButton(this);
    button_star->setAttribute(Qt::WA_TranslucentBackground);
    button_star->setStyleSheet("QPushButton{border:none;background-color:transparent;}QPushButton:!hover{image: url(:/st1_16px);}QPushButton:hover{image: url(:/st2_16px);}");
    connect(button_star, SIGNAL(clicked()), this, SLOT(clicked_button_star()));
    label_key = new QLabel(this);
    label_key->setAttribute(Qt::WA_TranslucentBackground);
    label_key->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    label_key->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    button_webSearch = new QPushButton(this);
    button_webSearch->setText("Search");
    button_webSearch->setStyleSheet("QPushButton{border:none;color:white;font-size:8pt;}QPushButton:!hover{background-color: #2CA0DC;}QPushButton:hover{background-color: #157DB3;}");
    connect(button_webSearch, SIGNAL(clicked()), this, SLOT(clicked_button_webSearch()));
    button_copy = new QPushButton(this);
    button_copy->setText(tr("Copy"));
    button_copy->setStyleSheet("QPushButton{border:none;color:white;font-size:8pt;}QPushButton:!hover{background-color: #8AD2CF;}QPushButton:hover{background-color: #44B1AC;}");
    connect(button_copy, SIGNAL(clicked()), this, SLOT(clicked_button_copy()));
    button_delete = new QPushButton(this);
    button_delete->setText(tr("Delete"));
    button_delete->setStyleSheet("QPushButton{border:none;}QPushButton:!hover{background-color:#FF8989;}QPushButton:hover{background-color:#F66F6C;}");
    connect(button_delete, SIGNAL(clicked()), this, SLOT(clicked_button_delete()));
    frame_buttons = new QFrame(this);
    frame_buttons->setAttribute(Qt::WA_TranslucentBackground);
    hBoxLayout_frame = new QHBoxLayout(this);
    hBoxLayout_frame->setMargin(0);
    hBoxLayout_frame->addWidget(button_copy);
    hBoxLayout_frame->addWidget(button_webSearch);
    hBoxLayout_frame->addWidget(button_delete);
    frame_buttons->setLayout(hBoxLayout_frame);
    frame_buttons->hide();
    hBoxLayout = new QHBoxLayout();
    hBoxLayout->setMargin(0);
    hBoxLayout2 = new QHBoxLayout();
    hBoxLayout2->setMargin(0);
    vBoxLayout = new QVBoxLayout();
    vBoxLayout->setMargin(3);
    hBoxLayout->addWidget(label_text);
    hBoxLayout->addWidget(button_star);
    vBoxLayout->addLayout(hBoxLayout);
    hBoxLayout2->addWidget(frame_buttons);
    hBoxLayout2->addWidget(label_key);
    vBoxLayout->addLayout(hBoxLayout2);
    setLayout(vBoxLayout);
    setAttribute(Qt::WA_TranslucentBackground);
}

void item::setKey(int key_)
{
    Key = key_;
    if(key_==0)
        return;
    if(key_<=keyMax)
    {
        label_key->setText("<html><head/><body><p><span><i>Ctrl</i></span><i>+</i><span><i>"+QString::number(key_)+"</i></span></p></body></html>");
        //label_key->setText("<img src=\":/kCtrl\"  alt=\"Ctrl\" /><img src=\":/k"+QString::number(key_)+"\"  alt=\""+QString::number(key_)+"\" />");
        label_key->setToolTip("<b>Shortcut key:</b><br />    Ctrl+"+QString::number(key_));
    }
}

void item::setText(QString text_)
{
    text = text_;
    label_text->setText("<h4>"+label_text->fontMetrics().elidedText(text_, Qt::ElideRight, textMaxLong, Qt::TextSingleLine)+"</h4>");
    label_text->setToolTip("<b>Text:</b><br />    "+text);
}

QString item::getText()
{
    return text;
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


void item::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit itemClicked(text);
}

void item::clicked_button_star()
{
    setStar(!getIsStar());
    emit itemIsStarChanged(text, getIsStar());
}

void item::clicked_button_webSearch()
{
    //openUrl(baiduSearchAPI+text);
    emit itemWebSearch(text);
}

void item::clicked_button_copy()
{
    //setClipboardText(text);
    emit itemCopy(text);
}

void item::clicked_button_delete()
{
    emit itemDelete(text);
}

void item::focusOn()
{
    frame_buttons->show();
}

void item::focusLost()
{
    frame_buttons->hide();
}
