#include <iostream>
#include <fstream>

#include <GL/glew.h>

#include <VistaBase/VistaStreamUtils.h>

#include "ShaderRegistry.hpp"

namespace {
	void readFileIntoString(std::string filename, std::string &result) {
		std::ifstream file(filename.c_str());
		if(file) {
			// get size of file
			file.seekg(0, std::ios::end);
			std::streampos length = file.tellg();
			file.seekg(0, std::ios::beg);

			std::vector<char> buffer(length);
			file.read(&buffer[0],length);

			result = std::string(buffer.begin(), buffer.end());
		}
	}
}

namespace rhapsodies {
	GLuint ShaderRegistry::RegisterShader(std::string name,
										  GLenum type,
										  std::string path) {

		vstr::debug() << "Registering shader: " << name << std::endl;
		
		// create gl shader object
		GLuint shader = glCreateShader(type);

		// read data from path
		std::string sShader;
		readFileIntoString(path, sShader);

		const char* strShaderData = sShader.c_str();
		glShaderSource(shader, 1, &strShaderData, NULL);

		// vstr::debug() << "Shader source:" << std::endl
		// 			  << strShaderData << std::endl << std::endl;
		
		glCompileShader(shader);

		GLint status;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
		
		if(status == GL_FALSE)	{
			GLint infoLogLength;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

			const char *strShaderType = NULL;
			switch(type) {
			case GL_VERTEX_SHADER: strShaderType = "vertex"; break;
			case GL_GEOMETRY_SHADER: strShaderType = "geometry"; break;
			case GL_FRAGMENT_SHADER: strShaderType = "fragment"; break;
			case GL_COMPUTE_SHADER: strShaderType = "compute"; break;
			}

			std::cerr << "Compile failure in " << strShaderType
					  << " shader: " << name << std::endl
					  << strInfoLog << std::endl;
			
			delete[] strInfoLog;
		}

		m_mapShader[name] = shader;
		return shader;
	}

	GLuint ShaderRegistry::RegisterProgram(std::string name,
										   std::vector<std::string> shader_names) {
		
		vstr::debug() << "Registering program: " << name << std::endl;
		
		GLuint program = glCreateProgram();

		for(size_t iLoop = 0; iLoop < shader_names.size(); iLoop++)
			glAttachShader(program, m_mapShader[shader_names[iLoop]]);

		glLinkProgram(program);

		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);

		if(status == GL_FALSE)	{
			GLint infoLogLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

			GLchar *strInfoLog = new GLchar[infoLogLength + 1];
			glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
			std::cerr << "Linker failure: " << strInfoLog << std::endl;
			delete[] strInfoLog;
		}

		for(size_t iLoop = 0; iLoop < shader_names.size(); iLoop++)
			glDetachShader(program, m_mapShader[shader_names[iLoop]]);

		m_mapProgram[name] = program;
		return program;
	}

	GLuint ShaderRegistry::RegisterUniform(std::string program_name,
										   std::string uniform_name) {
		GLuint location = glGetUniformLocation(GetProgram(program_name),
											   uniform_name.c_str());
		m_mapUniform[program_name][uniform_name] = location;
		return location;		
	}

	GLuint ShaderRegistry::GetProgram(std::string name) {
		std::map<std::string, GLuint>::iterator it = m_mapProgram.find(name);

		if(it == m_mapProgram.end()) {
			vstr::err() << "Program " << name << " not found in ShaderRegistry!"
						<< std::endl;
			return ~0;
		}
		
		return it->second;
	}

	GLuint ShaderRegistry::GetUniform(std::string program_name,
									  std::string uniform_name) {
		return m_mapUniform[program_name][uniform_name];
	}
}
