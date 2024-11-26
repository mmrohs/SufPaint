#include "cadjustmentmenu.h"
#include "../Management/cactionmanager.h"
#include "../Management/cimagemanager.h"


CAdjustmentMenu::CAdjustmentMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CAdjustmentMenu::AddActions()
{
    AddActionToMenu(AdjustInvert);
    AddActionToMenu(AdjustGrayscale);
    AddActionToMenu(AdjustSepia);
}

void CAdjustmentMenu::AddConnections()
{
    ConnectAction(AdjustInvert, &CAdjustmentMenu::InvertColors);
    ConnectAction(AdjustGrayscale, &CAdjustmentMenu::Grayscale);
    ConnectAction(AdjustSepia, &CAdjustmentMenu::Sepia);
}

template<typename func>
void CAdjustmentMenu::ConnectAction(EnumActions e, func&& slot)
{
    CActionManager* pActionManager = CActionManager::GetActionManager();
    if (pActionManager != NULL)
    {
        QAction* pAction = pActionManager->FindAction(e);
        if (pAction != NULL)
        {
            connect(pAction, &QAction::triggered, this, slot);
        }
    }
}

void CAdjustmentMenu::InvertColors()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->InvertColors();
    }
}

void CAdjustmentMenu::Grayscale()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->Grayscale();
    }
}

void CAdjustmentMenu::Sepia()
{
    if (m_pImageManager != NULL)
    {
        m_pImageManager->Sepia();
    }
}
