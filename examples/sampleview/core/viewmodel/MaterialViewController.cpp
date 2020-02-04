// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "MaterialViewController.h"
#include "MaterialItems.h"
#include "MaterialModel.h"
#include "item_constants.h"
#include <mvvm/model/modelutils.h>

using namespace ModelView;

namespace
{
const std::vector<std::pair<QString, std::string>> material_types = {
    {"SLD-based material", ::Constants::SLDMaterialType},
    {"Refractive index material", ::Constants::RefIndexMaterialType}};

const std::deque<QColor> color_queue = {Qt::blue,   Qt::red,  Qt::green,   Qt::gray,   Qt::black,
                                        Qt::yellow, Qt::cyan, Qt::magenta, Qt::darkRed};
} // namespace

MaterialViewController::MaterialViewController(MaterialModel* model)
    : m_material_model(model), m_view_model(model), m_selection_model(&m_view_model),
      m_current_material_type(material_types.front().second), m_color_queue(color_queue)
{
    SessionItem* root = model ? Utils::TopItem<MaterialContainerItem>(model) : nullptr;
    m_view_model.setRootSessionItem(root);
    m_view_model.setMaterialType(m_current_material_type);

    connect(&m_selection_model, &QItemSelectionModel::selectionChanged, this,
            &MaterialViewController::onSelectionChanged);
}

void MaterialViewController::onMaterialSelectionChange(const QString& material_display_name)
{
    for (auto& info : material_types)
        if (info.first == material_display_name) {
            m_view_model.setMaterialType(info.second);
            m_current_material_type = info.second;
            break;
        }
    emit rowCheckStateChanged(checkedItems());
}

void MaterialViewController::onCreateMaterial()
{
    SessionItem* root = m_view_model.sessionItemFromIndex(QModelIndex());
    auto inserted = m_material_model->insertNewItem(m_current_material_type, root,
                                                    MaterialContainerItem::T_MATERIALS);

    // assign a color to the new material
    QColor current = m_color_queue.front();
    inserted->setProperty(MaterialBaseItem::P_COLOR, current);
    m_color_queue.pop_front();
    m_color_queue.push_back(current);
}

void MaterialViewController::onCloneMaterial()
{
    auto to_clone = selectedMaterialItems();
    SessionItem* root = m_view_model.sessionItemFromIndex(QModelIndex());

    for (auto item : to_clone) {
        auto new_item = m_material_model->insertNewItem(m_current_material_type, root,
                                                        MaterialContainerItem::T_MATERIALS);

        for (auto child : item->children()) {
            auto new_child = new_item->getItem(item->tagOfItem(child));
            new_child->setData(child->data());
        }
    }
}

void MaterialViewController::onRemoveMaterial()
{
    auto to_delete = selectedMaterialItems();
    SessionItem* root = m_view_model.sessionItemFromIndex(QModelIndex());

    for (auto item : to_delete)
        m_material_model->removeItem(root, root->tagRowOfItem(item));
}

QStringList MaterialViewController::materialSets() const
{
    QStringList result;
    for (auto& iter : material_types)
        result.push_back(iter.first);
    return result;
}

void MaterialViewController::toggleRowSelection(const QModelIndex& index)
{
    disconnect(&m_selection_model, &QItemSelectionModel::selectionChanged, this,
               &MaterialViewController::onSelectionChanged);

    bool current_value = m_view_model.data(index, Qt::CheckStateRole).value<bool>();
    m_view_model.setData(index, !current_value, Qt::CheckStateRole);
    updateSelection(index);

    emit rowCheckStateChanged(checkedItems());

    connect(&m_selection_model, &QItemSelectionModel::selectionChanged, this,
            &MaterialViewController::onSelectionChanged);
}

void MaterialViewController::toggleRowSpanSelection(const QModelIndex& index)
{
    disconnect(&m_selection_model, &QItemSelectionModel::selectionChanged, this,
               &MaterialViewController::onSelectionChanged);

    const bool set_value = !m_view_model.data(index, Qt::CheckStateRole).value<bool>();
    auto selected = m_selection_model.currentIndex();
    int previous = selected.isValid() ? selected.row() : 0;
    int now = index.row();

    for (int i = std::min(previous, now), max = std::max(previous, now); i <= max; ++i) {
        QModelIndex i_index = m_view_model.index(i, 0);
        m_view_model.setData(i_index, set_value, Qt::CheckStateRole);
    }
    updateSelection(index);

    emit rowCheckStateChanged(checkedItems());

    connect(&m_selection_model, &QItemSelectionModel::selectionChanged, this,
            &MaterialViewController::onSelectionChanged);
}

//! Updates selection to checked rows and sets current index of selection model to the given
//! index.
void MaterialViewController::updateSelection(const QModelIndex& current)
{
    auto selection_state = [](const QModelIndex& index) {
        bool selected = index.data(Qt::CheckStateRole).value<bool>();
        auto flag = selected ? QItemSelectionModel::Select : QItemSelectionModel::Deselect;
        return flag | QItemSelectionModel::Rows;
    };

    for (int i = 0, count = m_view_model.rowCount(); i < count; ++i) {
        QModelIndex index = m_view_model.index(i, 0);
        m_selection_model.select(index, selection_state(index));
    }

    m_selection_model.setCurrentIndex(current, selection_state(current));
}

void MaterialViewController::onSelectionChanged(const QItemSelection&, const QItemSelection&)
{
    for (int i = 0, count = m_view_model.rowCount(); i < count; ++i) {
        QModelIndex index = m_view_model.index(i, 0);
        m_view_model.setData(index, false, Qt::CheckStateRole);
    }
    emit rowCheckStateChanged(checkedItems());
}

QList<MaterialBaseItem*> MaterialViewController::selectedMaterialItems() const
{
    QList<MaterialBaseItem*> result;
    for (auto index : checkedItems()) {
        auto material = m_view_model.sessionItemFromRow(index.row());
        if (!material)
            continue;
        result.append(material);
    }
    return result;
}

QList<QModelIndex> MaterialViewController::checkedItems() const
{
    QList<QModelIndex> result;
    for (int i = 0, count = m_view_model.rowCount(); i < count; ++i) {
        QModelIndex index = m_view_model.index(i, 0);
        if (index.data(Qt::CheckStateRole).value<bool>())
            result.append(index);
    }
    return result;
}
