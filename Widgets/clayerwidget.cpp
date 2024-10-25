#include "clayerwidget.h"

CLayerWidget::CLayerWidget(QWidget* pParent)
    : QGroupBox(tr("Layers"), pParent)
{
    setMinimumWidth(150);
    setMaximumWidth(150);
}
