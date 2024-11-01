#include "ccolormanager.h"


/*static*/ CColorManager* CColorManager::m_pSingletonInstance = NULL;

CColorManager::CColorManager()
    : m_foregroundColor(Qt::black), m_backgroundColor(Qt::white)
{
}

/*static*/ CColorManager* CColorManager::GetColorManager()
{
    if (m_pSingletonInstance == NULL)
    {
        m_pSingletonInstance = new CColorManager();
    }
    return m_pSingletonInstance;
}

QColor CColorManager::GetForegroundColor() const
{
    return m_foregroundColor;
}

QColor CColorManager::GetBackgroundColor() const
{
    return m_backgroundColor;
}

void CColorManager::SetForegroundColor(QColor color, bool bIgnoreAlpha /*= false*/)
{
    if (bIgnoreAlpha)
        color.setAlpha(m_foregroundColor.alpha());

    bool bChange = m_foregroundColor != color;
    m_foregroundColor = color;
    if (bChange)
        emit ColorUpdate();
}

void CColorManager::SetBackgroundColor(QColor color, bool bIgnoreAlpha /*= false*/)
{
    if (bIgnoreAlpha)
        color.setAlpha(m_backgroundColor.alpha());

    bool bChange = m_backgroundColor != color;
    m_backgroundColor = color;
    if (bChange)
        emit ColorUpdate();
}

void CColorManager::SwitchColors()
{
    QColor foregroundColor = m_foregroundColor;
    m_foregroundColor = m_backgroundColor;
    m_backgroundColor = foregroundColor;
    emit ColorUpdate();
}
