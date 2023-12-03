/*
 * @Author: love-yuri yuri2078170658@gmail.com
 * @Date: 2023-12-02 16:06:34
 * @LastEditTime: 2023-12-03 16:40:43
 * @Description: 扫描当前目录下所有文件
 */
#include <iostream>
#include <filesystem>
#include <string_view>

namespace fs = std::filesystem;

void listFilesAndDirectories(const fs::path &directory, const std::string_view &prefix) {
  try {
    for (const auto &entry : fs::directory_iterator(directory)) {
      std::string filename = entry.path().filename().string();
      std::cout << "<file>" << prefix  << filename << "</file>" << std::endl;
    }
  } catch (const std::exception &e) {
    std::cerr << "Error reading directory: " << e.what() << std::endl;
  }
}

int main() {
  const std::string path = "/home/yuri/love/zombie/qrc/cards"; // 替换为你的目录路径

  listFilesAndDirectories(path, "cards/");

  return 0;
}
