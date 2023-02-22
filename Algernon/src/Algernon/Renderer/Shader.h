#pragma once

#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

namespace Algernon {

	class Shader
	{
	public:
		virtual ~Shader()= default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int value) = 0;
		virtual void SetFloat3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetFloat4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;

		/// <summary>
		/// Pass in the vertex shader and fragment shader to render the image
		/// </summary>
		/// <param name="vertexSrc"> => Vertex shader program</param>
		/// <param name="fragmentSrc"> => Fragement shader program</param>
		/// <returns>Shader class pointer</returns>
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSrc, const std::string& fragmentSrc);
		static Ref<Shader> Create(const std::string& filepath);

		virtual const std::string& GetName() const = 0;
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, const Ref<Shader>& shader);
		void Add(const Ref<Shader>& shader);

		/// <summary>
		/// Load Shader by filepath, and then add Shader to library.
		/// </summary>
		/// <param name="filepath">Shader filepath</param>
		/// <returns>Shader`s Ref</returns>
		Ref<Shader> Load(const std::string& filepath);
		Ref<Shader> Load(const std::string& name, const std::string& filepath);

		/// <summary>
		/// Get Shader by it`s name, not abolute pathfile.
		/// </summary>
		/// <param name="name">Shader filepath`s name</param>
		/// <returns>Shader`s Ref</returns>
		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name) const;
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};

}

