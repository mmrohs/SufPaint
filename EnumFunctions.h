#ifndef ENUMFUNCTIONS_H
#define ENUMFUNCTIONS_H

#include <QString>
#include <QKeySequence>
#include <QIcon>
#include "Enums.h"

// Helpful functions for the enumerations in Enums.h

QString GetActionName(EnumActions e);
QKeySequence GetActionShortcut(EnumActions e);
QIcon GetActionIcon(EnumActions e);

//QString GetToolName(EnumTools e);
//QString GetToolTooltip(EnumTools e);
//QIcon GetToolIcon(EnumTools e);

#endif // ENUMFUNCTIONS_H
