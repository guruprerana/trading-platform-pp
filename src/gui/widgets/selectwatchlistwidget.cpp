#include "selectwatchlistwidget.h"
#include "ui_selectwatchlistwidget.h"
#include <QJsonDocument>
#include <QFile>
#include <QJsonArray>
#include <QJsonObject>
#include <QString>
#include <QListWidgetItem>
#include <QVariant>

SelectWatchlistWidget::SelectWatchlistWidget(QWidget *parent) :
  QWidget(parent),
  ui(new Ui::SelectWatchlistWidget) {
  ui->setupUi(this);

  QFile symbolsFile(":/data/symbols.json");

  if (!symbolsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
    return;
  }

  // symbolsFile.open(QIODevice::ReadOnly);
  QJsonDocument symbolsDoc = QJsonDocument::fromJson(symbolsFile.readAll());

  if (symbolsDoc.isNull() || !symbolsDoc.isArray()) {
    // probably should raise error because cannot load json
    qWarning("Could not load symbols.json");
    return;
  }

  if (symbolsDoc.isNull() || !symbolsDoc.isArray()) {
    qWarning("symbols.json does not have right JSON structure.");
  }

  QJsonArray symbols = symbolsDoc.array();

  int j = 0;

  for (QJsonArray::ConstIterator i = symbols.begin(); i != symbols.end(); i++) {
    if (!i->isObject()) {
      continue;
    }

    QJsonObject symbol = i->toObject();

    if (!symbol.contains("symbol") || !symbol.value("symbol").isString()) {
      continue;
    }

    QString symbol_str = symbol.value("symbol").toString();

    QString desc_str = "";


    desc_str = symbol.value("description").toString();



    if (desc_str.length() > 0) {
      ui->availableSymbolsListWidget->addItem(symbol_str + " - " + desc_str);
    } else {
      ui->availableSymbolsListWidget->addItem(symbol_str);
    }

    QListWidgetItem *item = ui->availableSymbolsListWidget->item(j);
    item->setData(LIST_ITEM_WIDGET_DATA_ROLE, QVariant(symbol_str));

    j++;
  }
}

SelectWatchlistWidget::~SelectWatchlistWidget() {
  delete ui;
}

QStringList SelectWatchlistWidget::getSelectedWatchList() const {
  QStringList selectedWatchlist;

  for (int i = 0; i < ui->chosenSymbolsListWidget->count(); ++i) {
    QListWidgetItem *item = ui->chosenSymbolsListWidget->item(i);

    if (!item->data(LIST_ITEM_WIDGET_DATA_ROLE).canConvert<QString>()) {
      qWarning("Cannot get symbol from QListWidgetItem");
      continue;
    }

    selectedWatchlist.push_back(item->data(
                                  LIST_ITEM_WIDGET_DATA_ROLE).value<QString>());
  }

  return selectedWatchlist;
}
