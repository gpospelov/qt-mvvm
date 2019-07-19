#include "SampleTreeController.h"
#include "SampleModel.h"
#include "modelutils.h"
#include "sessionitem.h"
#include <set>

using namespace ModelView;

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
{}

void SampleTreeController::onRemove()
{
    const QModelIndexList& selection = m_selection_model.selectedRows();
    if (selection.empty())
        return;

    std::set<SessionItem*> to_delete;
    for (auto& index : selection) {
        if (auto item = m_view_model.sessionItemFromIndex(index))
        to_delete.insert(item);
    }

    for (auto item: to_delete)
        Utils::DeleteItemFromModel(item);
}
