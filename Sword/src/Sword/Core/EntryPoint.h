#ifndef C97DEF10_3EBB_4B55_A850_B4B2A67C0A04
#define C97DEF10_3EBB_4B55_A850_B4B2A67C0A04

#include "Log.h"
#include "Application.h"

#ifdef SW_PLATFORM_WINDOWS

extern Sword::Application* Sword::CreateApplication();

int main(int argc, char** argv) {
    Sword::Log::Init();

    SW_CORE_ERROR("Initialized log!");
    SW_INFO("Initialized log!");

    auto app = Sword::CreateApplication();
    app->Run();
    delete app;
}

#endif

#endif /* C97DEF10_3EBB_4B55_A850_B4B2A67C0A04 */
