#ifndef WATCHLIST_WIDGET_H
#define WATCHLIST_WIDGET_H

#include <QWidget>

namespace Ui {
class Watchlist_Widget;
}

class Watchlist_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Watchlist_Widget(QWidget *parent = nullptr);
    ~Watchlist_Widget();

private:
    Ui::Watchlist_Widget *ui;
};

#endif // WATCHLIST_WIDGET_H
