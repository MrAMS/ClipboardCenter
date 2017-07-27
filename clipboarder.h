#ifndef CLIPBOARDER_H
#define CLIPBOARDER_H

#include <item.h>

#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListWidgetItem>
#include <QSizePolicy>
#include <QTimer>
#include <QMessageBox>
#include <QDesktopServices>
#include <QAction>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QDesktopWidget>

#include <QMap>
#include <QClipboard>
#include <QImage>
#include <QPixmap>
#include <QMap>
#include <QStringList>
#include <QVariant>
#include <QVariantList>
#include <QApplication>
#include <QDate>
#include <QDateTime>
#include <QSettings>
#include <QCryptographicHash>

namespace Ui {
class Clipboarder;
}

class Clipboarder : public QMainWindow
{
    Q_OBJECT

public:
    explicit Clipboarder(QWidget *parent = 0);
    ~Clipboarder();

private:
    Ui::Clipboarder *ui;
    QClipboard::Mode mode = QClipboard::Clipboard;
    QClipboard *board = QApplication::clipboard();
    QStringList list_clipboarde;
    QTimer *timer = new QTimer(this);
    QMap<QListWidgetItem*, item*> map_item_bored;
    QMenu *menu_tray = new QMenu(this);
    QMap<QListWidgetItem*, item*> map_item_starList;

    QSystemTrayIcon *system_tray = new QSystemTrayIcon(this);

    bool mMoveing;
    QPoint mMovePosition;
    int screen_center_x = 0;
    bool isHide=true;

    const QString baiduSearchAPI="http://www.baidu.com/s?wd=";


    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

protected:
     void closeEvent(QCloseEvent *event);

private slots:

    void hotKey_Ctrl1();
    void hotKey_Ctrl2();
    void hotKey_Ctrl3();
    void hotKey_Ctrl4();
    void hotKey_Ctrl5();

    void clipboardChanged(QClipboard::Mode mode_);

    void fRefresh();

    void setClipboardText(const QString &text);
    QString getClipboardText();

    void saveSettings();
    void loadSettings();
    void loadClipboardList(QClipboard::Mode mode_);
    void loadStarList();
    bool isStarText(QString text);

    void itemIsStarChanged_receiver(QString text, bool isStar_);
    void itemClicked_receiver(QString text);
    void itemCopy_receiver(QString text);
    void itemWebSearch_receiver(QString text);
    void itemDelete_receiver(QString text);
    void itemDelete_receiver_starList(QString text);


    void addItem(QString text, bool isStar, int key);
    void addItem_starList(QString text, int key);

    void showWidget();
    void hideWidget();
    void onTheTop();
    void disOnTheTop();
    void searchItem();
    void openUrl(QString url);
    void showAboutWidget();

    void createActions();

    void on_pushButton_toHistory_clicked();
    void on_pushButton_toStar_clicked();
    void on_pushButton_clicked();
    void on_pushButton_info_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item_);
    void on_pushButton_show_clicked();
    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_listWidget_starList_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
};

#endif // CLIPBOARDER_H
