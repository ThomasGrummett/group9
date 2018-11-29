/**
  @brief This class takes a given QQuickWidget and displays an image given the absolute path. Will update on a change in picturename
  @author Stacey Gunderson, Alison Lee
  */

#include "image.h"
#include "picturename.h"

/**
  @brief This class takes a given QQuickWidget and sets up a label to call an image refresh to load the picture name
  @author Stacey Gunderson, Alison Lee
  **/
image::image(QQuickWidget *parent)
{
    //Creates and sets alignment of the label image to center
    image::label = new QLabel(parent);
    label->setAlignment(Qt::AlignTop);
    label->resize(500,500);
    picturename::instance().add_observer(this);

    image::update();
}

/**
 * @brief Loads the image name in the singleton class picturename to the widget's label and displays the image or an error if no image exists
 * @author Stacey Gunderson, Alison Lee
 */
void image::update()
{
    picturename::instance();
    QString name = picturename::instance().get_picture();
    QString link = "://" + name +".jpg";
    QImage* thing = new QImage(link);

    //Checks if the object exists and if not tries to load the image as a png
    //.jpg is used if both .jpg and .png exist
    if (thing->isNull()) {

        //Quick fix for if the image is a png and not jpg
        QString link = "://" + name +".png";
        QImage* thing = new QImage(link);
        if (thing->isNull())
        {
            //If neither png or jpg exits, then simply set an error message
            label->setText("Image not found");
        }
        else
        {
            //Scales the image to fit the label without breaking the aspect ratio
            QPixmap pix = QPixmap::fromImage(*thing);
            pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
            label->setPixmap(pix);
        }
    }
    else
    {
        //Scales the image to fit the label without breaking the aspect ratio
        QPixmap pix = QPixmap::fromImage(*thing);
        pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
        label->setPixmap(pix);
    }

    label->show();
}

//No longer needed with resource.qrc
//QCoreApplication::applicationDirPath(); Potentially useful to implement relative path if it was the same directory
//filename = filename + "rain.jpg";
/*
if(pix.load(filename))
{
    //Scales the image to fit within the size of label while keeping aspect ratio
    pix = pix.scaled(label->size(),Qt::KeepAspectRatio);
    label->setPixmap(pix);
    //---------------------------------------

}
else //Error displayed to the widget if it failed to find image
{
    label->setText(filename);
} */
