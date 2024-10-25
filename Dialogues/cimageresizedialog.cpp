#include "cimageresizedialog.h"
#include "ui_cimageresizedialog.h"
#include <qboxlayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinbox>
#include <QLabel>
#include <QSpacerItem>
#include <QCheckBox>


CImageResizeDialog::CImageResizeDialog(QWidget* pParent, QSize origSize)
    : QDialog(pParent),
    ui(new Ui::CImageResizeDialog), m_origSize(origSize),
    m_pRadioPixel(NULL), m_pRadioPercent(NULL), m_pChkAspRatio(NULL),
    m_pSpinWidth(NULL), m_pSpinHeight(NULL)
{
    ui->setupUi(this);
    ui->buttonBox->setWindowTitle(tr("Resize Image"));

    Init();
}

CImageResizeDialog::~CImageResizeDialog()
{
    delete ui;
}

QSize CImageResizeDialog::GetNewSize() const
{
    QSize newSize(1,1);
    if (m_pRadioPercent->isChecked())
    {
        double factor = m_pSpinWidth->value() / 100.0;
        newSize = QSize(factor * m_origSize.width(), factor * m_origSize.height());
    }
    else // pixel mode
    {
        newSize = QSize(m_pSpinWidth->value(), m_pSpinHeight->value());
    }
    return newSize;
}

void CImageResizeDialog::Init()
{
    AddLayout();

    m_aspectRatio = (double)m_origSize.width() / (double)m_origSize.height();
    m_pSpinWidth->setValue(m_origSize.width());
    m_pSpinHeight->setValue(m_origSize.height());

    AddConnections();
}

void CImageResizeDialog::AddLayout()
{
    // Groupbox "Mode"
    QGroupBox* pGBoxMode = new QGroupBox(tr("Mode"), this);
    QHBoxLayout* hlayout = new QHBoxLayout(this);
    m_pRadioPixel = new QRadioButton(tr("Pixel"), this);
    m_pRadioPixel->setChecked(Qt::CheckState::Checked);
    m_pRadioPercent = new QRadioButton(tr("Percent"), this);
    hlayout->addWidget(m_pRadioPixel);
    hlayout->addWidget(m_pRadioPercent);
    hlayout->setStretchFactor(m_pRadioPixel, 10);
    hlayout->setStretchFactor(m_pRadioPercent, 30);
    pGBoxMode->setLayout(hlayout);

    // Groupbox "New Size"
    QGroupBox* pGBoxValues = new QGroupBox(tr("New size"), this);
    QGridLayout* gridLayout = new QGridLayout(this);
    // 1st row
    QLabel* pLabelWidth = new QLabel(tr("Width:"), this);
    m_pSpinWidth = new QSpinBox(this);
    m_pSpinWidth->setRange(1, 10000);
    gridLayout->addWidget(pLabelWidth, 0, 0, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), 0, 1);
    gridLayout->addWidget(m_pSpinWidth, 0, 2);
    gridLayout->addItem(new QSpacerItem(1, 1), 0, 3);
    // 2nd row
    QLabel* pLabelHeight = new QLabel(tr("Height:"), this);
    m_pSpinHeight = new QSpinBox(this);
    m_pSpinHeight->setRange(1, 10000);
    gridLayout->addWidget(pLabelHeight, 1, 0, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), 1, 1);
    gridLayout->addWidget(m_pSpinHeight, 1, 2);
    gridLayout->addItem(new QSpacerItem(1, 1), 1, 3);
    // stretching
    gridLayout->setColumnStretch(0, 30);
    gridLayout->setColumnStretch(1, 5);
    gridLayout->setColumnStretch(2, 30);
    gridLayout->setColumnStretch(3, 30);
    pGBoxValues->setLayout(gridLayout);

    // Groupbox "Options"
    QGroupBox* pGBoxOptions = new QGroupBox(tr("Options"), this);
    QVBoxLayout* vOptLayout = new QVBoxLayout(this);
    m_pChkAspRatio = new QCheckBox(tr("Fixed aspect ratio"), this);
    m_pChkAspRatio->setCheckState(Qt::CheckState::Checked);
    vOptLayout->addWidget(m_pChkAspRatio);
    pGBoxOptions->setLayout(vOptLayout);

    // Layout
    QVBoxLayout* vlayout = ui->verticalLayout;
    vlayout->addWidget(pGBoxMode);
    vlayout->addWidget(pGBoxValues);
    vlayout->addWidget(pGBoxOptions);
}

void CImageResizeDialog::AddConnections()
{
    connect(m_pRadioPixel, &QAbstractButton::clicked, this, &CImageResizeDialog::ChangedToPixelMode);
    connect(m_pRadioPercent, &QAbstractButton::clicked, this, &CImageResizeDialog::ChangedToPercentMode);
    connect(m_pSpinWidth, &QSpinBox::valueChanged, this, &CImageResizeDialog::ChangedWidth);
    connect(m_pSpinHeight, &QSpinBox::valueChanged, this, &CImageResizeDialog::ChangedHeight);
    connect(m_pChkAspRatio, &QCheckBox::checkStateChanged, this, &CImageResizeDialog::ChangedOptionAR);
}

void CImageResizeDialog::ChangedWidth(int width)
{
    if (m_pRadioPercent->isChecked())
    {
        QSignalBlocker blocked(m_pSpinHeight);
        m_pSpinHeight->setValue(width);
    }
    else if (m_pChkAspRatio->checkState() == Qt::CheckState::Checked)
    {
        QSignalBlocker blocked(m_pSpinHeight);
        m_pSpinHeight->setValue(width / m_aspectRatio);
    }
}

void CImageResizeDialog::ChangedHeight(int height)
{
    if (m_pRadioPercent->isChecked())
    {
        QSignalBlocker blocked(m_pSpinWidth);
        m_pSpinWidth->setValue(height);
    }
    else if (m_pChkAspRatio->checkState() == Qt::CheckState::Checked)
    {
        QSignalBlocker blocked(m_pSpinWidth);
        m_pSpinWidth->setValue(height * m_aspectRatio);
    }
}

void CImageResizeDialog::ChangedToPixelMode(bool checked)
{
    if (checked)
    {
        QSignalBlocker blockedW(m_pSpinWidth);
        QSignalBlocker blockedH(m_pSpinHeight);
        double factor = m_pSpinWidth->value() / 100.0;
        m_pSpinWidth->setValue(factor * m_origSize.width());
        m_pSpinHeight->setValue(factor * m_origSize.height());
        m_pChkAspRatio->setEnabled(true);
        m_pChkAspRatio->setCheckState(Qt::CheckState::Checked);
    }
}

void CImageResizeDialog::ChangedToPercentMode(bool checked)
{
    if (checked)
    {
        m_pSpinWidth->setValue(100.0 * m_pSpinWidth->value() / m_origSize.width());
        m_pChkAspRatio->setEnabled(false);
        m_pChkAspRatio->setCheckState(Qt::CheckState::Unchecked);
    }
}

void CImageResizeDialog::ChangedOptionAR(Qt::CheckState state)
{
    if (state == Qt::CheckState::Checked)
    {
        m_pSpinWidth->setValue(m_pSpinWidth->value());
    }
}
