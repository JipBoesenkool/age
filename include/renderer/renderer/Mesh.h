//
// Created by Jip Boesenkool on 07/06/2018.
//

#ifndef AGE_MESH_H
#define AGE_MESH_H

#include <renderer/renderer/buffer/VertexBufferLayout.h>
#include <renderer/renderer/buffer/VertexBuffer.h>
#include <renderer/renderer/buffer/IndexBuffer.h>

typedef unsigned int MeshHandle;

struct Mesh
{
	std::string mName;
	VertexBufferLayout& mLayout;
	const VertexBufferObject& mVbo;
	const IndexBufferObject& mIBo;
};

#endif //AGE_MESH_H
