#ifndef CIMAGEPROCESSOR_H
#define CIMAGEPROCESSOR_H

#include <QImage>


/* The color pattern image for CColorPaletteWidget
*/
class CColorPatternImage : public QImage
{
    enum Mode { Dark, Light };
public:
    explicit CColorPatternImage(QSize size, Mode mode = Dark);
    explicit CColorPatternImage(int width, int height, Mode mode = Dark);

    QColor GetColorFromPos(int x, int y) const;
    QColor GetColorFromPos(QPointF pos) const;

private:
    void GeneratePatternImage();
    int CalcRed(QPointF pos) const;
    int CalcGreen(QPointF pos) const;
    int CalcBlue(QPointF pos) const;

    void SetMode(Mode mode);
    void SetStep();

private:
    Mode m_mode;
    double m_step; // step width of the color gradient


    friend class CColorPaletteWidget;
};

#endif // CIMAGEPROCESSOR_H
