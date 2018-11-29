/**
  @brief This class takes a given QQuickWidget and displays an image given the absolute path
  @author Stacey Gunderson, Alison Lee
  **/

#ifndef IMAGE_H
#define IMAGE_H

#include <QQuickWidget>
#include <QLabel>
#include <QCoreApplication>
#include <QObject>

/**
 @brief The image class displays an image using a QLabel
 @author Stacey Gunderson, Alison Lee
 **/
class image : public QObject
{
    Q_OBJECT
private:
    QLabel* label;

public:
    explicit image(QQuickWidget *parent = nullptr);

public slots:
    void update();
};

#endif // IMAGE_H
