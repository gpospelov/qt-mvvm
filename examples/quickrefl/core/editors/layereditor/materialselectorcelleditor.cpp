// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialselectorcelleditor.h"
#include "materialitems.h"
#include "materialmodel.h"
#include <QColor>
#include <QComboBox>
#include <QStandardItemModel>
#include <QVBoxLayout>
#include <mvvm/model/externalproperty.h>

using namespace ModelView;

MaterialSelectorCellEditor::MaterialSelectorCellEditor(MaterialModel* model, QWidget* parent)
    : CustomEditor(parent), m_box(new QComboBox), m_model(model),
      m_combo_model(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);

    m_box->setModel(m_combo_model);

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
    auto property = m_data.value<ModelView::ExternalProperty>();
    auto mdata = m_model->material_data();

    if (index >= 0 && index < static_cast<int>(mdata.size())) {
        if (property != mdata[static_cast<size_t>(index)])
            setDataIntern(QVariant::fromValue(mdata[index]));
    }
}

void MaterialSelectorCellEditor::update_components()
{
    setConnected(false);

    m_combo_model->clear();

    QStandardItem* parentItem = m_combo_model->invisibleRootItem();
    for (auto prop : m_model->material_data()) {
        auto item = new QStandardItem(QString::fromStdString(prop.text()));
        parentItem->appendRow(item);
        item->setData(prop.color(), Qt::DecorationRole);
    }

    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns index for QComboBox.

int MaterialSelectorCellEditor::internIndex()
{
    if (!m_data.canConvert<ModelView::ExternalProperty>())
        return 0;

    auto property = m_data.value<ModelView::ExternalProperty>();
    int result(-1);
    for (auto prop : m_model->material_data()) {
        ++result;
        if (property.identifier() == prop.identifier())
            return result;
    }

    return result;
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
