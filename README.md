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

> 如果怕麻烦，直接用qt creator 打开本项目的cmakelist文件就行
>
> 如果怕麻烦，直接用qt creator 打开本项目的cmakelist文件就行
>
> 如果怕麻烦，直接用qt creator 打开本项目的cmakelist文件就行

1. 安装QT: [链接](https://mirrors.tuna.tsinghua.edu.cn/qt/official_releases/online_installers/) 下载 `qt-unified-windows-x64-online.exe`

2. 打开安装程序登录账号安装qt，直接开始安装

3. 前面一路默认就行。到选择文件夹那里选择`qt 6.7 for desktop development ` 就行

4. 安装完成后打开qt的目录将以下目录添加到系统环境变量中。如果不会请自行百度

5. ```bash
   # D:\Applications\ 是我电脑的目录，自己电脑自己看着换
   
   D:\Applications\Qt\Tools\CMake_64\bin;
   D:\Applications\Qt\Tools\mingw1120_64\bin;
   D:\Applications\Qt\Tools\Ninja;
   D:\Applications\Qt\6.7.0\mingw_64\bin;
   D:\Applications\Qt\6.7.0\mingw_64\plugins;
   D:\Applications\Qt\6.7.0\mingw_64\plugins\platforms;
   ```

6. 克隆本项目到本地

7. 更改项目中的 `CMakeList.txt`文件

   1. 更改qt库目录: 修改`line 9: set(CMAKE_PREFIX_PATH "D:\\Applications\\Qt\\6.7.0\\mingw_64") # qt库目录` 改为自己的qt库目录

   2. windows如果需要查看输出，请取消 `# 设置项目属性` 将`WIN32_EXECUTABLE` 设置为`FALSE` 或者直接注释 

8. 在终端中打开本项目

9. 新建build文件夹并进入文件夹

10. 使用`cmake .. -G Ninja` 构建

11.  使用`ninja` 开始构建程序

12. 完成，直接运行就行

## 项目运行配置文件

`qrc/config/...`

## 目前已知bug 

1. 僵尸boss死亡后概率性复活

## 待更新功能

1. 音频功能 在 `hyprland`下出现音频无法播放
2. 拖动画面居中 在`hyprland`下无法更改鼠标中心点

## tips

1. 在`main.cpp`中将`yuri::Tools::init();` 更改为`yuri::Tools::init(true)`即可开启日志输入本地文件功能.
