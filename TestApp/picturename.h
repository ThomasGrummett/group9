/**
  @brief A singleton design that holds a single given QString object for a picture name
  @author Stacey Gunderson, Alison Lee
 */

#ifndef PICTURENAME_H
#define PICTURENAME_H
#include <QString>
#include <QObject>
#include <QList>
#include "image.h"

class picturename : private QObject
{
    Q_OBJECT
private:
    QString picturelink;
    picturename(picturename& other){};
    picturename& operator=(picturename& other){};
    static picturename* _instance;
    QList<image*> observers;

public:
    static picturename& instance();
    QString get_picture();
    void add_observer(image*);
    void remove_observer(image*);
    void set_picture(QString);

signals:
    void notify();

protected:
    picturename();

};

#endif // PICTURENAME_H
