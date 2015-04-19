#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHttpMultiPart>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QFile>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void Progress(qint64 bytesSent, qint64 bytesTotal);
    void uploadDone();

private:
    Ui::MainWindow *ui;
    QNetworkReply * reply;
};

#endif // MAINWINDOW_H
