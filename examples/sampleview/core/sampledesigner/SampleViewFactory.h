// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEVIEWFACTORY_H
#define SAMPLEVIEWFACTORY_H

#include <QString>

class IView;

class SampleViewFactory
{
public:
    static bool isValidType(const std::string& name);
    static IView* createSampleView(const std::string& name);
};


#endif // SAMPLEVIEWFACTORY_H
