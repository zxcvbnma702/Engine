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

	Algernon::Renderer2D::BeginScene(m_CameraController.GetCamera());

	Algernon::Renderer2D::DrawQuad({0.0, 0.0}, {1.0, 1.0}, { 0.8f, 0.2f, 0.3f, 1.0f });

	Algernon::Renderer2D::EndScene();
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
