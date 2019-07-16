// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/SampleViewFactory.h
//! @brief     Defines class SampleViewFactory
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef SAMPLEVIEWFACTORY_H
#define SAMPLEVIEWFACTORY_H

#include <QMap>
#include <QStringList>

class IView;

class SampleViewFactory
{
public:
    static bool isValidType(const QString &name);
    static IView *createSampleView(const QString &name);

    static bool isValidExampleName();

private:
    static QStringList m_valid_item_names;
};


#endif // SAMPLEVIEWFACTORY_H
