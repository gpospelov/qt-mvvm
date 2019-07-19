#include "SampleTreeController.h"
#include "SampleModel.h"

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
{}
