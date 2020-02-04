// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "layereditortoolbar.h"
#include "layereditoractions.h"
#include "resources.h"
#include "styleutils.h"
#include "item_constants.h"
#include <QAction>
#include <QMenu>
#include <QToolButton>

LayerEditorToolBar::LayerEditorToolBar(LayerEditorActions* actions, QWidget* parent)
    : QToolBar(parent)
{
    InitIconResources();

    setIconSize(StyleUtils::ToolBarIconSize());
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto layer_menu = create_layer_menu(actions);

    auto add_layer_button = new QToolButton;
    add_layer_button->setText("Add");
    add_layer_button->setToolTip(
        "Adds a new single layer (default) or new layer-repeater after currently selected.\nIf "
        "nothing is selected, appends to the end. Click and hold to see possible choices.");
    add_layer_button->setPopupMode(QToolButton::MenuButtonPopup);
    add_layer_button->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    add_layer_button->setMenu(layer_menu);
    add_layer_button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    addWidget(add_layer_button);
    connect(add_layer_button, &QToolButton::clicked,
            [layer_menu]() { layer_menu->defaultAction()->triggered(); });

    auto action = new QAction("Clone");
    action->setIcon(QIcon(":/icons/plus-circle-multiple-outline.svg"));
    action->setToolTip("Clones selected layer");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onClone);
    addAction(action);

    action = new QAction("Remove");
    action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));
    action->setToolTip("Removes selected layer");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onRemove);
    addAction(action);

    addSeparator();

    action = new QAction("Up");
    action->setIcon(QIcon(":/icons/arrow-up-circle-outline.svg"));
    action->setToolTip("Moves selected layer up");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onMoveUp);
    addAction(action);

    action = new QAction("Down");
    action->setIcon(QIcon(":/icons/arrow-down-circle-outline.svg"));
    action->setToolTip("Moves selected layer down");
    connect(action, &QAction::triggered, actions, &LayerEditorActions::onMoveDown);
    addAction(action);
}

//! Creates menu to add layer and layer-repeater.

QMenu* LayerEditorToolBar::create_layer_menu(LayerEditorActions* editor_actions)
{
    auto result = new QMenu("Add", this);
    result->setToolTipsVisible(true);
    result->menuAction()->setToolTip("Adds a single layer or layer-repeater.");
    result->setIcon(QIcon(":/icons/plus-circle-outline.svg"));

    // add layer action
    auto action = result->addAction("Adds a single layer");
    action->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    action->setToolTip("Adds a new layer after selected one");
    action->setData(QVariant::fromValue(QString::fromStdString(Constants::LayerItemType)));
    connect(action, &QAction::triggered, editor_actions, &LayerEditorActions::onAddLayer);
    result->setDefaultAction(action);

    // add layer repeater action
    action = result->addAction("Adds layer repeater");
    action->setIcon(QIcon(":/icons/plus-circle-outline.svg"));
    action->setToolTip("Adds a new layer-repeater after selected one.\n"
                       "Layer repeater allows to repeat it content (i.e. bi-layer) "
                       "certain amount of times");
    action->setData(QVariant::fromValue(QString::fromStdString(Constants::MultiLayerItemType)));
    connect(action, &QAction::triggered, editor_actions, &LayerEditorActions::onAddLayer);

    return result;
}
