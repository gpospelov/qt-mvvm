// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modelinqmlcore/particleviewmodel.h"
#include "modelinqmlcore/particlemodel.h"

ParticleViewModel::ParticleViewModel(ParticleModel* model) : ModelView::PropertyViewModel(model) {}
