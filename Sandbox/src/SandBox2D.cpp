#include "SandBox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

SandBox2D::SandBox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandBox2D::OnAttach()
{
	m_SquareVA = Algernon::VertexArray::Create();

	float squareVertices[5 * 4] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	Algernon::Ref<Algernon::VertexBuffer> squareVB;
	squareVB.reset(Algernon::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
	squareVB->SetLayout({
		{ Algernon::ShaderDataType::Float3, "a_Position" }
		});
	m_SquareVA->AddVertexBuffer(squareVB);

	uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
	Algernon::Ref<Algernon::IndexBuffer> squareIB;
	squareIB.reset(Algernon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
	m_SquareVA->SetIndexBuffer(squareIB);

	m_FlatColorShader = Algernon::Shader::Create("assets/shaders/FlatColor.glsl");
}

void SandBox2D::OnDetach()
{
}

void SandBox2D::OnUpdate(Algernon::Timestep ts)
{
	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	Algernon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
	Algernon::RenderCommand::Clear();

	Algernon::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Algernon::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Algernon::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Algernon::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

	Algernon::Renderer::EndScene();
}

void SandBox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void SandBox2D::OnEvent(Algernon::Event& e)
{
	m_CameraController.OnEvent(e);
}
