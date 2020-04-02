// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QGraphicsView>

class ApplicationModels;
class SLDElementController;

//! The segment QGraphicsViewItem on the Graphicsscene
class SLDViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    SLDViewWidget(ApplicationModels* sld_model, QWidget* parent = nullptr);
    ~SLDViewWidget();

protected:
    void resizeEvent(QResizeEvent* event);

private:
    std::unique_ptr<SLDElementController> m_sld_controller;
};
