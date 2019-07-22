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
    m_sample_model->insertNewItem(::Constants::LayerType, mlayer, MultiLayerItem::T_LAYERS);
}

void SampleTreeController::onCreateLayer()
{
    insertSampleElement(::Constants::LayerType);
}

void SampleTreeController::onClone()
{
    auto to_clone = selectedItem(m_selection_model, m_view_model);
    if (!to_clone)
        return;

    auto parent = to_clone->parent();
    const auto tag_row = parent->tagRowOfItem(to_clone);
    m_sample_model->copyItem(to_clone, parent, tag_row.first, tag_row.second + 1);
}

void SampleTreeController::onRemove()
{
    auto item = selectedItem(m_selection_model, m_view_model);
    if (!item)
        return;

    Utils::DeleteItemFromModel(item);
}

ModelView::SessionItem*  SampleTreeController::insertSampleElement(const std::string& model_type)
{
    auto selected_item = selectedItem(m_selection_model, m_view_model);
    SessionItem* parent = selected_item ? selected_item->parent() : nullptr;
    std::pair<std::string, int> tag_row =
        selected_item ? parent->tagRowOfItem(selected_item) : std::pair<std::string, int>{{}, -1};

    return m_sample_model->insertNewItem(model_type, parent, tag_row.first, tag_row.second + 1);
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
