// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialSelectorCellEditor.h"
#include "externalproperty.h"
#include <QComboBox>
#include <QVBoxLayout>
#include <QDebug>

namespace
{
QStringList toList(const std::vector<std::string>& container)
{
    QStringList result;
    for (auto str : container)
        result.push_back(QString::fromStdString(str));
    return result;
}
} // namespace

using namespace ModelView;

MaterialSelectorCellEditor::MaterialSelectorCellEditor(QWidget* parent)
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

QSize MaterialSelectorCellEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize MaterialSelectorCellEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void MaterialSelectorCellEditor::onIndexChanged(int index)
{
    qDebug() << "MaterialSelectorCellEditor::onIndexChanged" << index;
}

void MaterialSelectorCellEditor::update_components()
{
    setConnected(false);

    m_box->clear();
    m_box->insertItems(0, toList(internLabels()));
    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns list of labels for QComboBox

std::vector<std::string> MaterialSelectorCellEditor::internLabels()
{
    return {"aaa"};
}

//! Returns index for QComboBox.

int MaterialSelectorCellEditor::internIndex()
{
    return 0;
}

void MaterialSelectorCellEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &MaterialSelectorCellEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &MaterialSelectorCellEditor::onIndexChanged);
}
