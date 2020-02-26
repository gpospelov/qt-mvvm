// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

//#include <mvvm/model/sessionitem.h>
//#include <mvvm/model/sessionmodel.h>
//#include <mvvm/signals/modelmapper.h>
//#include <mvvm/viewmodel/abstractviewmodel.h>
//#include <mvvm/viewmodel/abstractviewmodelcontroller.h>
//#include <mvvm/viewmodel/childrenstrategyinterface.h>
//#include <mvvm/viewmodel/rowstrategyinterface.h>
//#include <mvvm/viewmodel/viewitem.h>
//#include <mvvm/viewmodel/viewmodelutils.h>

//namespace
//{

////! Returns true if given SessionItem role is valid for view
//bool isValidItemRole(const ModelView::ViewItem* view, int item_role)
//{
//    if (view->item_role() == item_role)
//        return true;

//    if (item_role == ModelView::ItemDataRole::APPEARANCE)
//        return true;
//    return false;
//}
//} // namespace

//using namespace ModelView;

//struct AbstractViewModelController::AbstractViewModelControllerImpl {
//    AbstractViewModelControllerImpl(AbstractViewModel* view_model)
//        : m_view_model(view_model), m_root_item(nullptr), m_session_model(nullptr)
//    {
//    }

//    QList<QStandardItem*> constructRow(SessionItem* item)
//    {
//        return m_row_strategy->constructRow(item);
//    }

//    std::vector<SessionItem*> item_children(const SessionItem* item) const
//    {
//        return m_children_strategy->children(item);
//    }

//    void reset_view_model()
//    {
//        m_view_model->clear();
//    }

//    void update_labels()
//    {
//        m_view_model->setHorizontalHeaderLabels(m_row_strategy->horizontalHeaderLabels());
//    }

//    std::vector<QStandardItem*> findStandardViews(SessionItem* item) {
//        return m_view_model->findStandardViews(item);
//    }

//    AbstractViewModel* m_view_model;
//    SessionItem* m_root_item;
//    SessionModel* m_session_model;
//    std::unique_ptr<ChildrenStrategyInterface> m_children_strategy;
//    std::unique_ptr<RowStrategyInterface> m_row_strategy;
//};

//AbstractViewModelController::AbstractViewModelController(AbstractViewModel* view_model)
//    : p_impl(std::make_unique<AbstractViewModelControllerImpl>(view_model))
//{
//}

//AbstractViewModelController::~AbstractViewModelController()
//{
//    if (sessionModel())
//        sessionModel()->mapper()->unsubscribe(this);
//}

//void AbstractViewModelController::setViewModel(AbstractViewModel* view_model)
//{
//    p_impl->m_view_model = view_model;
//}

//void AbstractViewModelController::setSessionModel(SessionModel* model)
//{
//    if (sessionModel())
//        sessionModel()->mapper()->unsubscribe(this);

//    p_impl->m_session_model = model;

//    if (sessionModel()) {
//        auto on_data_change = [this](SessionItem* item, int role) { onDataChange(item, role); };
//        sessionModel()->mapper()->setOnDataChange(on_data_change, this);

//        auto on_item_inserted = [this](SessionItem* item, TagRow tagrow) {
//            onItemInserted(item, tagrow);
//        };
//        sessionModel()->mapper()->setOnItemInserted(on_item_inserted, this);

//        auto on_item_removed = [this](SessionItem* item, TagRow tagrow) {
//            onItemRemoved(item, tagrow);
//        };
//        sessionModel()->mapper()->setOnItemRemoved(on_item_removed, this);

//        auto on_model_destroyed = [this](SessionModel*) {
//            p_impl->m_session_model = nullptr;
//            p_impl->m_view_model->clear();
//        };
//        sessionModel()->mapper()->setOnModelDestroyed(on_model_destroyed, this);

