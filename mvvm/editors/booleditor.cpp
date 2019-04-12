// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "booleditor.h"
#include <QCheckBox>
#include <QHBoxLayout>
#include <stdexcept>

namespace  {
const QString true_text = "True";
const QString false_text = "False";
}

using namespace ModelView;

BoolEditor::BoolEditor(QWidget* parent)
    : CustomEditor(parent), m_checkBox(new QCheckBox)

{
    setAutoFillBackground(true);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    layout->addWidget(m_checkBox);
    setLayout(layout);

    connect(m_checkBox, &QCheckBox::toggled, this, &BoolEditor::onCheckBoxChange);
    setFocusProxy(m_checkBox);
    m_checkBox->setText(true_text);
}

void BoolEditor::onCheckBoxChange(bool value)
{
    if(value != m_data.toBool())
        setDataIntern(QVariant(value));
}

void BoolEditor::update_components()
{
    if (m_data.type() != QVariant::Bool)
        throw std::runtime_error("BoolEditor::update_components() -> Error. Wrong variant type");

    bool value = m_data.toBool();
    m_checkBox->blockSignals(true);
    m_checkBox->setChecked(value);
    m_checkBox->setText(value ? true_text : false_text);
    m_checkBox->blockSignals(false);
}
