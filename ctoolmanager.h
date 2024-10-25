#ifndef CTOOLMANAGER_H
#define CTOOLMANAGER_H

#include "Enums.h"
#include <QObject>


// Management class for the selected tool
// (based on the singleton design pattern)
class CToolManager : public QObject
{
    Q_OBJECT
public:
    static CToolManager* GetToolManager();

    void SetActiveTool(EnumTools tool);
    EnumTools GetActiveTool() const;
    bool IsActiveTool(EnumTools tool) const;

Q_SIGNALS:
    void ToolChanged();

protected:
    CToolManager();

private:
    static CToolManager* m_pSingletonInstance;

    // currently active tool
    EnumTools m_activeTool;
};

#endif // CTOOLMANAGER_H
