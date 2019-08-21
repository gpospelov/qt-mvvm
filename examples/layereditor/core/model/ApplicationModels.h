// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef APPLICATIONMODELS_H
#define APPLICATIONMODELS_H

#include <QString>
#include <memory>

class MaterialModel;
class SampleModel;

/*!
@class ApplicationModels
@brief Container class to hold all SessionModel's used during GUI session.

Given class holds SampleModel with multilayer structure and MaterialModel with collection
of materials.
*/

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
    struct ApplicationModelsPrivate;
    std::unique_ptr<ApplicationModelsPrivate> p_impl;
};

#endif //  APPLICATIONMODELS_H
