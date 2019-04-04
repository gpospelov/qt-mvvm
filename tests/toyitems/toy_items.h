// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOYITEMS_H
#define TOYITEMS_H

#include "compounditem.h"
#include "sessionmodel.h"
#include "itemfactoryinterface.h"
#include "defaultitemcatalogue.h"
#include <string>

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

class MultiLayer : public ModelView::CompoundItem
{
public:
    static const std::string T_LAYERS;
    MultiLayer();
};

// ----------------------------------------------------------------------------

class Layer : public ModelView::CompoundItem
{
public:
    static const std::string P_THICKNESS;
    static const std::string T_PARTICLES;
    Layer();
};

// ----------------------------------------------------------------------------

class Particle : public ModelView::CompoundItem
{
public:
    static const std::string P_POSITION;
    Particle();
};

// ----------------------------------------------------------------------------

class InterferenceFunction : public ModelView::CompoundItem
{
public:
    static const std::string P_ROTATION_ANLE;
    static const std::string P_INTEGRATION;
    static const std::string P_LATTICE_TYPE;

    InterferenceFunction();

    void activate() override;

private:
    void update_appearance();
};

//! Returns catalogue of toy items.
std::unique_ptr<ModelView::ItemCatalogue> CreateToyItemCatalogue();

} // ToyItems

#endif // TOYITEMS_H

