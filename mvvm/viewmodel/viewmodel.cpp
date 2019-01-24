// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "viewmodel.h"
#include "sessionmodel.h"

using namespace ModelView;

ViewModel::ViewModel(QObject* parent)
    : QStandardItemModel(parent)
    , m_sessionModel(nullptr)
{

}

void ViewModel::setSessionModel(SessionModel* model)
{
    m_sessionModel = model;
}
