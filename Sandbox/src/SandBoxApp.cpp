#include<Algernon.h>

#include <glm/gtc/matrix_transform.hpp>
#include <imgui/imgui.h>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/OpenGLShader.h>

class ExampleLayer : public Algernon::Layer
{
public:
	ExampleLayer(): Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		m_VertexArray.reset(Algernon::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		//Create VertexBuffer
		Algernon::Ref<Algernon::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Algernon::VertexBuffer::Create(vertices, sizeof(vertices)));

		//Set VertexBuffer layout
		Algernon::BufferLayout layout = {
			{ Algernon::ShaderDataType::Float3, "a_Position" },
			{ Algernon::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };

		//Create IndexBuffer
		Algernon::Ref<Algernon::IndexBuffer> indexBuffer;
		indexBuffer.reset(Algernon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Shader by glsl
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;	

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			uniform vec3 u_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
				color = vec4(u_Color, 1.0);
			}
		)";

		m_Shader.reset(Algernon::Shader::Create(vertexSrc, fragmentSrc));

		//////// square /////////////
		m_SquareVA.reset(Algernon::VertexArray::Create());
		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Algernon ::Ref<Algernon::VertexBuffer> squareVB;
		squareVB.reset(Algernon::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Algernon::ShaderDataType::Float3, "a_Position" },
			{ Algernon::ShaderDataType::Float2, "a_TexCoord" }
			});

		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Algernon::Ref<Algernon::IndexBuffer> squareIB;
		squareIB.reset(Algernon::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		m_TextureShader.reset(Algernon::Shader::Create("assets/shaders/Texture.glsl"));

		m_Texture = Algernon::Texture2D::Create("assets/textures/Checkerboard.png");
		m_CTexture = Algernon::Texture2D::Create("assets/textures/ChernoLogo.png");

		std::dynamic_pointer_cast<Algernon::OpenGLShader>(m_TextureShader)->Bind();
		std::dynamic_pointer_cast<Algernon::OpenGLShader>(m_TextureShader)->UploadUniformInt("u_Texture", 0);

	}

	void OnUpdate(Algernon::Timestep ts) override
	{
		if (Algernon::Input::IsKeyPressed(AL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Algernon::Input::IsKeyPressed(AL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Algernon::Input::IsKeyPressed(AL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Algernon::Input::IsKeyPressed(AL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Algernon::Input::IsKeyPressed(AL_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		if (Algernon::Input::IsKeyPressed(AL_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Algernon::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Algernon::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Algernon::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Algernon::OpenGLShader>(m_Shader)->Bind();
		std::dynamic_pointer_cast<Algernon::OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_Color);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Algernon::Renderer::Submit(m_Shader, m_VertexArray, transform);
			}
		}

		m_Texture->Bind();
		Algernon::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		m_CTexture->Bind();
		Algernon::Renderer::Submit(m_TextureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		Algernon::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_Color));
		ImGui::End();

	}
private:
	Algernon::Ref<Algernon::Shader> m_Shader;
	Algernon::Ref<Algernon::VertexArray> m_VertexArray;

	Algernon::Ref<Algernon::Shader>  m_TextureShader;
	Algernon::Ref<Algernon::VertexArray> m_SquareVA;

	Algernon::Ref<Algernon::Texture2D> m_Texture, m_CTexture;

	Algernon::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };
};

class SandBox : public Algernon::Application {
public:
	SandBox() {
		PushLayer(new ExampleLayer());
	}
	~SandBox() {
	}
};

Algernon::Application* Algernon::CreateApplication() {
	return new SandBox();
}