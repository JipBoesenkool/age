//
// Created by Jip Boesenkool on 12/08/2018.
//

#ifndef AGE_GLUNIFORMBUFFER_H
#define AGE_GLUNIFORMBUFFER_H

#include <renderer/renderer/UniformBuffer.h>
#include <renderer/ogl_renderer/GLUtilities.h>
#include <renderer/renderer/UniformList.h>

class GLUniformBuffer : public UniformBuffer
{
private:
	std::string mBufferName;
	unsigned int mUBOHandle;
	UniformList* mpUniforms;
public:
	GLUniformBuffer();
	~GLUniformBuffer();

	void Init( const std::string& name, UniformList* pUniforms, Shader* shaderBegin, unsigned int shaderCount ) override;
	void Bind() override;
};

#endif //AGE_GLUNIFORMBUFFER_H
