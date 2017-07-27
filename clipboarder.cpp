#include "clipboarder.h"
#include "ui_clipboarder.h"

#include <qDebug>

Clipboarder::Clipboarder(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Clipboarder)
{
    ui->setupUi(this);
    connect(board, SIGNAL(changed(QClipboard::Mode)), this, SLOT(clipboardChanged(QClipboard::Mode)));
    //connect(ui->pushButton_quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    setWindowFlags(Qt::WindowTitleHint|Qt::WindowSystemMenuHint|Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setOffset(-5, 5);
    shadow_effect->setColor(QColor("#3A4055"));
    shadow_effect->setBlurRadius(8);
    ui->frame_main->setGraphicsEffect(shadow_effect);
    ui->stackedWidget->setCurrentIndex(0);
    ui->frame_2->layout()->setMargin(0);
    ui->frame->layout()->setMargin(0);
    //setWindowOpacity(0.8);
    loadSettings();

    QAction* action_save = new QAction(this);
    action_save->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    connect(action_save, SIGNAL(triggered()), this, SLOT(searchItem()));

    if(!QSystemTrayIcon::isSystemTrayAvailable())
        return;
    createActions();
    system_tray ->setToolTip(tr("AMS - ClipboardCenter v2.0"));
    system_tray ->setIcon(QIcon("://logo"));
    system_tray->setContextMenu(menu_tray);
    //connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    //connect(tray_menu, SIGNAL(showWidget()), this, SLOT(showNormal()));

    system_tray->show();
    system_tray->showMessage(tr("AMS - ClipboardCenter v2.0"), QString("ClipboardCenter is already!"));

    timer->start(500);
    connect(timer, SIGNAL(timeout()), this, SLOT(fRefresh()));

    hideWidget();
}

Clipboarder::~Clipboarder()
{
    delete ui;
}

void Clipboarder::mousePressEvent(QMouseEvent *event)
{
    mMoveing = true;
    mMovePosition = event->globalPos() - pos();
    event->accept();
}

void Clipboarder::mouseMoveEvent(QMouseEvent *event)
{
    if (mMoveing && (event->buttons() && Qt::LeftButton)
            && (event->globalPos()-mMovePosition).manhattanLength() > QApplication::startDragDistance())
    {
        move(event->globalPos()-mMovePosition);
        mMovePosition = event->globalPos() - pos();
    }
    event->accept();
}

void Clipboarder::mouseReleaseEvent(QMouseEvent *event)
{
    mMoveing = false;
}

void Clipboarder::closeEvent(QCloseEvent *event)
{
    saveSettings();
    system_tray->hide();
}

void Clipboarder::hotKey_Ctrl1()
{
    if(list_clipboarde.length()>=2 and ui->stackedWidget->currentIndex()==0)
        setClipboardText(list_clipboarde[1]);
    else
    {
        if(ui->listWidget_starList->item(1))
            setClipboardText(map_item_starList.value(ui->listWidget_starList->item(1))->getText());
    }
}

void Clipboarder::hotKey_Ctrl2()
{
    if(list_clipboarde.length()>=3 and ui->stackedWidget->currentIndex()==0)
        setClipboardText(list_clipboarde[2]);
    else
    {
        if(ui->listWidget_starList->item(2))
            setClipboardText(map_item_starList.value(ui->listWidget_starList->item(2))->getText());
    }
}

void Clipboarder::hotKey_Ctrl3()
{
    if(list_clipboarde.length()>=4 and ui->stackedWidget->currentIndex()==0)
        setClipboardText(list_clipboarde[3]);
    else
    {
        if(ui->listWidget_starList->item(3))
            setClipboardText(map_item_starList.value(ui->listWidget_starList->item(3))->getText());
    }
}

void Clipboarder::hotKey_Ctrl4()
{
    if(list_clipboarde.length()>=5 and ui->stackedWidget->currentIndex()==0)
        setClipboardText(list_clipboarde[4]);
    else
    {
        if(ui->listWidget_starList->item(4))
            setClipboardText(map_item_starList.value(ui->listWidget_starList->item(4))->getText());
    }
}

void Clipboarder::hotKey_Ctrl5()
{
    if(list_clipboarde.length()>=6 and ui->stackedWidget->currentIndex()==0)
        setClipboardText(list_clipboarde[5]);
    else
    {
        if(ui->listWidget_starList->item(5))
            setClipboardText(map_item_starList.value(ui->listWidget_starList->item(5))->getText());
    }
}

