#include "cnewimagedialog.h"
#include "ui_cnewimagedialog.h"
#include <QGroupBox>
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>
#include <QPainter>


CNewImageDialog::CNewImageDialog(QWidget* pParent)
    : QDialog(pParent),
    ui(new Ui::CNewImageDialog),
    m_pSpinWidth(NULL), m_pSpinHeight(NULL), m_pComboTemplates(NULL)
{
    ui->setupUi(this);
    Init();
}

CNewImageDialog::~CNewImageDialog()
{
    delete ui;
}

int CNewImageDialog::GetWidth() const
{
    return m_pSpinWidth->value();
}

int CNewImageDialog::GetHeight() const
{
    return m_pSpinHeight->value();
}

void CNewImageDialog::Init()
{
    AddLayout();
    AddConnections();
    FillCombobox();
}

void CNewImageDialog::AddLayout()
{
    // Gridlayout for Groupbox "Image Size"
    QGridLayout* gridLayout = new QGridLayout(this);
    // 1st row
    int row = 0, column = 0;
    m_pComboTemplates = new QComboBox(this);
    gridLayout->addWidget(new QLabel(tr("Template:"), this), row, column++, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    gridLayout->addWidget(m_pComboTemplates, row, column++);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    // 2nd row
    row++; column = 0;
    m_pSpinWidth = new QSpinBox(this);
    m_pSpinWidth->setRange(1, 10000);
    gridLayout->addWidget(new QLabel(tr("Width:"), this), row, column++, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    gridLayout->addWidget(m_pSpinWidth, row, column++);
    gridLayout->addWidget(new QLabel(tr(" Pixel"), this), row, column++);
    // 3rd row
    row++; column = 0;
    m_pSpinHeight = new QSpinBox(this);
    m_pSpinHeight->setRange(1, 10000);
    gridLayout->addWidget(new QLabel(tr("Height:"), this), row, column++, Qt::AlignRight);
    gridLayout->addItem(new QSpacerItem(1, 1), row, column++);
    gridLayout->addWidget(m_pSpinHeight, row, column++);
    gridLayout->addWidget(new QLabel(tr(" Pixel"), this), row, column++);
    // stretching
    gridLayout->setColumnStretch(0, 30);
    gridLayout->setColumnStretch(1, 5);
    gridLayout->setColumnStretch(2, 30);
    gridLayout->setColumnStretch(3, 30);

    // Groupboxes
    QGroupBox* pGBoxSize = new QGroupBox(tr("Image Size"), this);
    pGBoxSize->setLayout(gridLayout);
    m_pGBoxPreview = new QGroupBox(tr("Preview"), this);

    // Dialog-Layout
    QVBoxLayout* vlayout = ui->verticalLayout;
    vlayout->addWidget(pGBoxSize, 4);
    vlayout->addWidget(m_pGBoxPreview, 5);
}

void CNewImageDialog::AddConnections()
{
    connect(m_pComboTemplates, &QComboBox::currentIndexChanged, this, &CNewImageDialog::SetImageSize);
    connect(m_pComboTemplates, &QComboBox::currentIndexChanged, this, &CNewImageDialog::UpdatePreview);
    connect(m_pSpinWidth, &QSpinBox::valueChanged, this, &CNewImageDialog::SetCustomSize);
    connect(m_pSpinWidth, &QSpinBox::valueChanged, this, &CNewImageDialog::UpdatePreview);
    connect(m_pSpinHeight, &QSpinBox::valueChanged, this, &CNewImageDialog::SetCustomSize);
    connect(m_pSpinHeight, &QSpinBox::valueChanged, this, &CNewImageDialog::UpdatePreview);
}

void CNewImageDialog::FillCombobox()
{
    if (m_pComboTemplates != NULL && m_pComboTemplates->count() == 0)
    {
        EnumTemplate templates[] = { CUSTOM, S640X480, S800X600, S1024X768, S1600X1200 };

        for (int i = 0; i < sizeof(templates)/sizeof(templates[0]); ++i)
        {
            QString text = GetTemplateText(templates[i]);
            m_pComboTemplates->insertItem(templates[i], text);
        }
        m_pComboTemplates->setCurrentIndex((int)S640X480);
    }
}

void CNewImageDialog::SetImageSize()
{
    if (m_pComboTemplates != NULL && m_pSpinWidth != NULL && m_pSpinHeight != NULL)
    {
        EnumTemplate t = (EnumTemplate)m_pComboTemplates->currentIndex();
        if (t > EnumTemplate::CUSTOM)
        {
            QSignalBlocker wBlocker(m_pSpinWidth);
            QSignalBlocker hBlocker(m_pSpinHeight);
            m_pSpinWidth->setValue(GetTemplateWidth(t));
            m_pSpinHeight->setValue(GetTemplateHeight(t));
        }
    }
}

void CNewImageDialog::SetCustomSize()
{
    if (m_pComboTemplates != NULL && m_pComboTemplates->currentIndex() != (int)CUSTOM)
    {
        QSignalBlocker blocker(m_pComboTemplates);
        m_pComboTemplates->setCurrentIndex((int)CUSTOM);
    }
}

void CNewImageDialog::UpdatePreview()
{
    update();
}

int CNewImageDialog::GetTemplateWidth(EnumTemplate e) const
{
    switch (e)
    {
    case S640X480:      return 640;
    case S800X600:      return 800;
    case S1024X768:     return 1024;
    case S1600X1200:    return 1600;
    default:            return 0;
    }
}

int CNewImageDialog::GetTemplateHeight(EnumTemplate e) const
{
    switch (e)
    {
    case S640X480:      return 480;
    case S800X600:      return 600;
    case S1024X768:     return 768;
    case S1600X1200:    return 1200;
    default:            return 0;
    }
}

QString CNewImageDialog::GetTemplateText(EnumTemplate e) const
{
    switch (e)
    {
    case INVALID:       return tr("Invalid value");
    case CUSTOM:        return tr("Custom");
    case S640X480:      return "640 x 480";
    case S800X600:      return "800 x 600";
    case S1024X768:     return "1024 x 768";
    case S1600X1200:    return "1600 x 1200";
    default:            return 0;
    }
}

/*virtual*/ void CNewImageDialog::paintEvent(QPaintEvent* pEvent)
{
    QDialog::paintEvent(pEvent);

    // draw the preview rectangle into the GroupBox
    static const int BORDER = 2;
    QRect previewRect = CalcPreviewRect();
    QRect previewRectBorder(previewRect.topLeft() - QPoint(BORDER, BORDER), previewRect.size() + 2 * QSize(BORDER, BORDER));
    QPainter paint;
    paint.begin(this);
    paint.fillRect(previewRectBorder, QBrush(Qt::black));
    paint.fillRect(previewRect, QBrush(Qt::white));
    paint.end();
}

QRect CNewImageDialog::CalcPreviewRect() const
{
    static const int MAXWIDTH = 150;
    static const int MAXHEIGHT = 100;
    static const QPoint CORR = QPoint(0,5);

    int width(0), height(0);
    double ratio = (double) m_pSpinWidth->value() / m_pSpinHeight->value();
    if (ratio >= 1.0)
    {
        width = MAXWIDTH;
        height = MAXWIDTH / ratio;
    }
    else
    {
        width = MAXHEIGHT * ratio;
        height = MAXHEIGHT;
    }
    if (width > MAXWIDTH)
    {
        height *= (double) MAXWIDTH / width;
        width = MAXWIDTH;
    }
    if (height > MAXHEIGHT)
    {
        width *= (double) MAXHEIGHT / height;
        height = MAXHEIGHT;
    }

    QSize size = m_pGBoxPreview->size();
    QPoint posOrigin = m_pGBoxPreview->parentWidget()->pos() + m_pGBoxPreview->pos();
    QPoint posCenter = posOrigin + QPoint(0.5 * size.width(), 0.5 * size.height()) + CORR;
    QPoint posTopLeft = posCenter - QPoint(0.5 * width, 0.5 * height);

    return QRect(posTopLeft, QSize(width, height));
}
