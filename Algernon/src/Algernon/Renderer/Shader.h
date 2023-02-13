#pragma once

#include <string>

namespace Algernon {

	class Shader
	{
	public:
		virtual ~Shader()= default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		/// <summary>
		/// Pass in the vertex shader and fragment shader to render the image
		/// </summary>
		/// <param name="vertexSrc"> => Vertex shader program</param>
		/// <param name="fragmentSrc"> => Fragement shader program</param>
		/// <returns>Shader class pointer</returns>
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
		static Shader* Create(const std::string& filepath);
	};

}

