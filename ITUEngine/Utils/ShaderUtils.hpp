#ifndef ITUENGINE_SHADERUTILS_H
#define ITUENGINE_SHADERUTILS_H

#include <GL/glew.h>
#include <Assertion.hpp>

namespace ShaderUtils {
	// Create a NULL-terminated string by reading the provided file
	static char* readShaderSource(const char* shaderFile)
	{
		FILE* fp = fopen(shaderFile, "r");
		if ( fp == NULL ) { return NULL; }
		fseek(fp, 0L, SEEK_END);
		long size = ftell(fp);
		fseek(fp, 0L, SEEK_SET);
		char* buf = new char[size + 1];
		fread(buf, 1, size, fp);
		buf[size] = ' ';
		fclose(fp);
		return buf;
	}

	// Create a GLSL program object from vertex and fragment shader files
	GLuint initShader(const char* vShaderFile, const char* fShaderFile)
	{
		struct Shader {
			const char* filename;
			GLenum type;
			GLchar* source;
		};

		Shader shaders[2] =
		{
			{ vShaderFile, GL_VERTEX_SHADER, NULL },
			{ fShaderFile, GL_FRAGMENT_SHADER, NULL }
		};

		GLuint program = glCreateProgram( void );

		std::string error;

		for (int i = 0; i < 2; ++i)
		{
			Shader& s = shaders[i];
			s.source = readShaderSource( s.filename );

			error = "Failed to read " << s.filename;
			ASSERT_MSG(shaders[i].source == NULL, error);

			GLuint shader = glCreateShader(s.type);

			glShaderSource(shader, 1, (const GLchar**) &s.source, NULL);

			glCompileShader(shader);

			GLint  compiled;
			glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );

			if ( !compiled ) {

				error = s.filename << " failed to compile:" << std::endl;

				GLint  logSize;
				glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &logSize );
				char* logMsg = new char[logSize];
				glGetShaderInfoLog( shader, logSize, NULL, logMsg );

				error = error << logMsg << std::endl;
				delete [] logMsg;

				ASSERT_MSG(compiled, error);
			}

			delete [] s.source;
			glAttachShader( program, shader );
		}

		// link  and error check
		glLinkProgram(program);

		GLint  linked;
		glGetProgramiv( program, GL_LINK_STATUS, &linked );

		if ( !linked ) {
			error = "Shader program failed to link" << std::endl;

			GLint  logSize;
			glGetProgramiv( program, GL_INFO_LOG_LENGTH, &logSize);
			char* logMsg = new char[logSize];
			glGetProgramInfoLog( program, logSize, NULL, logMsg );
			
			error = error << logMsg << std::endl;

			delete [] logMsg;

			ASSERT_MSG(linked, error);
		}

		// use program object
		glUseProgram(program);

		return program;
	}
}

#endif // ITUENGINE_SHADERUTILS_H