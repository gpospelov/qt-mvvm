// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QApplication>
#include <QLocale>
#include <QTreeView>

#include <mvvm/model/compounditem.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/signals/itemmapper.h>
#include <mvvm/viewmodel/defaultviewmodel.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>

using namespace ModelView;

int main(int argc, char** argv)
{
    QLocale::setDefault(QLocale(QLocale::English, QLocale::UnitedStates));

    QApplication app(argc, argv);

    SessionModel model;
    auto item = model.insertItem<CompoundItem>();
    item->setDisplayName("Item");

    item->addProperty("Hello", "World!");
    item->addProperty("Your answer is", true);

    auto on_property = [](SessionItem* item, const std::string& name) {
        if (name == "Hello")
            item->setProperty("Your answer is", item->property<std::string>("Hello") == "World!");
    };
    item->mapper()->setOnPropertyChange(on_property, nullptr);

    DefaultViewModel viewmodel(&model);
    ViewModelDelegate delegate;

    QTreeView view;
    view.setModel(&viewmodel);
    view.setItemDelegate(&delegate);
    view.show();

    return app.exec();
}
