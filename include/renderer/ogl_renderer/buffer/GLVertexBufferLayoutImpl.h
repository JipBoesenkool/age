//
// Created by Jip Boesenkool on 10/06/2018.
//

#ifndef AGE_BUFFERLAYOUTIMPL_H
#define AGE_BUFFERLAYOUTIMPL_H

#include "renderer/renderer/buffer/VertexBufferLayout.h"

#include <string>
#include <unordered_map>

//TODO: Create static
class GLVertexBufferLayoutImpl : public VertexBufferLayoutImpl
{
//Members
private:
	static std::unordered_map<std::string, std::pair<unsigned int, unsigned int> > sGLTypeMap;
//Functions
public:
	unsigned int CalculateStride( std::vector< VertexBufferElement >* elements ) override;
private:
	unsigned int GLTypeOf(const std::string& typeName);
	unsigned int GLSizeOf(const std::string& typeName);
};

#endif //AGE_BUFFERLAYOUT_H
