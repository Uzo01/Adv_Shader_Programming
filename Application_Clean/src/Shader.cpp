
//
//#include <shader.h>
//#include <fstream>
//#include <sstream>
//#include <iostream>

//
//
//Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const char* tessellationEva = nullptr, const char* tessellationControl = nullptr)
//{
//	// 1. retrieve the vertex/fragment source code from filePath
//	std::string vertexCode;
//	std::string fragmentCode;
//	std::string geometryCode;
//	std::string tessEvalCode;
//	std::string tessControlCode;
//
//	std::ifstream vShaderFile;
//	std::ifstream fShaderFile;
//	std::ifstream gShaderFile;
//	std::ifstream tEShaderFile;
//	std::ifstream tCShaderFile;
//
//	// ensure ifstream objects can throw exceptions:
//	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	tEShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//	tCShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
//
//	try
//	{
//		// open files
//		vShaderFile.open(vertexPath);
//		fShaderFile.open(fragmentPath);
//		std::stringstream vShaderStream, fShaderStream;
//		// read file's buffer contents into streams
//		vShaderStream << vShaderFile.rdbuf();
//		fShaderStream << fShaderFile.rdbuf();
//		// close file handlers
//		vShaderFile.close();
//		fShaderFile.close();
//		// convert stream into string
//		vertexCode = vShaderStream.str();
//		fragmentCode = fShaderStream.str();
//		if (geometryPath != nullptr)
//		{
//			gShaderFile.open(geometryPath);
//			std::stringstream gShaderStream;
//			gShaderStream << gShaderFile.rdbuf();
//			gShaderFile.close();
//			geometryCode = gShaderStream.str();
//		}
//		if (tessellationEva != nullptr)
//		{
//			tEShaderFile.open(tessellationEva);
//			std::stringstream tEShaderStream;
//			tEShaderStream << tEShaderFile.rdbuf();
//			tEShaderFile.close();
//			tessEvalCode = tEShaderStream.str();
//		}
//		if (tessellationControl != nullptr)
//		{
//			tCShaderFile.open(tessellationControl);
//			std::stringstream tCShaderStream;
//			tCShaderStream << tCShaderFile.rdbuf();
//			tCShaderFile.close();
//			tessControlCode = tCShaderStream.str();
//		}
//
//	}
//	catch (std::ifstream::failure e)
//	{
//		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
//	}
//	const char* vShaderCode = vertexCode.c_str();
//	const char* fShaderCode = fragmentCode.c_str();
//
//
//	// 2. compile shaders
//	unsigned int vertex, fragment;
//	// vertex shader
//	vertex = glCreateShader(GL_VERTEX_SHADER);
//	glShaderSource(vertex, 1, &vShaderCode, NULL);
//	glCompileShader(vertex);
//	checkCompileErrors(vertex, "VERTEX");
//	// fragment Shader
//	fragment = glCreateShader(GL_FRAGMENT_SHADER);
//	glShaderSource(fragment, 1, &fShaderCode, NULL);
//	glCompileShader(fragment);
//	checkCompileErrors(fragment, "FRAGMENT");
//	unsigned int geometry;
//	if (geometryPath != nullptr)
//	{
//		const char* gShaderCode = geometryCode.c_str();
//		geometry = glCreateShader(GL_GEOMETRY_SHADER);
//		glShaderSource(geometry, 1, &gShaderCode, NULL);
//		glCompileShader(geometry);
//		checkCompileErrors(geometry, "GEOMETRY");
//		std::cout << " loaded GEO" << std::endl;
//	}
//	unsigned int tessEvaluation;
//	if (tessellationEva != nullptr)
//	{
//		const char* tEShader = tessEvalCode.c_str();
//		tessEvaluation = glCreateShader(GL_TESS_EVALUATION_SHADER);
//		glShaderSource(tessEvaluation, 1, &tEShader, NULL);
//		glCompileShader(tessEvaluation);
//		checkCompileErrors(tessEvaluation, "TESS_EVALUTATION");
//		std::cout << " Tessellation evaluation loaded" << std::endl;
//	}
//	unsigned int tessController;
//	if (tessellationControl != nullptr)
//	{
//		const char* tCShader = tessControlCode.c_str();
//		tessController = glCreateShader(GL_TESS_CONTROL_SHADER);
//		glShaderSource(tessController, 1, &tCShader, NULL);
//		glCompileShader(tessController);
//		checkCompileErrors(tessController, "TESS_CONTROLLER");
//		std::cout << " Tessellation control loaded" << std::endl;
//	}
//
//	// shader Program
//	ID = glCreateProgram();
//	glAttachShader(ID, vertex);
//	glAttachShader(ID, fragment);
//	if (geometryPath != nullptr)
//		glAttachShader(ID, geometry);
//	if (tessellationEva != nullptr)
//		glAttachShader(ID, tessEvaluation);
//	if (tessellationControl != nullptr)
//		glAttachShader(ID, tessController);
//	glLinkProgram(ID);
//	checkCompileErrors(ID, "PROGRAM");
//	// delete the shaders as they're linked into our program now and no longer necessery
//	glDeleteShader(vertex);
//	glDeleteShader(fragment);
//	if (geometryPath != nullptr)
//		glDeleteShader(geometry);
//	if (tessellationEva != nullptr)
//		glDeleteShader(tessEvaluation);
//	if (tessellationControl != nullptr)
//		glDeleteShader(tessController);
//	//if (geometryPath != nullptr)
//}
//
//void Shader::use()
//{
//	glUseProgram(ID);
//}
//
//// ------------------------------------------------------------------------
//void Shader::setBool(const std::string& name, bool value) const
//{
//	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
//}
//// ------------------------------------------------------------------------
//void Shader::setInt(const std::string& name, int value) const
//{
//	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
//}
//// ------------------------------------------------------------------------
//void Shader::setFloat(const std::string& name, float value) const
//{
//	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
//}
//// ------------------------------------------------------------------------
//void Shader::setVec2(const std::string& name, const glm::vec2& value) const
//{
//	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//}
//void Shader::setVec2(const std::string& name, float x, float y) const
//{
//	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
//}
//// ------------------------------------------------------------------------
//void Shader::setVec3(const std::string& name, const glm::vec3& value) const
//{
//	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//}
//void Shader::setVec3(const std::string& name, float x, float y, float z) const
//{
//
//	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
//}
//// ------------------------------------------------------------------------
//void Shader::setVec4(const std::string& name, const glm::vec4& value) const
//{
//	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
//}
//void Shader::setVec4(const std::string& name, float x, float y, float z, float w)
//{
//	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
//}
//// ------------------------------------------------------------------------
//void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
//{
//	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//}
//// ------------------------------------------------------------------------
//void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
//{
//	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//}
//// ------------------------------------------------------------------------
//void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
//{
//	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
//}
//// --------------------------------------------------------------------------
//void Shader::setUniformBlock(const std::string& name, unsigned int uniformBlock) const
//{
//	unsigned int uniformBlockIndex = glGetUniformBlockIndex(ID, name.c_str());
//	glUniformBlockBinding(ID, uniformBlockIndex, uniformBlock);
//}
//
//
//void Shader::checkCompileErrors(GLuint shader, std::string type)
//{
//	GLint success;
//	GLchar infoLog[1024];
//	if (type != "PROGRAM")
//	{
//		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
//		if (!success)
//		{
//			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
//			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//		}
//	}
//	else
//	{
//		glGetProgramiv(shader, GL_LINK_STATUS, &success);
//		if (!success)
//		{
//			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
//			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
//		}
//	}
//}