void Clipboarder::clipboardChanged(QClipboard::Mode mode_)
{
    QString text = getClipboardText();
    if(list_clipboarde.isEmpty())
    {
        list_clipboarde.insert(0,text);
        loadClipboardList(mode_);
        emit on_pushButton_toHistory_clicked();
        if(isHide)
            onTheTop();
        else
            disOnTheTop();
        return;
    }
    if(mode_ != mode or text.isEmpty() or list_clipboarde[0]==text)
        return;

    list_clipboarde.removeAll(text);
    list_clipboarde.insert(0,text);
    loadClipboardList(mode_);
    emit on_pushButton_toHistory_clicked();
    if(isHide)
        onTheTop();
    else
        disOnTheTop();
}

void Clipboarder::fRefresh()
{
    clipboardChanged(mode);
}

void Clipboarder::setClipboardText(const QString &text)
{
    board->setText(text, mode);
    return;
}

QString Clipboarder::getClipboardText()
{
    return board->text(mode);
}

void Clipboarder::saveSettings()
{
    QSettings settings("AMS","ClipboardCenter");
    settings.beginGroup("settings");
    settings.setValue("pos",pos());
    settings.endGroup();
}

void Clipboarder::loadSettings()
{
    QSettings settings("AMS","ClipboardCenter");
    settings.beginGroup("settings");
    move(settings.value("pos",QPoint(QApplication::desktop()->availableGeometry().center().x()-width()/2,0)).toPoint());
    settings.endGroup();

}

void Clipboarder::loadClipboardList(QClipboard::Mode mode_)
{
    ui->listWidget->clear();
    int key=0;
    foreach (QString text, list_clipboarde) {
        addItem(text, isStarText(text), key);
        key++;
    }
}

void Clipboarder::loadStarList()
{
    ui->listWidget_starList->clear();
    map_item_starList.clear();

    QSettings settings("AMS","ClipboardCenter");
    settings.beginGroup("data");
    int key=0;
    foreach (QString s, settings.value("starList").toStringList()) {
        addItem_starList(s, key);
        key++;
    }
    settings.endGroup();
}

bool Clipboarder::isStarText(QString text)
{
    QSettings settings("AMS","ClipboardCenter");
    settings.beginGroup("data");
    foreach (QString s, settings.value("starList").toStringList())
        if(s==text)
        {
            settings.endGroup();
            return true;
        }
    settings.endGroup();
    return false;
}

void Clipboarder::itemIsStarChanged_receiver(QString text, bool isStar_)
{
    if(text == "")
        return;
    QSettings settings("AMS","ClipboardCenter");
    settings.beginGroup("data");
    QStringList list = settings.value("starList").toStringList();
    if(!isStar_)
    {
        list.removeAll(text);
    }else
    {
        list.insert(0, text);
    }

    settings.setValue("starList", list);
    loadClipboardList(mode);
    loadStarList();
}

void Clipboarder::itemClicked_receiver(QString text)
{
    setClipboardText(text);
    emit on_pushButton_toHistory_clicked();
}

void Clipboarder::itemCopy_receiver(QString text)
{
    setClipboardText(text);
}

void Clipboarder::itemWebSearch_receiver(QString text)
{
    openUrl(baiduSearchAPI + text);
}

void Clipboarder::itemDelete_receiver(QString text)
{
    list_clipboarde.removeAll(text);
    loadClipboardList(mode);
}

void Clipboarder::itemDelete_receiver_starList(QString text)
{
    emit itemIsStarChanged_receiver(text, false);
}

void Clipboarder::addItem(QString text, bool isStar, int key)
{
    item *widget = new item(this);
    widget->setText(text);
    widget->setStar(isStar);
    widget->setKey(key);
    connect(widget, SIGNAL(itemIsStarChanged(QString, bool)), this, SLOT(itemIsStarChanged_receiver(QString, bool)));
    connect(widget, SIGNAL(itemCopy(QString)), this, SLOT(itemCopy_receiver(QString)));
    connect(widget, SIGNAL(itemWebSearch(QString)), this, SLOT(itemWebSearch_receiver(QString)));
    connect(widget, SIGNAL(itemDelete(QString)), this, SLOT(itemDelete_receiver(QString)));
    connect(widget, SIGNAL(itemClicked(QString)), this, SLOT(itemClicked_receiver(QString)));
    QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget);
    ui->listWidget->addItem(item_ui);
    ui->listWidget->setItemWidget(item_ui, widget);
    item_ui->setSizeHint(QSize(widget->width(),widget->height()));
    map_item_bored.insert(item_ui, widget);
}

