// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
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
