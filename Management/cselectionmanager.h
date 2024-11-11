#ifndef CSELECTIONMANAGER_H
#define CSELECTIONMANAGER_H

#include <QObject>
#include "../Misc/cselection.h"


// Management class for selections of image data
// (based on the singleton design pattern)
class CSelectionManager : public QObject
{
    Q_OBJECT
protected:
    explicit CSelectionManager();

public:
    static CSelectionManager* GetSelectionManager();

    bool HasSelection() const;
    const CSelection& GetSelection();

    void SetSelection(const CSelection& selection);
    void ResizeSelection(QRect rect);
    void ClearSelection();

Q_SIGNALS:
    void SelectionChanged();

private:
    static CSelectionManager* m_pSingletonInstance;
    CSelection m_selection;
};

#endif // CSELECTIONMANAGER_H
