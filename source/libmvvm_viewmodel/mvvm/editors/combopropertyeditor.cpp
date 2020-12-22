// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/combopropertyeditor.h"
#include "mvvm/model/comboproperty.h"
#include <QComboBox>
#include <QVBoxLayout>

namespace {
QStringList toList(const std::vector<std::string>& container)
{
    QStringList result;
    for (const auto& str : container)
        result.push_back(QString::fromStdString(str));
    return result;
}
} // namespace

using namespace ModelView;

ComboPropertyEditor::ComboPropertyEditor(QWidget* parent)
    : CustomEditor(parent), m_box(new QComboBox)
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);

    setConnected(true);
}

QSize ComboPropertyEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize ComboPropertyEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

bool ComboPropertyEditor::is_persistent() const
{
    return true;
}

void ComboPropertyEditor::onIndexChanged(int index)
{
    auto comboProperty = m_data.value<ComboProperty>();

    if (comboProperty.currentIndex() != index) {
        comboProperty.setCurrentIndex(index);
        setDataIntern(QVariant::fromValue<ComboProperty>(comboProperty));
    }
}

void ComboPropertyEditor::update_components()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, toList(internLabels()));
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

std::vector<std::string> ComboPropertyEditor::internLabels()
{
    if (!m_data.canConvert<ComboProperty>())
        return {};
    auto comboProperty = m_data.value<ComboProperty>();
    return comboProperty.values();
}

//! Returns index for QComboBox.

int ComboPropertyEditor::internIndex()
{
    if (!m_data.canConvert<ComboProperty>())
        return 0;
    auto comboProperty = m_data.value<ComboProperty>();
    return comboProperty.currentIndex();
}

void ComboPropertyEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &ComboPropertyEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &ComboPropertyEditor::onIndexChanged);
}
