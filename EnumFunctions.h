#ifndef ENUMFUNCTIONS_H
#define ENUMFUNCTIONS_H

#include <QString>
#include <QKeySequence>
#include <QIcon>
#include "Enums.h"
#include "Tools/ctool.h"


// Helpful functions for the enumerations in Enums.h

QString GetActionName(EnumActions action);
QKeySequence GetActionShortcut(EnumActions action);
QIcon GetActionIcon(EnumActions action);

CTool* GetNewTool(EnumTools tool);
QString GetToolName(EnumTools tool);
QString GetTooltip(EnumTools tool);
QIcon GetToolIcon(EnumTools tool);

#endif // ENUMFUNCTIONS_H
