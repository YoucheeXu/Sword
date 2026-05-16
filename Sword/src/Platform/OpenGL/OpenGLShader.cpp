#include "OpenGLShader.h"

#include "Sword/Core/Log.h"

#include <fstream>
#include <vector>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Sword {

static GLenum ShaderTypeFromString(std::string const& type) {
    if (type == "vertex") {
        return GL_VERTEX_SHADER;
    }
    if (type == "fragment" || type == "pixel") {
        return GL_FRAGMENT_SHADER;
    }

    SW_CORE_ASSERT(false, "Unkown shader type '{0}!", type);
    return 0;
}

OpenGLShader::OpenGLShader(std::string const& filepath) {
    std::string source       = ReadFile(filepath);
    auto        shaderSource = PreProcess(source);
    Compile(shaderSource);
}

OpenGLShader::OpenGLShader(std::string const& vertexSrc, std::string const& fragmentSrc) {
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    Compile(sources);
}

OpenGLShader::~OpenGLShader() {
    glDeleteProgram(m_RendererID);
}

std::string OpenGLShader::ReadFile(std::string const& filepath) {
    std::string   result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    if (in) {
        in.seekg(0, std::ios::end);
        result.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&result[0], result.size());
        in.close();
    } else {
        SW_CORE_ERROR("Could not open file '{0}'", filepath);
    }

    return result;
}

std::unordered_map<GLenum, std::string> OpenGLShader::PreProcess(std::string const& source) {
    std::unordered_map<GLenum, std::string> shaderSources;

    char const* typeToken       = "#type";
    size_t      typeTokenLength = strlen(typeToken);
    size_t      pos             = source.find(typeToken, 0);  //Start of shader type declaration line
    while (pos != std::string::npos) {
        size_t eol = source.find_first_of("\r\n", pos);  //End of shader type declaration line
        SW_CORE_ASSERT(eol != std::string::npos, "Syntax error");
        size_t      begin = pos + typeTokenLength + 1;  //Start of shader type name (after "#type " keyword)
        std::string type  = source.substr(begin, eol - begin);
        SW_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

        size_t nextLinePos
            = source.find_first_not_of("\r\n", eol);  //Start of shader code after shader type declaration line
        SW_CORE_ASSERT(nextLinePos != std::string::npos, "Syntax error");
        pos = source.find(typeToken, nextLinePos);  //Start of next shader type declaration line

        shaderSources[ShaderTypeFromString(type)]
            = (pos == std::string::npos) ? source.substr(nextLinePos) : source.substr(nextLinePos, pos - nextLinePos);
    }

    return shaderSources;
}

void OpenGLShader::Compile(std::unordered_map<GLenum, std::string>& shaderSource) {
    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    GLuint program = glCreateProgram();

    std::vector<GLenum> glShaderIDs;
    glShaderIDs.reserve(shaderSource.size());
    for (auto& kv : shaderSource) {
        GLenum             type   = kv.first;
        std::string const& source = kv.second;

        // Create an empty vertex shader handle
        GLuint shader = glCreateShader(type);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        GLchar const* sourceCStr = (GLchar const*)source.c_str();
        glShaderSource(shader, 1, &sourceCStr, 0);

        // Compile the shader
        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(shader);

            // Use the infoLog as you see fit.
            SW_CORE_ERROR("Shader compilation failure!");
            SW_CORE_ERROR("{0}", infoLog.data());
            SW_CORE_ASSERT(false, "Shader compilation failure!")

            // In this simple program, we'll just leave
            break;
        }

        // Attach our shaders to our program
        glAttachShader(program, shader);

        glShaderIDs.push_back(shader);
    }

    // Link our program
    glLinkProgram(program);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        // The maxLength includes the NULL character
        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        // We don't need the program anymore.
        glDeleteProgram(program);
        // Don't leak shaders either.
        for (auto id : glShaderIDs) {
            glDeleteShader(id);
        }

        // Use the infoLog as you see fit.
        SW_CORE_ERROR("Shader link failure!");
        SW_CORE_ERROR("{0}", infoLog.data());
        SW_CORE_ASSERT(false, "Shader link failure!")

        // In this simple program, we'll just leave
        return;
    }

    // Always detach shaders after a successful link.
    for (auto id : glShaderIDs) {
        glDetachShader(program, id);
    }

    m_RendererID = program;
}

void OpenGLShader::Bind() const {
    glUseProgram(m_RendererID);
}

void OpenGLShader::Unbind() const {
    glUseProgram(0);
}

void OpenGLShader::UploadUniformInt(std::string const& name, int val) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, val);
}

void OpenGLShader::UploadUniformFloat(std::string const& name, float val) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, val);
}

void OpenGLShader::UploadUniformFloat2(std::string const& name, glm::vec2 const& vec) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform2f(location, vec.x, vec.y);
}

void OpenGLShader::UploadUniformFloat3(std::string const& name, glm::vec3 const& vec) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(location, vec.x, vec.y, vec.z);
}

void OpenGLShader::UploadUniformFloat4(std::string const& name, glm::vec4 const& vec) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
}

void OpenGLShader::UploadUniformMat3(std::string const& name, glm::mat3 const& matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void OpenGLShader::UploadUniformMat4(std::string const& name, glm::mat4 const& matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

}  // namespace Sword