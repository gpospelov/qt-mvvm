// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOYCONSTANTS_H
#define TOYCONSTANTS_H

#include <mvvm/model/itemfactoryinterface.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <string>

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{
namespace Constants
{

const ModelView::model_type MultiLayerType = "MultiLayer";
const ModelView::model_type LayerType = "Layer";
const ModelView::model_type ParticleType = "Particle";
const ModelView::model_type InterferenceType = "Interference";

const ModelView::model_type CylinderType = "Cylinder";
const ModelView::model_type SphereType = "Sphere";
const ModelView::model_type AnysoPyramidType = "AnysoPyramid";

const ModelView::model_type ShapeGroupType = "ShapeGroup";
}

} // ToyItems

#endif // TOYCONSTANTS_H
