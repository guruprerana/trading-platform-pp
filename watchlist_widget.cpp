#include "watchlist_widget.h"
#include "ui_watchlist_widget.h"

Watchlist_Widget::Watchlist_Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Watchlist_Widget)
{
    ui->setupUi(this);
}

Watchlist_Widget::~Watchlist_Widget()
{
    delete ui;
}
