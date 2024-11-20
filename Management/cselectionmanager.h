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
    CSelection* GetSelection();

    void SetSelection(CSelection* pSelection);
    void ClearSelection();

Q_SIGNALS:
    void SelectionChanged();

public slots:
    void ImagePropertiesChanged();

private:
    static CSelectionManager* m_pSingletonInstance;
    CSelection* m_pSelection;
};

#endif // CSELECTIONMANAGER_H
