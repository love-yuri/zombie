/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-11-30 22:31:31
 * @LastEditTime: 2023-12-03 16:14:12
 * @Description:
 */
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollBar>
#include <qgraphicsitem.h>
#include <qnamespace.h>
#include <qtimer.h>
#include <QGraphicsProxyWidget>

class LongImageScene : public QGraphicsScene {
public:
  LongImageScene(QObject *parent = nullptr) :
    QGraphicsScene(parent) {
    // 加载长图像
    QPixmap longImage("/home/yuri/Qq/Chapter1/map.png");

    // 创建图像项并添加到场景中
    QGraphicsPixmapItem *longImageItem = new QGraphicsPixmapItem(longImage);
    longImageItem->setZValue(0);
    rectangleItem = new QGraphicsRectItem(50, 50, 100, 100);
    rectangleItem->setBrush(QBrush(Qt::red)); // 设置矩形颜色

    // 设置矩形项的Z轴值较高
    rectangleItem->setZValue(1);
    // 创建QWidget
    QPushButton *button = new QPushButton("Click me!");
    button->resize(100, 100);
    button->show();

    // 创建QGraphicsProxyWidget
    QGraphicsProxyWidget *proxyWidget = new QGraphicsProxyWidget;
    proxyWidget->setPos(-100, -100);
    proxyWidget->setWidget(button);
    proxyWidget->setZValue(2);
    addItem(proxyWidget);
    addItem(rectangleItem);
    addItem(longImageItem);
  }

public:
  QGraphicsRectItem *rectangleItem;
};

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);

  // 创建场景
  LongImageScene scene;

  // 创建视图
  QGraphicsView view(&scene);

  // 隐藏滚动条
  view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  // 创建主窗口
  QWidget mainWindow;
  // 创建按钮
  QPushButton button("Move Camera");
  QObject::connect(&button, &QPushButton::clicked, [&]() {
    // 移动视图的滚动条以显示中间区域
    QScrollBar *horizontalScrollBar = view.horizontalScrollBar();
    qDebug() << horizontalScrollBar->value();
    int maxScroll = horizontalScrollBar->maximum();
    QTimer *timer = new QTimer(&mainWindow);
    timer->setInterval(3);
    timer->start();
    QTimer::connect(timer, &QTimer::timeout, [horizontalScrollBar, timer, &scene]() {
      horizontalScrollBar->setValue(horizontalScrollBar->value() - 1);
      qDebug() << scene.rectangleItem->pos();
      scene.rectangleItem->setPos(QPoint(horizontalScrollBar->value(), 0));
      if (horizontalScrollBar->value() == 0) {
        timer->stop();
      }
    });
  });

  // 创建布局
  QVBoxLayout layout;
  layout.addWidget(&view);
  layout.addWidget(&button);

  mainWindow.setLayout(&layout);
  mainWindow.setGeometry(100, 100, 800, 600);
  mainWindow.show();

  return a.exec();
}
