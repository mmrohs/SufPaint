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

    QColor GetColorFromPos(QPoint pos);

private:
    void GeneratePatternImage();
    int CalcRed(int x, int y) const;
    int CalcGreen(int x, int y) const;
    int CalcBlue(int x, int y) const;
};

#endif // CIMAGEPROCESSOR_H