void Clipboarder::addItem_starList(QString text, int key)
{
    item *widget = new item(this);
    widget->setText(text);
    widget->setStar(true);
    widget->setKey(key);
    connect(widget, SIGNAL(itemIsStarChanged(QString, bool)), this, SLOT(itemIsStarChanged_receiver(QString, bool)));
    connect(widget, SIGNAL(itemCopy(QString)), this, SLOT(itemCopy_receiver(QString)));
    connect(widget, SIGNAL(itemWebSearch(QString)), this, SLOT(itemWebSearch_receiver(QString)));
    connect(widget, SIGNAL(itemDelete(QString)), this, SLOT(itemDelete_receiver_starList(QString)));
    connect(widget, SIGNAL(itemClicked(QString)), this, SLOT(itemClicked_receiver(QString)));
    QListWidgetItem *item_ui = new QListWidgetItem("",ui->listWidget_starList);
    ui->listWidget_starList->addItem(item_ui);
    ui->listWidget_starList->setItemWidget(item_ui, widget);
    item_ui->setSizeHint(QSize(widget->width(),widget->height()));
    map_item_starList.insert(item_ui, widget);
}

void Clipboarder::showWidget()
{
    move(x(),0);
    isHide = false;
    ui->pushButton_show->setIcon(QIcon("://up"));
}

void Clipboarder::hideWidget()
{
    move(x(),-1*height()+ui->frame_2->height()+30);
    isHide = true;
    ui->pushButton_show->setIcon(QIcon("://down"));

}

void Clipboarder::onTheTop()
{
    hide();
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::WindowTitleHint|Qt::WindowSystemMenuHint|Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    show();
}

void Clipboarder::disOnTheTop()
{
    hide();
    setWindowFlags(Qt::WindowTitleHint|Qt::WindowSystemMenuHint|Qt::WindowCloseButtonHint|Qt::FramelessWindowHint);
    show();
}

void Clipboarder::searchItem()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if(!item)
        return;
    openUrl(baiduSearchAPI+map_item_bored.value(item)->getText());
}

