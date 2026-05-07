#include "Application.h"

#include "Events/Event.h"
#include "ImGui/ImGuiLayer.h"
#include "Renderer/Buffer.h"
#include "Sword/Events/ApplicationEvent.h"
#include "Sword/Log.h"
#include "Sword/Renderer/Shader.h"
#include "Sword/Window.h"

#include <cstdint>
#include <functional>
#include <memory>

#include <glad/glad.h>

namespace Sword {

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

Application* Application::s_Instance = nullptr;

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type) {
    switch (type) {
        case Sword::ShaderDataType::Float:
            return GL_FLOAT;
        case Sword::ShaderDataType::Float2:
            return GL_FLOAT;
        case Sword::ShaderDataType::Float3:
            return GL_FLOAT;
        case Sword::ShaderDataType::Float4:
            return GL_FLOAT;
        case Sword::ShaderDataType::Mat3:
            return GL_FLOAT;
        case Sword::ShaderDataType::Mat4:
            return GL_FLOAT;
        case Sword::ShaderDataType::Int:
            return GL_INT;
        case Sword::ShaderDataType::Int2:
            return GL_INT;
        case Sword::ShaderDataType::Int3:
            return GL_INT;
        case Sword::ShaderDataType::Int4:
            return GL_INT;
        case Sword::ShaderDataType::Bool:
            return GL_BOOL;
        case Sword::ShaderDataType::None:
            return GL_NONE;
    }

    SW_CORE_ASSERT(false, "Unknown ShaderDataType!");
    return 0;
}

Application::Application() {
    SW_CORE_ASSERT(!s_Instance, "Application already exists!");
    s_Instance = this;

    m_Window = std::unique_ptr<Window>(Window::Create());
    m_Window->SetEventCallback(BIND_EVENT_FN(Application::OnEvent));

    m_ImGuiLayer = new ImGuiLayer();
    PushOverLay(m_ImGuiLayer);

    // Vertex Array
    glGenVertexArrays(1, &m_VertexArray);
    glBindVertexArray(m_VertexArray);

    // Vertex Buffer
    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f, -0.5f, 0.0f, 0.2f, 0.3f,  0.8f,  1.0f,
        0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f,
    };
    // float vertices[3 * 3] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
    m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

    {
        BufferLayout layout = {
            {ShaderDataType::Float3, "a_Position"},
            {ShaderDataType::Float4, "a_Color"},
        };
        m_VertexBuffer->SetLayout(layout);
    }

    uint32_t index = 0;
    const auto& layout = m_VertexBuffer->GetLayout();
    for (auto const& element : layout) {
        glEnableVertexAttribArray(index);
        glVertexAttribPointer(index,
                              element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE,
                              layout.GetStride(),
                              (void const*)element.Offset);
        index++;
    }
    // Index Buffer
    unsigned int indices[3] = {0, 1, 2};
    m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

    std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }    
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;
        in vec4 v_Color;

        void main() {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
            color = v_Color;
        }           
    )";

    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
}

Application::~Application() {
    delete m_ImGuiLayer;
}

void Application::PushLayer(Layer* layer) {
    m_LayerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverLay(Layer* layer) {
    m_LayerStack.PushOverlay(layer);
    layer->OnAttach();
}

void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(Application::OnWindowClose));

    // SW_CORE_TRACE(e.ToString());

    for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
        (*--it)->OnEvent(e);
        if (e.Handled) {
            break;
        }
    }
}

void Application::Run() {
    WindowResizeEvent e(1980, 720);
    SW_TRACE(e.ToString());

    while (m_Running) {
        glClearColor(0.1, 0.1, 0.1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(m_VertexArray);
        glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

        for (Layer* layer : m_LayerStack) {
            layer->OnUpdate();
        }

        m_ImGuiLayer->Begin();
        for (Layer* layer : m_LayerStack) {
            layer->OnImGuiRender();
        }
        m_ImGuiLayer->End();

        m_Window->OnUpdate();
    }
}

bool Application::OnWindowClose(WindowCloseEvent& e) {
    m_Running = false;
    return true;
}

}  // namespace Sword