// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/externalpropertycomboeditor.h"
#include "mvvm/model/externalproperty.h"
#include <QColor>
#include <QComboBox>
#include <QStandardItemModel>
#include <QVBoxLayout>

using namespace ModelView;

ExternalPropertyComboEditor::ExternalPropertyComboEditor(callback_t callback, QWidget* parent)
    : CustomEditor(parent)
    , m_getPropertiesCallback(std::move(callback))
    , m_box(new QComboBox)
    , m_comboModel(new QStandardItemModel(this))
{
    setAutoFillBackground(true);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_box);
    setLayout(layout);

    m_box->setModel(m_comboModel);

    setConnected(true);
}

QSize ExternalPropertyComboEditor::sizeHint() const
{
    return m_box->sizeHint();
}

QSize ExternalPropertyComboEditor::minimumSizeHint() const
{
    return m_box->minimumSizeHint();
}

void ExternalPropertyComboEditor::onIndexChanged(int index)
{
    auto property = m_data.value<ModelView::ExternalProperty>();
    auto mdata = m_getPropertiesCallback();

    if (index >= 0 && index < static_cast<int>(mdata.size())) {
        if (property != mdata[static_cast<size_t>(index)])
            setDataIntern(QVariant::fromValue(mdata[static_cast<size_t>(index)]));
    }
}

void ExternalPropertyComboEditor::update_components()
{
    setConnected(false);

    m_comboModel->clear();

    QStandardItem* parentItem = m_comboModel->invisibleRootItem();
    for (auto prop : m_getPropertiesCallback()) {
        auto item = new QStandardItem(QString::fromStdString(prop.text()));
        parentItem->appendRow(item);
        item->setData(prop.color(), Qt::DecorationRole);
    }

    m_box->setCurrentIndex(internIndex());

    setConnected(true);
}

//! Returns index for QComboBox.

int ExternalPropertyComboEditor::internIndex()
{
    if (!m_data.canConvert<ModelView::ExternalProperty>())
        return 0;

    auto property = m_data.value<ModelView::ExternalProperty>();
    int result(-1);
    for (auto prop : m_getPropertiesCallback()) {
        ++result;
        if (property.identifier() == prop.identifier())
            return result;
    }

    return result;
}

void ExternalPropertyComboEditor::setConnected(bool isConnected)
{
    if (isConnected)
        connect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this,
                &ExternalPropertyComboEditor::onIndexChanged, Qt::UniqueConnection);
    else
        disconnect(m_box, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
                   this, &ExternalPropertyComboEditor::onIndexChanged);
}
