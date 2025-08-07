#pragma once
#include <string>

namespace Pack
{
	class Shader
	{
	public:
		Shader(const std::string& vertexFileName, const std::string& fragFileName);
		~Shader();

		void Bind() const;
		void UnBind() const;
	protected:
		std::string FileToString(const std::string& fileName);

	private:
		uint32_t m_RendererID;
	};
}