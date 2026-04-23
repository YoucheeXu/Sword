#ifndef C97DEF10_3EBB_4B55_A850_B4B2A67C0A04
#define C97DEF10_3EBB_4B55_A850_B4B2A67C0A04

#include "Application.h"
extern Sword::Application* Sword::CreateApplication();

int main(int argc, char** argv) {
  auto app = Sword::CreateApplication();
  app->Run();
  delete app;
}

#endif /* C97DEF10_3EBB_4B55_A850_B4B2A67C0A04 */
