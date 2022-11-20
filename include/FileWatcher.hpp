#pragma once

#include <chrono>
#include <filesystem>
#include <functional>
#include <thread>

using Duration = std::chrono::duration<int, std::milli>;

struct File {
  File(const std::string& path)
      : path{path}, writeTime{std::filesystem::last_write_time(path)} {}

  std::string path;
  std::filesystem::file_time_type writeTime;
};

class FileWatcher {
 public:
  FileWatcher(const std::string& path) : file{path}, running{true} {}
  virtual ~FileWatcher() {}

  void watch(std::function<void()>&& onModified) {
    while (running) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
      auto lastWriteTime = std::filesystem::last_write_time(file.path);
      if (lastWriteTime != file.writeTime) {
        file.writeTime = lastWriteTime;
        onModified();
      }
    }
  }

  void stop() { running = false; }

 private:
  File file;
  bool running;
};
