#include "cadjustmentmenu.h"
#include "../cactionmanager.h"
#include "../cimagemanager.h"


CAdjustmentMenu::CAdjustmentMenu(const QString& title, QWidget* parent)
    : CMenuBase(title, parent)
{
    m_pImageManager = CImageManager::GetImageManager();

    AddActions();
    AddConnections();
}

void CAdjustmentMenu::AddActions()
{
    AddActionToMenu(ActionAdjustInvert);
    AddActionToMenu(ActionAdjustGrayscale);
    AddActionToMenu(ActionAdjustSepia);
}

void CAdjustmentMenu::AddConnections()
{
    ConnectAction(ActionAdjustInvert, &CAdjustmentMenu::InvertColors);
    ConnectAction(ActionAdjustGrayscale, &CAdjustmentMenu::Grayscale);
    ConnectAction(ActionAdjustSepia, &CAdjustmentMenu::Sepia);
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
