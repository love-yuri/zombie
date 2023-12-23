# 植物大战僵尸

> 基于qt6 的 QGraphics 2D 图形实现 植物大战僵

## 编译环境

1. 仅基于QT6 `QWidget`, 未使用其他模块. 安装qt6-base 即可
2. 使用`cmake`进行构建,未添加`qmake`版本
3. 项目在`archlinux`上编译测试通过

## 如何运行?

### Linux

1. 安装`qt6-base`包 arch系 `sudo pacman -S qt6-base`

2. 安装`cmake` `make` `gcc`等构建工具

3. 克隆本项目`git clone https://github.com/love-yuri/zombie.git`可以使用git也可以自行下载zip

4. 开始构建

   ```bash
   cd zombie # 进入项目
   mkdir build # 创建缓存文件夹
   cd build # 进入缓存文件夹
   cmake .. # 编译cmake文件
   make # 使用make构建项目
   ./yuri # 运行项目
   ```

### Windows

自行百度安装qt后使用qtcreator或者clion进行编译构建.

或者实用 mysy2 安装gcc cmake make qt6-base后进行编译

未在windows下测试

## 项目运行配置文件

`qrc/config/...`

## 目前已知bug 

1. 僵尸boss死亡后概率性复活

## 待更新功能

1. 音频功能 在 `hyprland`下出现音频无法播放
2. 拖动画面居中 在`hyprland`下无法更改鼠标中心点

