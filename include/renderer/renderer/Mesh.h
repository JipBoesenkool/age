//
// Created by Jip Boesenkool on 07/06/2018.
//

#ifndef AGE_MESH_H
#define AGE_MESH_H

typedef unsigned int MeshHandle;

struct MeshResource
{
	std::string mName;
	VertexBufferLayout& mLayout;
	const VertexBufferObject& mVbo;
	const IndexBufferObject& mIBo;
};

#endif //AGE_MESH_H