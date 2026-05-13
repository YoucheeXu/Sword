#include "Sword.h"
#include "glm/ext/matrix_float4x4.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/vector_float3.hpp"

class ExampleLayer : public Sword::Layer {
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-2.0f, 2.0f, -1.125f, 1.125f), m_CameraPosition(0.0f), m_SquarePosition(0.0f) {
        // Vertex Array
        m_VertexArray.reset(Sword::VertexArray::Create());

        // Vertex Buffer
        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f, 0.5f, -0.5f, 0.0f, 0.2f,
            0.3f,  0.8f,  1.0f, 0.0f, 0.5f, 0.0f, 0.8f, 0.8f, 0.2f,  1.0f,
        };
        std::shared_ptr<Sword::VertexBuffer> vertexBuffer;
        vertexBuffer.reset(Sword::VertexBuffer::Create(vertices, sizeof(vertices)));

        Sword::BufferLayout layout = {
            {Sword::ShaderDataType::Float3, "a_Position"},
            {Sword::ShaderDataType::Float4, "a_Color"},
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        // Index Buffer
        unsigned int                        indices[3] = {0, 1, 2};
        std::shared_ptr<Sword::IndexBuffer> indexBuffer;
        indexBuffer.reset(Sword::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        m_SquareVertexArray.reset(Sword::VertexArray::Create());

        float squareVertices[3 * 4] = {
            -0.5f,
            -0.5f,
            0.0f,
            0.5f,
            -0.5f,
            0.0f,
            0.5f,
            0.5f,
            0.0f,
            -0.5f,
            0.5f,
            0.0f,
        };
        std::shared_ptr<Sword::VertexBuffer> squareVertexBuffer;
        squareVertexBuffer.reset(Sword::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        Sword::BufferLayout SquareLayout = {
            {Sword::ShaderDataType::Float3, "a_Position"},
        };
        squareVertexBuffer->SetLayout(SquareLayout);
        m_SquareVertexArray->AddVertexBuffer(squareVertexBuffer);

        // Index Buffer
        unsigned int                        squareIndices[6] = {0, 1, 2, 2, 3, 0};
        std::shared_ptr<Sword::IndexBuffer> squareIndexBuffer;
        squareIndexBuffer.reset(Sword::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVertexArray->SetIndexBuffer(squareIndexBuffer);

        std::string vertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        uniform mat4 m_ViewProjection;
        uniform mat4 m_Transform;

        out vec3 v_Position;
        out vec4 v_Color;

        void main() {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = m_ViewProjection * m_Transform * vec4(a_Position, 1.0);
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

        m_Shader.reset(new Sword::Shader(vertexSrc, fragmentSrc));

        std::string blueShaderVertexSrc = R"(
        #version 330 core

        layout(location = 0) in vec3 a_Position;

        uniform mat4 m_ViewProjection;
        uniform mat4 m_Transform;

        out vec3 v_Position;

        void main() {
            v_Position = a_Position;
            gl_Position = m_ViewProjection * m_Transform * vec4(a_Position, 1.0);
        }    
    )";

        std::string blueShaderFragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main() {
            color = vec4(0.2, 0.3, 0.8, 1.0);
        }           
    )";

        m_BlueShader.reset(new Sword::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
    }

    virtual void OnUpdate(Sword::TimeStep ts) override {
        // more smooth
        float moveSpeed = m_CameraMoveSpeed * ts;
        if (Sword::Input::IsKeyPressed(Sword::Key::Left)) {
            m_CameraPosition.x += moveSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::Right)) {
            m_CameraPosition.x -= moveSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::Down)) {
            m_CameraPosition.y += moveSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::Up)) {
            m_CameraPosition.y -= moveSpeed;
        }

        float rotationSpeed = m_CameraRotationSpeed * ts;
        if (Sword::Input::IsKeyPressed(Sword::Key::A)) {
            m_CameraRotation -= rotationSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::D)) {
            m_CameraRotation += rotationSpeed;
        }

        moveSpeed = m_SquareMoveSpeed * ts;
        if (Sword::Input::IsKeyPressed(Sword::Key::J)) {
            m_SquarePosition.x -= moveSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::L)) {
            m_SquarePosition.x += moveSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::K)) {
            m_SquarePosition.y -= moveSpeed;
        } else if (Sword::Input::IsKeyPressed(Sword::Key::I)) {
            m_SquarePosition.y += moveSpeed;
        }

        Sword::RenderCommand::SetClearColor({0.1, 0.1, 0.1, 1});
        Sword::RenderCommand::Clear();

        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);

        Sword::Renderer::BeginScene(m_Camera);

        static glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        for (int y = 0; y < 20; y++) {
            for (int x = 0; x < 20; x++) {
                glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
                glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Sword::Renderer::Submit(m_BlueShader, m_SquareVertexArray, transform);
            }
        }
        glm::mat4 transform2 = glm::translate(glm::mat4(1.0f), m_SquarePosition);
        Sword::Renderer::Submit(m_Shader, m_VertexArray, transform2);

        Sword::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override {}

    virtual void OnEvent(Sword::Event& event) override {
        Sword::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Sword::KeyPressedEvent>(SW_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
    }

    bool OnKeyPressedEvent(Sword::KeyPressedEvent& event) {
        // if (event.GetKeyCode() == Sword::Key::Left) {
        //     m_CameraPosition.x += m_CameraMoveSpeed;
        // } else if (event.GetKeyCode() == Sword::Key::Right) {
        //     m_CameraPosition.x -= m_CameraMoveSpeed;
        // } else if (event.GetKeyCode() == Sword::Key::Down) {
        //     m_CameraPosition.y += m_CameraMoveSpeed;
        // } else if (event.GetKeyCode() == Sword::Key::Up) {
        //     m_CameraPosition.y -= m_CameraMoveSpeed;
        // }

        return false;
    }

private:
    std::shared_ptr<Sword::Shader>      m_Shader;
    std::shared_ptr<Sword::VertexArray> m_VertexArray;

    std::shared_ptr<Sword::Shader>      m_BlueShader;
    std::shared_ptr<Sword::VertexArray> m_SquareVertexArray;

    Sword::OrthographicCamera m_Camera;

    glm::vec3 m_CameraPosition;
    float     m_CameraMoveSpeed = 5.0f;

    float m_CameraRotation      = 0.0f;
    float m_CameraRotationSpeed = 180.0f;

    glm::vec3 m_SquarePosition;
    float     m_SquareMoveSpeed = 1.0f;
};

class Sandbox : public Sword::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() {}

private:
};

Sword::Application* Sword::CreateApplication() {
    return new Sandbox();
}
