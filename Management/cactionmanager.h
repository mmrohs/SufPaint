#ifndef CACTIONMANAGER_H
#define CACTIONMANAGER_H

#include <qaction.h>
#include "../Enums.h"


// Collection of all available QActions
// (based on the singleton design pattern)
class CActionManager : public QObject
{
    Q_OBJECT
protected:
    explicit CActionManager();

public:
    static CActionManager* GetActionManager();

    void AddAction(EnumActions e, QAction* pAction);
    void RemoveAction(EnumActions e);
    QAction* FindAction(EnumActions e);

public slots:
    // checks all actions and enables/disables
    // them if their requirements are (not) fulfilled
    void CheckAllActions();

private:
    void CheckAction(EnumActions e);
    void CheckAction(QAction* pAction, EnumActions e);

private:
    static CActionManager* m_pSingletonInstance;
    std::map<EnumActions, QAction*> m_actionMap;
};

#endif // CACTIONMANAGER_H
