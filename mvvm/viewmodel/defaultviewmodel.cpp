// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "defaultviewmodel.h"
#include "childrenstrategies.h"
#include "itemutils.h"
#include "labeldatarowconstructor.h"
#include "modelmapper.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include "viewemptyitem.h"
#include "viewmodelutils.h"
#include <QDebug>
#include <algorithm>

using namespace ModelView;

DefaultViewModel::DefaultViewModel(QObject* parent) : AbstractViewModel(parent)
{
    setRowConstructor(std::make_unique<LabelDataRowConstructor>());
    setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
}

DefaultViewModel::DefaultViewModel(SessionModel* model, QObject* parent) : DefaultViewModel(parent)
{
    setSessionModel(model);
}
