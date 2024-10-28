#include "ccanvasresizedialog.h"
#include "ui_ccanvasresizedialog.h"
#include <qboxlayout>
#include <QGroupBox>
#include <QRadioButton>
#include <QSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QComboBox>


CCanvasResizeDialog::CCanvasResizeDialog(QWidget* pParent, QSize origSize)
    : QDialog(pParent)
    , ui(new Ui::CCanvasResizeDialog), m_origSize(origSize),
    m_pRadioPixel(NULL), m_pRadioPercent(NULL), m_pChkAspRatio(NULL),
    m_pSpinWidth(NULL), m_pSpinHeight(NULL), m_pComboAnchor(NULL)
{
    ui->setupUi(this);
    Init();
}

CCanvasResizeDialog::~CCanvasResizeDialog()
{
    delete ui;
}

QSize CCanvasResizeDialog::GetNewSize() const
{
    QSize newSize(1,1);
    if (m_pRadioPercent->isChecked()) // percent mode
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

EnumAnchors CCanvasResizeDialog::GetAnchor() const
{
    EnumAnchors anchor = EnumAnchors::Invalid;
    if (m_pComboAnchor != NULL)
    {
        anchor = (EnumAnchors)m_pComboAnchor->currentIndex();
    }
    return anchor;
}

void CCanvasResizeDialog::Init()
{
    AddLayout();

    m_aspectRatio = (double)m_origSize.width() / (double)m_origSize.height();
    m_pSpinWidth->setValue(m_origSize.width());
    m_pSpinHeight->setValue(m_origSize.height());

    AddConnections();
    FillCombobox();
}

void CCanvasResizeDialog::AddLayout()
{
    // Layout of Groupbox "Mode"
    QHBoxLayout* hlayout = new QHBoxLayout(this);
    m_pRadioPixel = new QRadioButton(tr("Pixel"), this);
    m_pRadioPixel->setChecked(Qt::CheckState::Checked);
    m_pRadioPercent = new QRadioButton(tr("Percent"), this);
    hlayout->addWidget(m_pRadioPixel);
    hlayout->addWidget(m_pRadioPercent);
    hlayout->setStretchFactor(m_pRadioPixel, 10);
    hlayout->setStretchFactor(m_pRadioPercent, 30);

    // Groupbox "Mode"
    QGroupBox* pGBoxMode = new QGroupBox(tr("Mode"), this);
    pGBoxMode->setLayout(hlayout);

    // Layout of Groupbox "New Size"
    QGridLayout* gridLayout = new QGridLayout(this);
    // 1st row
    int row = 0, column = 0;
    QLabel* pLabelWidth = new QLabel(tr("Width:"), this);
    m_pSpinWidth = new QSpinBox(this);
    m_pSpinWidth->setRange(1, 10000);
    gridLayout->addWidget(pLabelWidth, row, column++, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    gridLayout->addWidget(m_pSpinWidth, row, column++);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    // 2nd row
    row++; column = 0;
    QLabel* pLabelHeight = new QLabel(tr("Height:"), this);
    m_pSpinHeight = new QSpinBox(this);
    m_pSpinHeight->setRange(1, 10000);
    gridLayout->addWidget(pLabelHeight, row, column++, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    gridLayout->addWidget(m_pSpinHeight, row, column++);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    // stretching
    gridLayout->setColumnStretch(0, 30);
    gridLayout->setColumnStretch(1, 5);
    gridLayout->setColumnStretch(2, 30);
    gridLayout->setColumnStretch(3, 30);

    // Groupbox "New Size"
    QGroupBox* pGBoxValues = new QGroupBox(tr("New size"), this);
    pGBoxValues->setLayout(gridLayout);

    // Layout of Groupbox "Options"
    QVBoxLayout* vLayoutOpt = new QVBoxLayout(this);
    // 1st row
    m_pChkAspRatio = new QCheckBox(tr("Fixed aspect ratio"), this);
    m_pChkAspRatio->setCheckState(Qt::CheckState::Checked);
    vLayoutOpt->addWidget(m_pChkAspRatio);
    // 2nd row
    QHBoxLayout* hLayoutOpt = new QHBoxLayout();
    QLabel* pLabelAnchor = new QLabel(tr("Anchor:"), this);
    m_pComboAnchor = new QComboBox(this);
    hLayoutOpt->addWidget(pLabelAnchor, 35, Qt::AlignRight);
    hLayoutOpt->addStretch(5);
    hLayoutOpt->addWidget(m_pComboAnchor, 30);
    hLayoutOpt->addStretch(30);
    // merge layouts
    vLayoutOpt->addLayout(hLayoutOpt);

    // Groupbox "Options"
    QGroupBox* pGBoxOptions = new QGroupBox(tr("Options"), this);
    pGBoxOptions->setLayout(vLayoutOpt);

    // Dialog-Layout
    QVBoxLayout* vlayout = ui->verticalLayout;
    vlayout->addWidget(pGBoxMode);
    vlayout->addWidget(pGBoxValues);
    vlayout->addWidget(pGBoxOptions);
}

void CCanvasResizeDialog::AddConnections()
{
    connect(m_pRadioPixel, &QAbstractButton::clicked, this, &CCanvasResizeDialog::ChangedToPixelMode);
    connect(m_pRadioPercent, &QAbstractButton::clicked, this, &CCanvasResizeDialog::ChangedToPercentMode);
    connect(m_pSpinWidth, &QSpinBox::valueChanged, this, &CCanvasResizeDialog::ChangedWidth);
    connect(m_pSpinHeight, &QSpinBox::valueChanged, this, &CCanvasResizeDialog::ChangedHeight);
    connect(m_pChkAspRatio, &QCheckBox::checkStateChanged, this, &CCanvasResizeDialog::ChangedOptionAR);
}

void CCanvasResizeDialog::FillCombobox()
{
    if (m_pComboAnchor != NULL && m_pComboAnchor->count() == 0)
    {
        m_pComboAnchor->insertItem(EnumAnchors::Center,     "Center");
        m_pComboAnchor->insertItem(EnumAnchors::TopLeft,    "TopLeft");
        m_pComboAnchor->insertItem(EnumAnchors::Top,        "Top");
        m_pComboAnchor->insertItem(EnumAnchors::TopRight,   "TopRight");
        m_pComboAnchor->insertItem(EnumAnchors::Right,      "Right");
        m_pComboAnchor->insertItem(EnumAnchors::BottomRight,"BottomRight");
        m_pComboAnchor->insertItem(EnumAnchors::Bottom,     "Bottom");
        m_pComboAnchor->insertItem(EnumAnchors::BottomLeft, "BottomLeft");
        m_pComboAnchor->insertItem(EnumAnchors::Left,       "Left");
    }
}

void CCanvasResizeDialog::ChangedWidth(int width)
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

void CCanvasResizeDialog::ChangedHeight(int height)
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

void CCanvasResizeDialog::ChangedToPixelMode(bool checked)
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

void CCanvasResizeDialog::ChangedToPercentMode(bool checked)
{
    if (checked)
    {
        m_pSpinWidth->setValue(100.0 * m_pSpinWidth->value() / m_origSize.width());
        m_pChkAspRatio->setEnabled(false);
        m_pChkAspRatio->setCheckState(Qt::CheckState::Unchecked);
    }
}

void CCanvasResizeDialog::ChangedOptionAR(Qt::CheckState state)
{
    if (state == Qt::CheckState::Checked)
    {
        m_pSpinWidth->setValue(m_pSpinWidth->value());
    }
}

