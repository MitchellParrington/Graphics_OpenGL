#pragma once
#include "bmpch.hpp"

#include "Bamboo/Shader.hpp"

#include "Bamboo/Viewport/VertexArray.hpp"
#include "Bamboo/Viewport/VertexBuffer.hpp"
#include "Bamboo/Viewport/IndexBuffer.hpp"
#include "Bamboo/Viewport/VertexStore.hpp"
#include "Bamboo/Viewport/IndexStore.hpp"

namespace Bam
{
    struct BM_API MeshData
    {
        VertexStore vertices;
        IndexStore indices;
    };

    struct BM_API Mesh
    {
        MeshData data;
        VertexArray vertexArray;
        VertexBuffer vertexBuffer;
        IndexBuffer indexBuffer;
        Shader shader;
    };

    //BM_API Mesh InitMesh(ui32t va, ui32t vb, ui32t ib, ui32t sh);
}