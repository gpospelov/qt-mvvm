// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "toymodel.h"
#include "toyitems.h"
#include <mvvm/model/itemcatalogue.h>

namespace
{
std::unique_ptr<ModelView::ItemCatalogue> CreateItemCatalogue()
{
    auto result = std::make_unique<ModelView::ItemCatalogue>();
    result->registerItem<ToyItems::MultiLayerItem>();
    result->registerItem<ToyItems::LayerItem>();
    result->registerItem<ToyItems::ParticleItem>();
    result->registerItem<ToyItems::LatticeItem>();
    result->registerItem<ToyItems::SphereItem>();
    result->registerItem<ToyItems::CylinderItem>();
    result->registerItem<ToyItems::AnysoPyramidItem>();
    result->registerItem<ToyItems::ShapeGroupItem>();
    return result;
}
} // namespace

ToyItems::SampleModel::SampleModel() : SessionModel("ToyModel")
{
    setItemCatalogue(CreateItemCatalogue());
}

ToyItems::SampleModel::SampleModel(std::shared_ptr<ModelView::ItemPool> pool)
    : SessionModel("ToyModel", pool)
{
    setItemCatalogue(CreateItemCatalogue());
}
