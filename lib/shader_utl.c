#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <GL/glew.h>

#include "dbg_assert.h"

GLuint compileShader(GLenum shaderType, const char *source) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &source, NULL);
    glCompileShader(shader);

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Shader compilation failed: %s\n", infoLog);
        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

GLuint createShaderProgram(const char *vertexSource, const char *fragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSource);

    if (!vertexShader || !fragmentShader) {
        return 0;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        GLchar infoLog[512];
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        fprintf(stderr, "Shader linking failed: %s\n", infoLog);
        glDeleteProgram(shaderProgram);
        return 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

char* readShaderSource(const char* filePath) {
    FILE* file = fopen(filePath, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", filePath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if (!buffer) {
        fprintf(stderr, "Failed to allocate memory for shader source\n");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);
    buffer[length] = '\0';

    fclose(file);
    return buffer;
}

static void __readFile(char *buffer, const char *filepath)
{
	FILE *file = fopen(filepath, "rt");
	if(file == NULL) {
		fprintf(stderr, "[ERROR]::Failed to open file: %s\n", filepath);
		return;
	}

	// Get the size of the file by getting the location of the cursor at the end of the file
	fseek(file, 0, SEEK_END);
	int64_t fileSize = ftell(file);
	// Move the cursor back at the begining
	fseek(file, 0, SEEK_SET);

	if(fileSize > 0) {
		buffer = (char *)malloc((fileSize + 1) * sizeof(char));
		if(buffer == NULL) {
			fprintf(stderr, "[ERROR]::Failed to allocate memory for file: %s\n", filepath);
			return;
		}
		// Read file
		uint32_t count = fread(buffer, sizeof(char), fileSize, file);

		// Correct buffer size accounting for \r\n characters
		if(count < fileSize) {
			buffer = realloc(buffer, count + 1);
		}

		// Terminate buffer
		buffer[count] = '\0';
	}
	fclose(file);
}

GLuint loadShaderProgram(const char *vertexPath, const char *fragmentPath, const char *geometricPath)
{
	char *vertexSrc;
	__readFile(vertexSrc, vertexPath);

	char *fragmentSrc;
	__readFile(fragmentSrc, fragmentPath);

	char *geometricSrc;
	if(geometricPath != NULL) {
		__readFile(geometricSrc, geometricPath);
	}
	return 1;
}

GLuint loadShaderProgram(const char *vertexPath, const char *fragmentPath) {
    char *vertexSource = readShaderSource(vertexPath);
    char *fragmentSource = readShaderSource(fragmentPath);

    if (!vertexSource || !fragmentSource) {
        return 0;
    }

    GLuint shaderProgram = createShaderProgram(vertexSource, fragmentSource);

    free(vertexSource);
    free(fragmentSource);

    return shaderProgram;
}
