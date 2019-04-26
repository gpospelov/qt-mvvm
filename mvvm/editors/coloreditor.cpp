// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "coloreditor.h"
#include "customvariants.h"
#include "styleutils.h"
#include <QLabel>
#include <QColor>
#include <QHBoxLayout>

using namespace ModelView;

ColorEditor::ColorEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_textLabel(new QLabel)
    , m_pixmapLabel(new QLabel)
{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    layout->addWidget(m_pixmapLabel);
    layout->addWidget(m_textLabel);
    layout->addStretch(1);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);

    setLayout(layout);
}

void ColorEditor::update_components()
{
    if (!Utils::IsColorVariant(m_data))
        throw std::runtime_error("ColorEditor::update_components() -> Error. Wrong variant type");

    QColor color = m_data.value<QColor>();
    QPixmap pixmap(Style::DefaultPixmapSize(), Style::DefaultPixmapSize());
    pixmap.fill(color);

    m_textLabel->setText(color.name());
    m_pixmapLabel->setPixmap(pixmap);
}
