// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MODELINQMLCORE_PARTICLEVIEWMODEL_H
#define MODELINQMLCORE_PARTICLEVIEWMODEL_H

#include <mvvm/viewmodel/propertyviewmodel.h>
#include <qqml.h>

class ParticleModel;

class ParticleViewModel : public ModelView::PropertyViewModel
{
    Q_OBJECT
    QML_ELEMENT
    QML_ADDED_IN_MINOR_VERSION(1)

public:
    ParticleViewModel(ParticleModel* model);
};

#endif // MODELINQMLCORE_PARTICLEVIEWMODEL_H
