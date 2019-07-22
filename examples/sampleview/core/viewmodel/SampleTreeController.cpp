#include "SampleTreeController.h"
#include "SampleModel.h"
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
{}

void SampleTreeController::onCreateLayer()
{}

void SampleTreeController::onClone()
{
    auto to_clone = selectedItem(m_selection_model, m_view_model);
    if (!to_clone)
        return;

    auto parent = to_clone->parent();
    const auto tag_row = parent->tagRowOfItem(to_clone);
    m_sample_model->copyItem(to_clone, parent, tag_row.first, tag_row.second);
}

void SampleTreeController::onRemove()
{
    auto item = selectedItem(m_selection_model, m_view_model);
    if (!item)
        return;

    Utils::DeleteItemFromModel(item);
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
