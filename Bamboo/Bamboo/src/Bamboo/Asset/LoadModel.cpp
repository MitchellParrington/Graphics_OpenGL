#include "bmpch.hpp"
#include "LoadModel.hpp"

#include "Vendor/Assimp.hpp"

#include "Bamboo/Asset/Model.hpp"

#include "Bamboo/Viewport/VertexArray.hpp"
#include "Bamboo/Viewport/VertexBuffer.hpp"
#include "Bamboo/Viewport/IndexBuffer.hpp"
#include "Bamboo/Viewport/Vertex.hpp"
#include "Bamboo/Viewport/IndexStore.hpp"
#include "Bamboo/Viewport/VertexStore.hpp"
#include "Bamboo/Viewport/BufferAttrib.hpp"

#include "Timer.hpp"
#include "Bamboo/Transform.hpp"
#include "Bamboo/Mesh.hpp"
#include "Bamboo/Buffer.hpp"
#include "Bamboo/Vec.hpp"

namespace Bam
{

    void LoadAssimpVertex(Vertex* vertex, const aiScene* assimpScene, aiMesh* assimpMesh, ui32t assimpVertexIndex)
    {
        if (assimpMesh->HasPositions())             for (ui32t i = 0; i < 3; i++) vertex->position[i]   = assimpMesh->mVertices[assimpVertexIndex][i];
        if (assimpMesh->HasNormals())               for (ui32t i = 0; i < 3; i++) vertex->normal[i]     = assimpMesh->mNormals[assimpVertexIndex][i];
        if (assimpMesh->HasTextureCoords(0))        for (ui32t i = 0; i < 3; i++) vertex->texCoords[i]  = assimpMesh->mTextureCoords[0][assimpVertexIndex][i];
        if (assimpMesh->HasTangentsAndBitangents()) for (ui32t i = 0; i < 3; i++) vertex->tangents[i]   = assimpMesh->mTangents[assimpVertexIndex][i];
        if (assimpMesh->HasTangentsAndBitangents()) for (ui32t i = 0; i < 3; i++) vertex->bitangents[i] = assimpMesh->mBitangents[assimpVertexIndex][i];
        if (assimpMesh->HasVertexColors(0))         for (ui32t i = 0; i < 4; i++) vertex->color[i]      = assimpMesh->mColors[0][assimpVertexIndex][i];
        return;
    }

    Vertex LoadAssimpVertex(const aiScene* assimpScene, aiMesh* assimpMesh, ui32t assimpVertexIndex)
    {
        Vertex vertex;
        LoadAssimpVertex(&vertex, assimpScene, assimpMesh, assimpVertexIndex);
        return vertex;
    }

    void LoadAssimpVertices(VertexStore* vs, const aiScene* assimpScene, aiMesh* assimpMesh)
    {
        for (ui32t i = 0; i < vs->count; i++)
        {
            LoadAssimpVertex(&vs->data[i], assimpScene, assimpMesh, i);
        }
    }

    ui32t NumAssimpMeshTriangles(const aiScene* assimpScene, aiMesh* assimpMesh)
    {
        ui32t res = 0;
        for (ui32t i = 0; i < assimpMesh->mNumFaces; i++)
        {
            if (assimpMesh->mFaces[i].mNumIndices == 3)
            {
                res++;
            }
        }
        return res;
    }

    Uint3 NumAssimpMeshPrimitives(const aiScene* assimpScene, aiMesh* assimpMesh)
    {
        Uint3 numPrimitive{};
        for (ui32t i = 0; i < assimpMesh->mNumFaces; i++)
        {
            ui32t numIndices = assimpMesh->mFaces[i].mNumIndices;
            if (numIndices > 3) continue;
            numPrimitive[numIndices - 1] += 1;
        }
        return numPrimitive;
    }

    void LoadAssimpIndices(IndexStore* is, const aiScene* assimpScene, aiMesh* assimpMesh)
    {
        ui32t index = 0;
        for (ui32t i = 0; i < assimpMesh->mNumFaces; i++)
        {
            if (assimpMesh->mFaces[i].mNumIndices == 3)
            {
                is->data[index + 0] = assimpMesh->mFaces[i].mIndices[0];
                is->data[index + 1] = assimpMesh->mFaces[i].mIndices[1];
                is->data[index + 2] = assimpMesh->mFaces[i].mIndices[2];
                index += 3;
            }
        }
    }

