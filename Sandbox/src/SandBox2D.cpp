#include "SandBox2D.h"
#include "imgui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

#include <chrono>

SandBox2D::SandBox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f)
{
}

void SandBox2D::OnAttach()
{
	AL_PROFILE_FUNCTION();

	m_CheckerboardTexture = Algernon::Texture2D::Create("assets/textures/Checkerboard.png");
}

void SandBox2D::OnDetach()
{
	AL_PROFILE_FUNCTION();
}

void SandBox2D::OnUpdate(Algernon::Timestep ts)
{
	AL_PROFILE_SCOPE("Sandbox2D::OnUpdate");

	// Update
	m_CameraController.OnUpdate(ts);
	
	// Render
	{
		AL_PROFILE_SCOPE("Renderer Prep");
		Algernon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Algernon::RenderCommand::Clear();
	}
	
	
	{
		AL_PROFILE_SCOPE("Renderer Draw");
		Algernon::Renderer2D::BeginScene(m_CameraController.GetCamera());

		//Algernon::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Algernon ::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Algernon::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		//Algernon::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);

		Algernon::Renderer2D::EndScene();
	}
	
}

void SandBox2D::OnImGuiRender()
{
	AL_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));

	ImGui::End();
}

void SandBox2D::OnEvent(Algernon::Event& e)
{
	m_CameraController.OnEvent(e);
}
