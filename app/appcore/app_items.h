// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef APPITEMS_H
#define APPITEMS_H

#include "sessionitem.h"
#include "sessionmodel.h"
#include "itemfactoryinterface.h"
#include <string>

//! Collection of toy items and models for testing purposes.

namespace AppItems
{

const ModelView::model_type MultiLayerType = "MultiLayer";
const ModelView::model_type LayerType = "Layer";

class MultiLayer : public ModelView::SessionItem
{
public:
    static const std::string T_LAYERS;
    MultiLayer();
};

class Layer : public ModelView::SessionItem
{
public:
    Layer();
};

class ItemFactory : public ModelView::ItemFactoryInterface
{
public:
    ModelView::SessionItem* createItem(const ModelView::model_type& modelType = {}) override;

    ModelView::SessionItem* createEmptyItem() override;
};

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

};

}

#endif // APPITEMS_H
