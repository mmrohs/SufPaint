#include "cselection.h"

CSelection::CSelection()
    : m_type(SelectionType::NONE)
{
}

void CSelection::Clear()
{
    m_type = SelectionType::NONE;
    m_rect = QRect();
}

bool CSelection::IsValid() const
{
    return m_type != SelectionType::NONE;
}

QRect CSelection::GetRect() const
{
    return m_rect;
}

void CSelection::SetRectangleSelection(QRect rect)
{
    m_type = SelectionType::RECTANGLE;
    m_rect = rect;
}

void CSelection::SetEllipticSelection(QRect rect)
{
    m_type = SelectionType::ELLIPSE;
    m_rect = rect;
}

void CSelection::SetCustomSelection()
{
    m_type = SelectionType::CUSTOM;
    // to do
}

void CSelection::Resize(QRect rect)
{
    m_rect = rect;
}

