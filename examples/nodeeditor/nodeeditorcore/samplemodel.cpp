// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "samplemodel.h"
#include "sampleitems.h"

using namespace ModelView;

namespace NodeEditor {

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    registerItem<ParticleItem>();
    registerItem<TransformationItem>();

    createInitialContent();
}

void SampleModel::createInitialContent()
{
    auto particleItem = insertItem<ParticleItem>();
    auto transformation = insertItem<TransformationItem>(particleItem);
}

} // namespace NodeEditor
