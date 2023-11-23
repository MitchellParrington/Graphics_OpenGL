#pragma once
#include "bmpch.hpp"

#include "Bamboo/Transform.hpp"

namespace Bam
{
    struct Mesh;
    struct Model;
    struct Node;

    struct BM_API Model
    {
        Node* children = nullptr; // array of all childen nodes. ix:0 should be root node
        Mesh* meshes = nullptr; // array of all meshes
        std::string name = "Unnamed";
        ui32t numChildren = 0;
        ui32t numMeshes = 0;
        uc8t renderIdsGenerated = 0;
    };

    // Access to children or meshes is slow
    struct BM_API Node
    {
        Model* model;
        ui32t* children = nullptr;
        ui32t* meshes = nullptr;
        std::string name = "Unnamed";
        ui32t parent;
        ui32t index;
        ui32t numChildren = 0;
        ui32t numMeshes = 0;
        Transform transform;
        uc8t open = 0;
    };

    BM_API Model* InitModel(ui32t numChildren, ui32t numMeshes);
    BM_API Model* InitModel();
    BM_API Status DeleteModel(Model* model);

    BM_API Status LogModelTreeHierachy(Model* model, ui32t nodeIndex, ui32t depth);
    BM_API Status LogModelTreeHierachy(Model* model);
}