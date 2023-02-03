#include<Algernon.h>

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
		std::shared_ptr<Algernon::VertexBuffer> vertexBuffer;
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
		std::shared_ptr<Algernon::IndexBuffer> indexBuffer;
		indexBuffer.reset(Algernon::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		m_VertexArray->SetIndexBuffer(indexBuffer);

		//Shader by glsl
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;	

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position =  u_ViewProjection * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Algernon::Shader(vertexSrc, fragmentSrc));
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

		Algernon::Renderer::Submit(m_Shader, m_VertexArray);

		Algernon::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{

	}
private:
	std::shared_ptr<Algernon::Shader> m_Shader;
	std::shared_ptr<Algernon::VertexArray> m_VertexArray;

	Algernon::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
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