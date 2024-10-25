#ifndef CTOOLBUTTON_H
#define CTOOLBUTTON_H

#include <QToolButton>
#include "../Enums.h"


class CToolButton : public QToolButton
{
public:
    explicit CToolButton(EnumTools tool, QWidget* parent = nullptr);

    void SetActive(bool bActive);
    bool IsActive() const;

public slots:
    void ToolChanged();

protected:
    virtual void paintEvent(QPaintEvent*) override;
    virtual void mousePressEvent(QMouseEvent *) override;

private:
    void SetIcon();
    void SetTooltip();

private:
    EnumTools m_tool;
    bool m_bActive;
};

#endif // CTOOLBUTTON_H
