#include "include/menu/last_dialog.h"
#include <qdialog.h>
#include <qlabel.h>
#include <qpixmap.h>
#include <qwidget.h>

LastDialog::LastDialog(QWidget *parent, QString fileName) :
  QDialog(parent) {
  QPixmap pixma(fileName);
  Label *label = new Label(this);
  label->resize(pixma.size());
  label->setPixmap(pixma);
  connect(label, &Label::clicked, [this] {
    close();
    emit clicked();
    deleteLater();
  });
  resize(pixma.size());
  show();
}