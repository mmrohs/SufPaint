#ifndef CSELECTION_H
#define CSELECTION_H

#include <QRect>


/* class describes a user defined selection of the image
*/
class CSelection
{
    enum SelectionType { NONE, RECTANGLE, ELLIPSE, CUSTOM };
public:
    explicit CSelection();

    bool IsValid() const;
    QRect GetRect() const;

    void SetRectangleSelection(QRect rect);
    void SetEllipticSelection(QRect rect);
    void SetCustomSelection();

    void Resize(QRect rect);

    void Clear();
private:
    SelectionType m_type;
    QRect m_rect;
};

#endif // CSELECTION_H