    Mesh LoadAssimpMesh(const aiScene* assimpScene, aiMesh* assimpMesh)
    {
        //Uint3 numPrimitives = NumAssimpMeshPrimitives(assimpScene, assimpMesh);
        ui32t numTriangles = NumAssimpMeshTriangles(assimpScene, assimpMesh);
        ui32t numVertices = assimpMesh->mNumVertices;
        ui32t numFaces = assimpMesh->mNumFaces;

        Mesh mesh;
        mesh.data.vertices = InitVertexStore(numVertices);
        mesh.data.indices = InitIndexStore(numTriangles * 3);

        LoadAssimpVertices(&mesh.data.vertices, assimpScene, assimpMesh);
        LoadAssimpIndices(&mesh.data.indices, assimpScene, assimpMesh);

        //VertexArrayFormat vaf = InitVertexArrayFormat(sizeof(Vertex));
        //mesh.vertexArray      = InitVertexArray();
        //mesh.vertexBuffer     = InitVertexBuffer(&mesh.data.vertices, BufferState::DynamicDraw);
        //mesh.indexBuffer      = InitIndexBuffer(&mesh.data.indices, 2, Bam::BufferState::StaticDraw);

        //FormatVertexArray(mesh.vertexArray, vaf, 3);
        //FormatVertexArray(mesh.vertexArray, vaf, 3);
        //FormatVertexArray(mesh.vertexArray, vaf, 3);
        //FormatVertexArray(mesh.vertexArray, vaf, 3);
        //FormatVertexArray(mesh.vertexArray, vaf, 3);
        //FormatVertexArray(mesh.vertexArray, vaf, 4);

        return mesh;
    }

    Uint2 LoadAssimpNode(Model* model, ui32t parentIndex, ui32t nodeIndex, ui32t meshIndex, const aiScene* assimpScene, const aiNode* assimpNode)
    {
        Node* node = &model->children[nodeIndex];
        node->model = model;
        node->numChildren = assimpNode->mNumChildren;
        node->numMeshes = assimpNode->mNumMeshes;
        node->index = nodeIndex;
        node->parent = parentIndex;
        node->name = assimpNode->mName.C_Str();

        node->children = new ui32t[node->numChildren]{};
        node->meshes = new ui32t[node->numMeshes]{};


        for (ui32t i = 0; i < node->numMeshes; i++)
        {
            node->meshes[i] = meshIndex;
            model->meshes[meshIndex] = LoadAssimpMesh(assimpScene, assimpScene->mMeshes[assimpNode->mMeshes[i]]);
            meshIndex++;
        }

        nodeIndex += 1;
        for (ui32t i = 0; i < node->numChildren; i++)
        {
            node->children[i] = nodeIndex;
            Uint2 indexes = LoadAssimpNode(model, node->index, nodeIndex, meshIndex, assimpScene, assimpNode->mChildren[i]);
            nodeIndex = indexes[0];
            meshIndex = indexes[1];
        }
        //BM_CORE_LOG_TRACE("{} {}", nodeIndex, meshIndex);
        return { nodeIndex, meshIndex };
    }

    Model* LoadAssimpModel(const char* filepath)
    {
        BM_PROFILE("F:LoadAssimpModel");

        Assimp::Importer importer;
        const aiScene* scene = importer.ReadFile
        (
            filepath,
            aiProcess_CalcTangentSpace
            | aiProcess_Triangulate
            | aiProcess_JoinIdenticalVertices
            | aiProcess_SortByPType
            | aiProcess_FlipUVs
            | aiProcess_CalcTangentSpace
            | aiProcess_GenUVCoords
            | aiProcess_GenSmoothNormals
        );
        
        if (scene == nullptr)
            return nullptr;

        ui32t numAssimpNodes = NumAssimpNodes(scene->mRootNode);
        ui32t numAssimpMeshes = scene->mNumMeshes;

        Model* model = InitModel(numAssimpNodes, numAssimpMeshes);
        LoadAssimpNode(model, (ui32t)-1, (ui32t)0, (ui32t)0, scene, scene->mRootNode);
        //LogModelTreeHierachy(model);

        model->name = scene->mRootNode->mName.C_Str();


        return model;
    }

    std::future<Bam::Model*> LoadAssimpModel_async(const char* filepath)
    {
        return std::async(std::launch::async, (Model* (*)(const char*))Bam::LoadAssimpModel, filepath);
    }

    ui32t NumAssimpNodes(const aiNode* assimpNode) 
    {
        ui32t nodeCount = 1;
        for (ui32t i = 0; i < assimpNode->mNumChildren; i++)
        {
            nodeCount += NumAssimpNodes(assimpNode->mChildren[i]);
        }
        return nodeCount;
    }
}