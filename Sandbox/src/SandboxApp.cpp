#include "Sword.h"

class ExampleLayer : public Sword::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        // SW_INFO("ExampleLayer::Update");
    }

    void OnEvent(Sword::Event& event) override {
        // SW_TRACE("[O}", event);
        SW_TRACE(event.ToString());
    }
};

class Sandbox : public Sword::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushLayer(new Sword::ImGuiLayer);
    }

    ~Sandbox() {}

private:
};

Sword::Application* Sword::CreateApplication() {
    return new Sandbox();
}
