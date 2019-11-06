// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include <mvvm/editors/doubleeditor.h>
#include <mvvm/utils/numericutils.h>
#include <QDoubleSpinBox>
#include <QVBoxLayout>

using namespace ModelView;

DoubleEditor::DoubleEditor(QWidget* parent)
    : CustomEditor(parent), m_doubleEditor(new QDoubleSpinBox)
{
    setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setFocusPolicy(Qt::StrongFocus);
    m_doubleEditor->setKeyboardTracking(false);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    layout->addWidget(m_doubleEditor);

    connect(m_doubleEditor,
            static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
            [=] { this->onEditingFinished(); });

    setLayout(layout);

    setFocusProxy(m_doubleEditor);
}

void DoubleEditor::setRange(double minimum, double maximum)
{
    m_doubleEditor->setMinimum(minimum);
    m_doubleEditor->setMaximum(maximum);
}

void DoubleEditor::setDecimals(int decimals)
{
    m_doubleEditor->setDecimals(decimals);
}

void DoubleEditor::setSingleStep(double value)
{
    m_doubleEditor->setSingleStep(value);
}

void DoubleEditor::onEditingFinished()
{
    double new_value = m_doubleEditor->value();

    if (!Utils::AreAlmostEqual(new_value, m_data.value<double>()))
        setDataIntern(QVariant::fromValue(new_value));
}

void DoubleEditor::update_components()
{
    if (m_data.type() != QVariant::Double)
        throw std::runtime_error("DoubleEditor::update_components() -> Error. Wrong variant type");

    m_doubleEditor->setValue(m_data.value<double>());
}
