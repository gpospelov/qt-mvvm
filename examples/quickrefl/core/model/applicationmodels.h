// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef APPLICATIONMODELS_H
#define APPLICATIONMODELS_H

#include <mvvm/interfaces/applicationmodelsinterface.h>
#include <memory>

namespace ModelView
{
class SessionModel;
}

class MaterialModel;
class SampleModel;
class SLDElementModel;
class SLDElementController;
class JobModel;
class RealDataModel;

//!  Main class to holds all models of GUI session.

class ApplicationModels : public ApplicationModelsInterface
{
public:
    ApplicationModels();
    ~ApplicationModels();

    MaterialModel* materialModel();
    SampleModel* sampleModel();
    SLDElementModel* sldViewModel();
    JobModel* jobModel();
    RealDataModel* realDataModel();

    std::vector<ModelView::SessionModel*> persistent_models() const override;

private:
    struct ApplicationModelsImpl;
    std::unique_ptr<ApplicationModelsImpl> p_impl;
};

#endif //  APPLICATIONMODELS_H
