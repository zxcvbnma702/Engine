#pragma once

#include "Algernon/Renderer/Texture.h"
#include "glad/glad.h"

namespace Algernon
{
	class OpenGLTexture2D: public Texture2D
	{
	public:
		//Default White Texture
		OpenGLTexture2D(uint32_t width, uint32_t height);
		//Load Texture from path
		OpenGLTexture2D(const std::string& path);
		virtual ~OpenGLTexture2D();

		virtual uint32_t GetWidth() const override { return m_Width; }
		virtual uint32_t GetHeight() const override { return m_Height; }

		//Set Data to show color
		virtual void SetData(void* data, uint32_t size) override;

		virtual void Bind(uint32_t slot = 0) const override;
	private:
		std::string m_Path;
		uint32_t m_Width, m_Height;
		uint32_t m_RendererID;
		GLenum m_InternalFormat, m_DataFormat;
	};
}


