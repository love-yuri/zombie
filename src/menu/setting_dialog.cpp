/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 15:34:47
 * @LastEditTime: 2023-12-02 19:49:54
 * @Description: 设置菜单
 */
#include "include/menu/setting_dialog.h"
#include "include/share/menu_dialog.h"
#include "../ui/ui_settingdialog.h"
#include "include/share/menu_label.h"

SettingDialog::SettingDialog(QWidget *parent) :
  MenuDialog(parent), ui(new Ui::SettingDialog) {
  ui->setupUi(this);
  ui->button->setIsButton(true);
  ui->button_2->setIsButton(true);
  connect(ui->yes, &MenuLabel::clicked, this, [this]() {
    hide();
  });
}

SettingDialog::~SettingDialog() {
  
}