void Clipboarder::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void Clipboarder::showAboutWidget()
{
    QDialog *dialog = new QDialog(this);
    //dialog->setWindowFlags(Qt::Dialog|Qt::WindowTitleHint|Qt::FramelessWindowHint|Qt::WindowCloseButtonHint);
    //dialog->setAttribute(Qt::WA_TranslucentBackground);
    /*QGraphicsDropShadowEffect *shadow_effect_dialog = new QGraphicsDropShadowEffect();
    shadow_effect_dialog->setOffset(-5, 5);
    shadow_effect_dialog->setColor(QColor("#3A4055"));
    shadow_effect_dialog->setBlurRadius(8);*/
    QVBoxLayout *vBoxLayout = new QVBoxLayout;
    QFrame *frame = new QFrame;
    frame->setStyleSheet("QFrame{background-color: #FFFFFF;}");
    //frame->setGraphicsEffect(shadow_effect_dialog);
    QLabel *context  = new QLabel("<html><head/><body><p align=\"center\"><img src=\":/logo\"/></p><p align=\"center\"><span style=\" font-size:11pt; color:#a2b2c2;\">AMS</span><span style=\" font-size:11pt; font-weight:600; color:#507596;\"> - ClipboardCenter</span></p><p align=\"center\"><span style=\" font-size:11pt; font-weight:600; color:#507596;\">V2.0</span></p><p align=\"center\"><span style=\" font-size:11pt; font-weight:600; color:#a2b2c2;\">A </span><span style=\" font-size:11pt; font-weight:600; color:#507596;\">convenient</span><span style=\" font-size:11pt; font-weight:600; color:#a2b2c2;\"> and </span><span style=\" font-size:11pt; font-weight:600; color:#507596;\">quick</span><span style=\" font-size:11pt; font-weight:600; color:#a2b2c2;\"> clipboard</span></p><p align=\"center\"><br/>By <a href=\"https://mrams.github.io/\"><span style=\" font-weight:600; text-decoration: underline; color:#ffd800;\">San Diego</span></a></p><p align=\"center\"><span style=\" color:#55aaff;\">2421653893@qq.com</span></p><p align=\"center\"><a href=\"https://github.com/MrAMS/ClipboardCenter\"><span style=\" font-weight:600; text-decoration: underline; color:#55aaff;\">GitHub</span></a></p><p align=\"center\"><a href=\"http://git.oschina.net/mrams/ClipboardCenter\"><span style=\" font-weight:600; text-decoration: underline; color:#00aaff;\">码云</span></a></p></body></html>");
    connect(context,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
    QPushButton *button = new QPushButton("OK");
    button->setStyleSheet("QPushButton{padding:5px;border:none;}QPushButton:!hover{background-color:#FFFFFF;}QPushButton:hover{background-color:#81C784;}");
    vBoxLayout->addWidget(context);
    vBoxLayout->addWidget(button);
    dialog->setLayout(vBoxLayout);
    connect(button, SIGNAL(clicked()), dialog, SLOT(accept()));
    dialog->exec();
}

void Clipboarder::createActions()
{
    QAction *action_show = new QAction(this);
    QAction *action_quit = new QAction(this);
    //QAction *action_login_home = new QAction(this);
    QAction *action_about = new QAction(this);
    //QAction *action_check_update = new QAction(this);
    //QAction *action_setting = new QAction(this);

    action_show->setIcon(QIcon(":/menu_tray/show"));
    //action_login_home->setIcon(QIcon(":/menu_tray/web"));
    action_about->setIcon(QIcon(":/menu_tray/about"));
    //action_check_update->setIcon(QIcon(":/menu_tray/updata"));
    //action_setting->setIcon(QIcon(":/menu_tray/settings"));
    action_quit->setIcon(QIcon(":/menu_tray/quit"));

    action_show->setText(tr("Show"));
    action_quit->setText(tr("Quit"));
    //action_login_home->setText(tr("Home on Web"));
    action_about->setText(tr("About"));
    //action_check_update->setText(tr("Updata"));
    //action_setting->setText(tr("Settings"));

    menu_tray->addAction(action_show);
    //menu_tray->addAction(action_setting);
    //menu_tray->addAction(action_login_home);
    menu_tray->addSeparator();
    menu_tray->addAction(action_about);
    //menu_tray->addAction(action_check_update);
    menu_tray->addSeparator();
    menu_tray->addAction(action_quit);
    //action_setting->setVisible(false);

    connect(action_show, SIGNAL(triggered(bool)), this, SLOT(showWidget()));
    connect(action_quit, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
    connect(action_about, SIGNAL(triggered(bool)), this, SLOT(showAboutWidget()));

    //QObject::connect(action_show, SIGNAL(triggered(bool)), this, SLOT(showWidget()));
}

void Clipboarder::on_pushButton_toHistory_clicked()
{
    ui->pushButton_toStar->setIcon(QIcon(":/st2"));
    ui->pushButton_toHistory->setIcon(QIcon(":/hi"));
    ui->stackedWidget->setCurrentIndex(0);
    loadClipboardList(mode);
}

void Clipboarder::on_pushButton_toStar_clicked()
{
    ui->pushButton_toStar->setIcon(QIcon(":/st1"));
    ui->pushButton_toHistory->setIcon(QIcon(":/hi2"));
    ui->stackedWidget->setCurrentIndex(1);
    loadStarList();
}

void Clipboarder::on_pushButton_clicked()
{
    QSettings settings("AMS","ClipboardCenter");
    settings.clear();
    loadStarList();
}

void Clipboarder::on_pushButton_info_clicked()
{
    showAboutWidget();
}

void Clipboarder::on_listWidget_itemDoubleClicked(QListWidgetItem *item_)
{
    item *widget = map_item_bored.value(item_);
    setClipboardText(widget->getText());
}

void Clipboarder::on_pushButton_show_clicked()
{
    if(isHide)
        showWidget();
    else
        hideWidget();
}

void Clipboarder::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current)
        map_item_bored.value(current)->focusOn();
    if(previous)
        map_item_bored.value(previous)->focusLost();
}

void Clipboarder::on_listWidget_starList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if(current)
        map_item_starList.value(current)->focusOn();
    if(previous)
        map_item_starList.value(previous)->focusLost();
}
