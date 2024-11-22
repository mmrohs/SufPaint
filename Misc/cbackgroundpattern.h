#ifndef CBACKGROUNDPATTERN_H
#define CBACKGROUNDPATTERN_H

#include <QObject>
#include <QPixmap>


/* class for drawing the background pattern begind the image
*/
class CBackgroundPattern
{
public:
    CBackgroundPattern();

    void Draw(class QPainter&) const;

private:
    void InitPixmap();

private:
    QPixmap m_tile;
};

#endif // CBACKGROUNDPATTERN_H
