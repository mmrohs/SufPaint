#ifndef CTOOLMANAGER_H
#define CTOOLMANAGER_H

#include <QObject>
#include "../Enums.h"
#include "../Tools/ctool.h"


// Management class for the selected tool
// (based on the singleton design pattern)
class CToolManager : public QObject
{
    Q_OBJECT
protected:
    explicit CToolManager();

public:
    static CToolManager* GetToolManager();

    CTool* GetActiveTool();
    EnumTools GetActiveToolEnum() const;

    void SetActiveTool(EnumTools tool);
    bool IsActiveTool(EnumTools tool) const;

Q_SIGNALS:
    void ToolChanged();

private:
    void CreateTool();

private:
    static CToolManager* m_pSingletonInstance;

    // currently active tool
    CTool*    m_pTool;
    EnumTools m_activeTool;
};

#endif // CTOOLMANAGER_H
