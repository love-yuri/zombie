/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 15:34:47
 * @LastEditTime: 2023-12-02 19:59:04
 * @Description: 设置菜单
 */
#include "include/menu/info_dialog.h"
#include "hpp/tools.hpp"
#include "include/share/menu_dialog.h"
#include "../ui/ui_infodialog.h"
#include "include/share/menu_label.h"

InfoDialog::InfoDialog(QWidget *parent) :
  MenuDialog(parent), ui(new Ui::InfoDialog) {
  ui->setupUi(this);
  connect(ui->label, &MenuLabel::clicked, this, [this]() {
    hide();
  });
}


InfoDialog::~InfoDialog() {
}