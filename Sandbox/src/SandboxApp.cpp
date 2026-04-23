#include "../../Sword/Sword.h"

class Sandbox : public Sword::Application {
   public:
    Sandbox() {}
    ~Sandbox() {}

   private:
};

Sword::Application* Sword::CreateApplication() {
    return new Sandbox();
}
