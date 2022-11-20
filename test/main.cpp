#include "../include/FileWatcher.hpp"
#include <iostream>

int main() {
  FileWatcher fw("./test.md");
  fw.watch([](const std::string& path){
    std::cout << "modified: " << path << std::endl;
  });
}
