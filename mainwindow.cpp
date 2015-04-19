#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :  QMainWindow(parent),  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

void MainWindow::Progress(qint64 bytesSent, qint64 bytesTotal) {
    qreal n = (qreal)bytesSent/(qreal)bytesTotal;
   ui->progressBar->setValue(n * 100);
    qDebug() << "Uploaded " << bytesSent << " of " << bytesTotal;
}

void MainWindow::uploadDone() {
    qDebug() << "Finished" << reply->errorString() << reply->attribute( QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << reply->readAll();
    reply->deleteLater();
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart textPart;
    textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"text\""));
    textPart.setBody("my text");

    QHttpPart imagePart;
    imagePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("image/jpeg"));
    imagePart.setHeader(QNetworkRequest::ContentDispositionHeader,
                        QVariant("form-data; name=\"userImage\";  filename=\"muhammad.jpg\""));
    QFile *file = new QFile("C:/Users/bou/Desktop/gold-floral-content(1).jpg");
    file->open(QIODevice::ReadOnly);
    imagePart.setBodyDevice(file);
    file->setParent(multiPart);

    //multiPart->append(textPart);
    multiPart->append(imagePart);

    QUrl url("http://maahad.net/web/upload/upload.php");
    QNetworkRequest request(url);

    QNetworkAccessManager * manager = new QNetworkAccessManager();
    reply = manager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(reply, SIGNAL(uploadProgress(qint64,qint64)), this, SLOT(Progress(qint64,qint64)));
    connect(reply, SIGNAL(finished()), this, SLOT(uploadDone()));

}
