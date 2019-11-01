// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "scientificspinboxeditor.h"
#include "numericutils.h"
#include "scientificspinbox.h"
#include <QVBoxLayout>

using namespace ModelView;

ScientificSpinBoxEditor::ScientificSpinBoxEditor(QWidget* parent)
    : CustomEditor(parent)
    , m_doubleEditor(new ScientificSpinBox)
{
    setAutoFillBackground(true);
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor,
            &ScientificSpinBox::valueChanged,
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
}

void ScientificSpinBoxEditor::setRange(double minimum, double maximum)
{
    m_doubleEditor->setMinimum(minimum);
    m_doubleEditor->setMaximum(maximum);
}


void ScientificSpinBoxEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
}

void ScientificSpinBoxEditor::setSingleStep(double step)
{
    m_doubleEditor->setSingleStep(step);
}

void ScientificSpinBoxEditor::onEditingFinished()
{
    double new_value = m_doubleEditor->value();

    if (!Utils::AreAlmostEqual(new_value, m_data.value<double>()))
        setDataIntern(QVariant::fromValue(new_value));
}

void ScientificSpinBoxEditor::update_components()
{
    if (m_data.type() != QVariant::Double)
        throw std::runtime_error(
            "ScientificSpinBoxEditor::update_components() -> Error. Wrong variant type");

    m_doubleEditor->setValue(m_data.value<double>());
}
