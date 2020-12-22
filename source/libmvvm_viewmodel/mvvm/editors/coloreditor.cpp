// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/coloreditor.h"
#include "mvvm/editors/customeventfilters.h"
#include "mvvm/editors/styleutils.h"
#include "mvvm/model/customvariants.h"
#include <QColorDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <stdexcept>

using namespace ModelView;

ColorEditor::ColorEditor(QWidget* parent)
    : CustomEditor(parent), m_pixmapLabel(new QLabel), m_focusFilter(new LostFocusFilter(this))

{
    setMouseTracking(true);
    setAutoFillBackground(true);

    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);

    layout->addWidget(m_pixmapLabel);
    //    layout->addWidget(m_textLabel); // no color name, only color rectangle
    layout->addStretch(1);
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_InputMethodEnabled);

    setLayout(layout);
}

void ColorEditor::mousePressEvent(QMouseEvent*)
{
    // temporarily installing filter to prevent loss of focus caused by too insistent dialog
    installEventFilter(m_focusFilter);

    auto new_color = QColorDialog::getColor(currentColor());

    removeEventFilter(m_focusFilter);

    if (new_color.isValid()) {
        setDataIntern(new_color);
        update_components();
    }
}

QColor ColorEditor::currentColor() const
{
    return m_data.value<QColor>();
}

void ColorEditor::update_components()
{
    if (!Utils::IsColorVariant(m_data))
        throw std::runtime_error("ColorEditor::update_components() -> Error. Wrong variant type");

    QPixmap pixmap(Style::DefaultPixmapSize(), Style::DefaultPixmapSize());
    pixmap.fill(currentColor());
    //    m_textLabel->setText(currentColor().name());
    m_pixmapLabel->setPixmap(pixmap);
}
