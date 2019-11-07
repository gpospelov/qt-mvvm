// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEEDITORFACTORY_H
#define SAMPLEEDITORFACTORY_H

#include <QItemEditorFactory>
#include <memory>

/*!
@namespace SampleEditorFactory
@brief A collection of functions returning properly configured QItemEditorFactory.
*/

namespace SampleEditorFactory {
std::unique_ptr<QItemEditorFactory> createStandardSampleEditorFactory();
}

#endif // SAMPLEEDITORFACTORY_H
