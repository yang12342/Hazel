#include "hzpch.h"
#include "OpenGLTexture.h"

#include <glad/glad.h>
#include <stb_image.h>


namespace Hazel
{
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		stbi_set_flip_vertically_on_load(true);

		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		HZ_CORE_ASSERT(data, "failed to load image");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataForm = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataForm = GL_RGBA;
		}
		else
		{
			internalFormat = GL_RGB8;
			dataForm = GL_RGB;
		}

		HZ_CORE_ASSERT(internalFormat & dataForm, "Format not support");

		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataForm, GL_UNSIGNED_BYTE, data);

		stbi_image_free(data);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}
