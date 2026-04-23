#ifndef APPLICATION_H
#define APPLICATION_H

#pragma once

namespace Sword {

class __declspec(dllexport) Application {
 public:
  Application();
  virtual ~Application();

  void Run [[noreturn]] ();

 private:
};

// To be defined in CLIENT
Application* CreateApplication();
}  // namespace Sword

#endif