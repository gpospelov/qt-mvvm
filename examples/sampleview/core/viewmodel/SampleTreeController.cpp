#include "SampleTreeController.h"
#include "LayerItems.h"
#include "SampleModel.h"
#include "item_constants.h"
#include "modelutils.h"
#include "sessionitem.h"
#include <set>

using namespace ModelView;

namespace {
SessionItem* selectedItem(const QItemSelectionModel& selection_model,
                          const LayerTableViewModel& view_model);
}

SampleTreeController::SampleTreeController(SampleModel* model)
    : QObject()
    , m_sample_model(model)
    , m_view_model(m_sample_model)
    , m_selection_model(&m_view_model)
{
    auto root = model ? model->rootItem() : nullptr;
    m_view_model.setRootSessionItem(root);
}

SampleTreeController::~SampleTreeController() = default;

void SampleTreeController::onCreateMultiLayer()
{
    auto mlayer = insertSampleElement(::Constants::MultiLayerType);
    auto new_item = m_sample_model->insertNewItem(::Constants::LayerType, mlayer,
                                                  MultiLayerItem::T_LAYERS);
    selectItem(new_item);
}

void SampleTreeController::onCreateLayer()
{
    auto new_item = insertSampleElement(::Constants::LayerType);
    selectItem(new_item);
}

void SampleTreeController::onClone()
{
    auto to_clone = selectedItem(m_selection_model, m_view_model);
    if (!to_clone)
        return;

    auto parent = to_clone->parent();
    const auto tag_row = parent->tagRowOfItem(to_clone);
    auto new_item = m_sample_model->copyItem(to_clone, parent, tag_row.first, tag_row.second + 1);
    selectItem(new_item);
}

void SampleTreeController::onRemove()
{
    auto item = selectedItem(m_selection_model, m_view_model);
    if (!item)
        return;

    SessionItem* to_select = findNextSibling(item);

    Utils::DeleteItemFromModel(item);
    selectItem(to_select);
}

ModelView::SessionItem*  SampleTreeController::insertSampleElement(const std::string& model_type)
{
    auto selected_item = selectedItem(m_selection_model, m_view_model);
    SessionItem* parent = selected_item ? selected_item->parent() : nullptr;
    std::pair<std::string, int> tag_row =
        selected_item ? parent->tagRowOfItem(selected_item) : std::pair<std::string, int>{{}, -1};

    return m_sample_model->insertNewItem(model_type, parent, tag_row.first, tag_row.second + 1);
}

SessionItem* SampleTreeController::findNextSibling(SessionItem* item)
{
    if (!item)
        return nullptr;

    auto parent = item->parent();
    if (!parent)
        return nullptr;

    auto siblings = parent->getItems(parent->tagFromItem(item));
    size_t size = siblings.size();
    if (size <= 1)
        return parent;
    if (siblings.back() == item)
        return siblings[size - 2];

    for (size_t i = 0; i < size; ++i)
        if (siblings[i] == item)
            return siblings[i + 1];

    return nullptr;
}

void SampleTreeController::selectItem(SessionItem *item)
{
    if (!item)
        return;

    const QModelIndexList index_list = m_view_model.indexOfSessionItem(item);
    if (index_list.empty())
        return;

    const QModelIndex& id = index_list.front(); // assuming one-to-one index/item correspondence
    auto flags = QItemSelectionModel::SelectCurrent | QItemSelectionModel::Rows;
    m_selection_model.select(id, flags);
    m_selection_model.setCurrentIndex(id, flags);
}

namespace {
SessionItem* selectedItem(const QItemSelectionModel& selection_model,
                          const LayerTableViewModel& view_model)
{
    const QModelIndexList& selection = selection_model.selectedRows();
    if (selection.empty())
        return nullptr;
    // assuming single-line selection mode
    Q_ASSERT(selection.size() == 1);

    return view_model.sessionItemFromIndex(selection.front());
}
}
