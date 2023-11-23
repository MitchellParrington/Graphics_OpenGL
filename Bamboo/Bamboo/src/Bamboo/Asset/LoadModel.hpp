#pragma once
#include "bmpch.hpp"

#include "Vendor/Assimp.hpp"

#include "Bamboo/Vec.hpp"

namespace Bam
{
    struct Mesh;
    struct Model;
    struct Vertex;
    struct IndexStore;
    struct VertexStore;

    BM_API void LoadAssimpVertex(Vertex* vertex, const aiScene* assimpScene, aiMesh* assimpMesh, ui32t assimpVertexIndex);
    BM_API Vertex LoadAssimpVertex(const aiScene* assimpScene, aiMesh* assimpMesh, ui32t assimpVertexIndex);
    BM_API void LoadAssimpVertices(VertexStore* vs, const aiScene* assimpScene, aiMesh* assimpMesh);
    BM_API ui32t NumAssimpMeshTriangles(const aiScene* assimpScene, aiMesh* assimpMesh);
    BM_API Uint3 NumAssimpMeshPrimitives(const aiScene* assimpScene, aiMesh* assimpMesh);
    BM_API void LoadAssimpIndices(IndexStore* is, const aiScene* assimpScene, aiMesh* assimpMesh);
    BM_API IndexStore LoadAssimpIndex(const aiScene* assimpScene, aiMesh* assimpMesh, ui32t assimpFaceIndex);
    BM_API Mesh LoadAssimpMesh(const aiScene* assimpScene, aiMesh* assimpMesh);
    BM_API Uint2 LoadAssimpNode(Model* model, ui32t parentIndex, ui32t nodeIndex, ui32t meshIndex, const aiScene* assimpScene, const aiNode* assimpNode);
    BM_API Model* LoadAssimpModel(const char* filepath);
    BM_API std::future<Bam::Model*> LoadAssimpModel_async(const char* filepath);
    BM_API ui32t NumAssimpNodes(const aiNode* assimpNode);
}