#ifndef SETTING_DIALOG_H
#define SETTING_DIALOG_H

#include "include/share/menu_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class SettingDialog;
}

class SettingDialog : public MenuDialog {
  Q_OBJECT

public:
  SettingDialog(QWidget *parent = nullptr);
  virtual ~SettingDialog();

private:
  Ui::SettingDialog *ui;
};

#endif