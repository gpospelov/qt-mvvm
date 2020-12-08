// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MOCKWIDGETS_H
#define MOCKWIDGETS_H

#include "mockinterfaces.h"
#include <gmock/gmock.h>

namespace ModelView
{
class SessionItem;
class SessionModel;
} // namespace ModelView

//! Mock class for CallbackContainer.

class CallbackMockWidget
{
public:
    MOCK_METHOD1(onItemDestroy, void(ModelView::SessionItem* item));
    MOCK_METHOD2(onDataChange, void(ModelView::SessionItem* item, int role));
};

//! Mock widget to test ItemMapper functionality.

class MockWidgetForItem : public ItemTestWidgetInterface
{
public:
    MockWidgetForItem(ModelView::SessionItem* item);
    ~MockWidgetForItem();

    void setItem(ModelView::SessionItem* item);

    MOCK_METHOD1(onItemDestroy, void(ModelView::SessionItem* item));
    MOCK_METHOD2(onDataChange, void(ModelView::SessionItem* item, int role));
    MOCK_METHOD2(onPropertyChange, void(ModelView::SessionItem* item, std::string name));
    MOCK_METHOD2(onChildPropertyChange, void(ModelView::SessionItem* item, std::string name));
    MOCK_METHOD2(onItemInserted, void(ModelView::SessionItem* item, ModelView::TagRow tagrow));
    MOCK_METHOD2(onItemRemoved, void(ModelView::SessionItem* item, ModelView::TagRow tagrow));
    MOCK_METHOD2(onAboutToRemoveItem, void(ModelView::SessionItem* item, ModelView::TagRow tagrow));

private:
    ModelView::SessionItem* m_item;
};

//! Mock class to test ModelMapper functionality.

class MockWidgetForModel : public ModelTestWidgetInterface
{
public:
    MockWidgetForModel(ModelView::SessionModel* model);
    ~MockWidgetForModel();

    void setModel(ModelView::SessionModel* model);

    MOCK_METHOD1(onModelDestroyed, void(ModelView::SessionModel* model));
    MOCK_METHOD1(onModelAboutToBeReset, void(ModelView::SessionModel* model));
    MOCK_METHOD1(onModelReset, void(ModelView::SessionModel* model));
    MOCK_METHOD2(onDataChange, void(ModelView::SessionItem* item, int role));
    MOCK_METHOD2(onItemInserted, void(ModelView::SessionItem* item, ModelView::TagRow tagrow));
    MOCK_METHOD2(onItemRemoved, void(ModelView::SessionItem* item, ModelView::TagRow tagrow));
    MOCK_METHOD2(onAboutToRemoveItem, void(ModelView::SessionItem* item, ModelView::TagRow tagrow));

private:
    ModelView::SessionModel* m_model;
};

#endif //  MOCKWIDGETS_H
