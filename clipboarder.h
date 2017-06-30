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
    QTimer *timer_opTop = new QTimer(this);
    QMap<QListWidgetItem*, item*> map_item_bored;

    bool mMoveing;
    QPoint mMovePosition;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private slots:

    void hotKey_Ctrl1();
    void hotKey_Ctrl2();
    void hotKey_Ctrl3();
    void hotKey_Ctrl4();
    void hotKey_Ctrl5();

    void clipboardChanged(QClipboard::Mode mode_);

    void fRefresh();
    void fRefreshWindowOnTop();

    void setClipboardText(const QString &text);
    QString getClipboardText();

    void loadClipboardList(QClipboard::Mode mode_);
    void loadStarList();
    bool isStarText(QString text);
    void itemIsStarChanged_receiver(QString text, bool isStar_);
    void itemClicked_receiver(QString text);

    void addItem(QString text, QDateTime time, bool isStar, int key);
    void addItem(QString text, QDateTime time, int key);

    void openUrl(QString url);

    void on_pushButton_toHistory_clicked();
    void on_pushButton_toStar_clicked();
    void on_pushButton_clicked();
    void on_pushButton_info_clicked();
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item_);
};

#endif // CLIPBOARDER_H
