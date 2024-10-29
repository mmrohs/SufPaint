#ifndef CIMAGEPROCESSOR_H
#define CIMAGEPROCESSOR_H

#include <QImage>


/* The color pattern image for CColorPaletteWidget
*/
class CColorPatternImage : public QImage
{
public:
    CColorPatternImage(QSize size);
    CColorPatternImage(int width, int height);

    QColor GetColorFromPos(QPointF pos);

private:
    void GeneratePatternImage();
    int CalcRed(double x, double y) const;
    int CalcGreen(double x, double y) const;
    int CalcBlue(double x, double y) const;
};

#endif // CIMAGEPROCESSOR_H
