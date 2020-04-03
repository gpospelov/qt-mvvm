// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importdataeditor.h"
#include "realdatamodel.h"
#include "styleutils.h"
#include "realdatamodel.h"
#include "datasetitem.h"
#include <mvvm/widgets/standardtreeviews.h>
#include <mvvm/plotting/graphcanvas.h>
#include <QAction>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>

using namespace ModelView;

ImportDataEditor::ImportDataEditor(RealDataModel* model, QWidget* parent)
    : QWidget(parent), model(model), toolbar(new QToolBar), topitems_tree(new TopItemsTreeView(model)),
    graph_canvas(new GraphCanvas), property_tree(new PropertyTreeView)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(toolbar);
    layout->addLayout(create_bottom_layout());
    setup_toolbar();
    setup_views();
}

void ImportDataEditor::setup_toolbar()
{
    toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto load_action = new QAction("Famous Loader");
    load_action->setToolTip("Summons the famous data loader.");
    load_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    toolbar->addAction(load_action);
    //    connect(reset_view, &QToolButton::clicked, [this]() { resetViewport(); });
}

void ImportDataEditor::setup_views()
{

}

QBoxLayout *ImportDataEditor::create_bottom_layout()
{
    auto result = new QHBoxLayout;
    result->addWidget(topitems_tree, 1);
    result->addWidget(graph_canvas, 5);
    result->addWidget(property_tree, 1);
    return result;
}
