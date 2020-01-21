// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QGraphicsView>
#include <QWheelEvent>
#include <QKeyEvent>

class ViewWidget : public QGraphicsView
{
    Q_OBJECT

public:
    //! The constructor
    ViewWidget(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);
private:


};
