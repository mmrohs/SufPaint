#include "cgradienttool.h"
#include "../Management/ccolormanager.h"
#include "../Management/cimagemanager.h"
#include "../Management/cselectionmanager.h"


CGradientTool::CGradientTool()
    : CTool(EnumTools::ToolGradient)
{
}

/*virtual*/ QIcon CGradientTool::GetToolIcon() const
{
    QIcon icon("Icons/Gradient.png");
    icon.addFile("Icons/Gradient_Disabled.png", QSize(), QIcon::Mode::Disabled);
    return icon;
}

/*virtual*/ QString CGradientTool::GetToolName() const
{
    return "Color Gradient";
}

/*virtual*/ QString CGradientTool::GetTooltip() const
{
    return "Fill areas with a color gradient";
}

/*virtual*/ void CGradientTool::ProcessMouseLPressEvent(QMouseEvent* pEvent)
{
    m_startPos = GetImagePos(pEvent, false);
}

/*virtual*/ void CGradientTool::ProcessMouseLReleaseEvent(QMouseEvent* pEvent)
{
    m_endPos = GetImagePos(pEvent, false);
    ApplyGradient();
    CImageManager::GetImageManager()->SendImagePixelsUpdate();
}

/*virtual*/ void CGradientTool::ProcessMouseLMoveEvent(QMouseEvent* pEvent)
{
    ProcessMouseLReleaseEvent(pEvent);
}

void CGradientTool::ApplyGradient()
{
    QImage* pImage = GetImage();
    if (pImage == NULL)
        return;

    InitColors();
    InitVectors();

    CSelection* pSelection = CSelectionManager::GetSelectionManager()->GetSelection();

    for (int y = 0; y < pImage->height(); ++y)
    {
        QRgb* line = reinterpret_cast<QRgb*>(pImage->scanLine(y));
        for (int x = 0; x < pImage->width(); ++x)
        {
            QPoint pos(x, y);
            if (pSelection != NULL && !pSelection->Contains(pos))
                continue;

            line[x] = CalculateColor(pos);
        }
    }
}

QRgb CGradientTool::CalculateColor(QPointF pos)
{
    // Position between Pixel and starting position
    QPointF p = pos - m_startPos;

    // dot product to determine the distance
    qreal dp = QPointF::dotProduct(p, m_diffPos) * m_invDiffLength;

    QRgb color;
    if (dp <= 0)
    {
        color = m_startColor.rgba();
    }
    else if (dp >= m_diffLength)
    {
        color = m_endColor.rgba();
    }
    else
    {
        int r,g,b,a;
        qreal div = dp * m_invDiffLength;
        r = m_startColor.red() + m_diffColor.red() * div;
        g = m_startColor.green() + m_diffColor.green() * div;
        b = m_startColor.blue() + m_diffColor.blue() * div;
        a = 255;
        color = qRgba(r,g,b,a);
    }
    return color;
}

void CGradientTool::InitColors()
{
    // get the colors
    CColorManager* pColorManager = CColorManager::GetColorManager();
    m_startColor = pColorManager->GetForegroundColor();
    m_endColor = pColorManager->GetBackgroundColor();

    // get the color difference
    m_diffColor.setRed( m_endColor.red() - m_startColor.red() );
    m_diffColor.setGreen( m_endColor.green() - m_startColor.green() );
    m_diffColor.setBlue( m_endColor.blue() - m_startColor.blue() );
}

void CGradientTool::InitVectors()
{
    // vector from startPos to endPos
    m_diffPos = m_endPos - m_startPos;
    m_diffLength = sqrt(m_diffPos.x() * m_diffPos.x() + m_diffPos.y() * m_diffPos.y());
    m_invDiffLength = 1.0 / m_diffLength;
}
