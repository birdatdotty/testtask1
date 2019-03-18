//https://doc.qt.io/qt-5/qtwidgets-draganddrop-dropsite-example.html

#ifndef DROPBOX_H
#define DROPBOX_H

#include <QWidget>
#include <QLabel>

class DropBox : public QLabel
{
  Q_OBJECT
public:
  explicit DropBox(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:

public slots:
};

#endif // DROPBOX_H
