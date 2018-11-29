/**
  @brief A singleton design that holds a single given QString object for a picture name
  @author Stacey Gunderson, Alison Lee
 */

#include "picturename.h"

picturename* picturename::_instance = NULL;

/**
   @brief Returns a pointer to a singleton instance of picturename, creates one if it does not exist
   @author Stacey Gunderson, Alison Lee
   @return the pointer to the instance of picturename
 */
picturename& picturename::instance()
{
    if (_instance == NULL)
    {
        _instance = new picturename();
    }
    return *_instance;
}


/**
   @brief Creates an instance of picturename, set aurora as default image
   @author Stacey Gunderson, Alison Lee
 */
picturename::picturename()
{
    this->set_picture("aurora");
}


/**
   @brief Sets the QString for the picture name to the given QString and notifies observers
   @author Stacey Gunderson, Alison Lee
 */
void picturename::set_picture(QString link)
{
    this->picturelink = link;
    emit notify();
}

/**
   @brief Adds an observer to the list, and creates a signal connection
   @author Stacey Gunderson, Alison Lee
 */
void picturename::add_observer(image* obj)
{
    this->observers.append(obj);
    QObject::connect(this, SIGNAL(notify()), obj, SLOT(update()));
}

/**
   @brief Removes an observer from the list
   @author Stacey Gunderson, Alison Lee
 */
void picturename::remove_observer(image* obj)
{
    QObject::disconnect(this, SIGNAL(notify()), obj, SLOT(update()));
    this->observers.removeOne(obj);
}

/**
   @brief Returns the QString with the name of the picture
   @author Stacey Gunderson, Alison Lee
 */
QString picturename::get_picture()
{
    return this->picturelink;
}
