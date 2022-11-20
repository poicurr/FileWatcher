#include "../include/FileWatcher.hpp"
#include <iostream>

int main() {
  FileWatcher fw("./test.md");
  fw.watch([](){
    std::cout << "modified!" << std::endl;
  });
}
