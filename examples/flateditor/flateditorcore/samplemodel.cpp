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

namespace FlatEditor {

SampleModel::SampleModel() : SessionModel("SampleModel")
{
    registerItem<BeamItem>();
    registerItem<DistributionNoneItem>();
    registerItem<DistributionGaussianItem>();
    registerItem<DistributionLogNormalItem>();
    registerItem<DistributionTrapezoidItem>();
    registerItem<DistributionGroupItem>();

    populateModel();
}

//! Provides initial model content.

void SampleModel::populateModel()
{
    insertItem<BeamItem>();
    insertItem<DistributionGroupItem>();
}

} // namespace FlatEditor
