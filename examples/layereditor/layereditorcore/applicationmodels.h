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

#include <memory>

class MaterialModel;
class SampleModel;
class QString;

//! Container class to hold all SessionModel's used during GUI session.
//! Holds SampleModel with multilayer structure and MaterialModel with collection of materials.

class ApplicationModels
{
public:
    ApplicationModels();
    ~ApplicationModels();

    MaterialModel* materialModel();
    SampleModel* sampleModel();

    void readFromFile(const QString& name);

    void writeToFile(const QString& name);

private:
    struct ApplicationModelsImpl;
    std::unique_ptr<ApplicationModelsImpl> p_impl;
};

#endif //  APPLICATIONMODELS_H