//        auto on_model_reset = [this](SessionModel*) {
//            setRootSessionItem(nullptr);
//           p_impl->reset_view_model();
//        };
//        sessionModel()->mapper()->setOnModelReset(on_model_reset, this);

//        init_view_model();
//    }
//}

//void AbstractViewModelController::setChildrenStrategy(
//    std::unique_ptr<ChildrenStrategyInterface> children_strategy)
//{
//    p_impl->m_children_strategy = std::move(children_strategy);
//}

//void AbstractViewModelController::setRowStrategy(std::unique_ptr<RowStrategyInterface> row_strategy)
//{
//    p_impl->m_row_strategy = std::move(row_strategy);
//}

//void AbstractViewModelController::iterate(const SessionItem* item, QStandardItem* parent)
//{
//    QStandardItem* origParent(parent);
//    for (auto child : p_impl->item_children(item)) {

//        auto row = p_impl->constructRow(child);
//        if (!row.empty()) {
//            parent->appendRow(row);
//            parent = row.at(0); // labelItem
//            iterate(child, parent);
//        }

//        parent = origParent;
//    }
//}

//void AbstractViewModelController::init_view_model()
//{
//    check_initialization();
//    p_impl->reset_view_model();
//    iterate(rootSessionItem(), p_impl->m_view_model->rootViewItem());
//    p_impl->update_labels();
//}

//void AbstractViewModelController::setRootSessionItem(SessionItem* item)
//{
//    if (item && item->model() != sessionModel())
//        throw std::runtime_error(
//            "ViewModel::setRootSessionItem()->Error. Item doesn't belong to a model.");

//    p_impl->m_root_item = item;
//    init_view_model();
//}

////! Returns root item of the model. Can be different from model's root item when the intention is
////! to show only part of the model.

//SessionItem* AbstractViewModelController::rootSessionItem() const
//{
//    return p_impl->m_root_item ? p_impl->m_root_item : sessionModel()->rootItem();
//}

//SessionModel* AbstractViewModelController::sessionModel()
//{
//    return p_impl->m_session_model;
//}

//const SessionModel* AbstractViewModelController::sessionModel() const
//{
//    return p_impl->m_session_model;
//}

////! Checks initial conditions for a class.

//void AbstractViewModelController::check_initialization()
//{
//    const std::string msg("AbstractViewModelController::check_initialization() -> Error. ");
//    if (!p_impl->m_view_model)
//        throw std::runtime_error(msg + "ViewModel is not defined");

//    if (!p_impl->m_session_model)
//        throw std::runtime_error(msg + "SessionModel is not defined");

//    if (!p_impl->m_row_strategy)
//        throw std::runtime_error(msg + "RowStrategy is not defined");

//    if (!p_impl->m_children_strategy)
//        throw std::runtime_error(msg + "Children is not defined");
//}

//void AbstractViewModelController::generate_children_views(SessionItem* parent)
//{
//    auto views = p_impl->findStandardViews(parent);
//    for (auto view : views)
//        view->removeRows(0, view->rowCount());

//    if (views.size())
//        iterate(parent, views.at(0));
//}

////! Generates necessary notifications on SessionItem's data change.

//void AbstractViewModelController::onDataChange(SessionItem* item, int role)
//{
//    for (auto view : p_impl->m_view_model->findViews(item)) {
//        // inform corresponding LabelView and DataView
//        if (isValidItemRole(view, role)) {
//            auto index = p_impl->m_view_model->indexFromItem(view);
//            p_impl->m_view_model->dataChanged(index, index, Utils::item_role_to_qt(role));
//        }
//    }
//}

////! Rebuild view model branch on session model change.

//void AbstractViewModelController::onItemInserted(SessionItem* parent, TagRow)
//{
//    generate_children_views(parent);
//}

////! Rebuild view model branch on session model change.

//void AbstractViewModelController::onItemRemoved(SessionItem* parent, TagRow)
//{
//    generate_children_views(parent);
//}
