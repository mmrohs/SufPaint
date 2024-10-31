#ifndef CIMAGEPROCESSOR_H
#define CIMAGEPROCESSOR_H

#include <QImage>


/* The color pattern image for CColorPaletteWidget
*/
class CColorPatternImage : public QImage
{
public:
    explicit CColorPatternImage(QSize size);
    explicit CColorPatternImage(int width, int height);

    QColor GetColorFromPos(int x, int y) const;
    QColor GetColorFromPos(QPointF pos) const;

private:
    void GeneratePatternImage();

    int CalcRed(QPointF pos) const;
    int CalcGreen(QPointF pos) const;
    int CalcBlue(QPointF pos) const;
    int CalcColor(QPointF pos, double rgbOffset) const;

    friend class CColorPaletteWidget;
};

#endif // CIMAGEPROCESSOR_H
