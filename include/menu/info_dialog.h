/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 18:45:35
 * @LastEditTime: 2023-12-02 20:01:52
 * @Description: 关于我们弹出框
 */
#ifndef INFO_DIALOG_H
#define INFO_DIALOG_H

#include "include/share/menu_dialog.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class InfoDialog;
}

class InfoDialog : public MenuDialog {
  Q_OBJECT

public:
  InfoDialog(QWidget *parent = nullptr);
  virtual ~InfoDialog();

private:
  Ui::InfoDialog *ui;
};

#endif