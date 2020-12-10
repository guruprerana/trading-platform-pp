#include "selectwatchlistwidget.h"
#include "ui_selectwatchlistwidget.h"
#include "qjsondocument.h"
#include "qfile.h"
#include "qjsonarray.h"
#include "qjsonobject.h"
#include "qstring.h"

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
    return;
  }

  QJsonArray symbols = symbolsDoc.array();

  for (QJsonArray::ConstIterator i = symbols.begin(); i != symbols.end(); i++) {
    if (!i->isObject()) {
      continue;
    }

    QJsonObject symbol = i->toObject();
    QString symbol_str = symbol.value("symbol").toString();
    QString desc_str = symbol.value("description").toString();

    if (desc_str.length() > 0) {
      ui->availableSymbolsListWidget->addItem(symbol_str + " - " + desc_str);
    } else {
      ui->availableSymbolsListWidget->addItem(symbol_str);
    }
  }
}

SelectWatchlistWidget::~SelectWatchlistWidget() {
  delete ui;
}
