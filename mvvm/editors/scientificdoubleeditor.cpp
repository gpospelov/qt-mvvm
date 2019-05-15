// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "scientificdoubleeditor.h"
#include "numericutils.h"
#include <QDoubleValidator>
#include <QVBoxLayout>
#include <QLineEdit>
#include <cmath>
#include <limits>
#include <stdexcept>

using namespace ModelView;

ScientificDoubleEditor::ScientificDoubleEditor(QWidget* parent)
    : CustomEditor(parent), m_lineEdit(new QLineEdit), m_validator(nullptr)

{
    setAutoFillBackground(true);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_lineEdit);

    m_validator = new QDoubleValidator(0.0, 1e+200, 1000, this);
    m_validator->setNotation(QDoubleValidator::ScientificNotation);
    m_lineEdit->setValidator(m_validator);

    connect(m_lineEdit, &QLineEdit::editingFinished, this,
            &ScientificDoubleEditor::onEditingFinished);

    setLayout(layout);
}

void ScientificDoubleEditor::setLimits(const RealLimits&) {}

void ScientificDoubleEditor::onEditingFinished()
{
    double new_value = m_lineEdit->text().toDouble();

    if (!Utils::AreAlmostEqual(new_value, m_data.toDouble()))
        setDataIntern(QVariant::fromValue(new_value));
}

void ScientificDoubleEditor::update_components()
{
    if (m_data.type() != QVariant::Double)
        throw std::runtime_error(
            "ScientificDoubleEditor::update_components() -> Error. Wrong variant type");

    m_lineEdit->setText(QString::number(m_data.toDouble(), 'g'));
}
