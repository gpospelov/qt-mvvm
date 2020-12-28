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

    create_initial_content();
}

void SampleModel::create_initial_content()
{
    auto item = insertItem<ParticleItem>();
}

} // namespace NodeEditor
