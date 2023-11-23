#include "bmpch.hpp"
#include "Model.hpp"

#include "Bamboo/Mesh.hpp"

namespace Bam
{
	Model* InitModel(ui32t numChildren, ui32t numMeshes)
	{
        Model* model = new Model{};
		model->numChildren = numChildren;
		model->numMeshes = numMeshes;
		model->children = new Node[numChildren]{};
		model->meshes = new Mesh[numMeshes]{};
        return model;
	}

	Model* InitModel()
	{
		return InitModel(0, 0);
	}

    Status DeleteModel(Model* model)
    {
        delete[] model->children;
        delete model;
        return Status::Success;
    }

    Status LogModelTreeHierachy(Model* model, ui32t nodeIndex, ui32t depth)
    {
        std::string pre;
        for (ui32t i = 0; i < depth; i++)
        {
            pre.append("  |");
        }

        Node& node = model->children[nodeIndex];

        BM_CORE_LOG_INFO("{}",                  pre);
        BM_CORE_LOG_INFO("{} model {}",         pre, (void*)node.model);
        BM_CORE_LOG_INFO("{} index {}",         pre, (void*)node.index);
        BM_CORE_LOG_INFO("{} parent {}",        pre, (void*)node.parent);
        BM_CORE_LOG_INFO("{} num children {}",  pre, (void*)node.numChildren);
        BM_CORE_LOG_INFO("{} children {}",      pre, (void*)node.children);
        BM_CORE_LOG_INFO("{} num meshes {}",    pre, (void*)node.numMeshes);
        BM_CORE_LOG_INFO("{} meshes {}",        pre, (void*)node.meshes);

        for (ui32t i = 0; i < node.numChildren; i++)
        {
            LogModelTreeHierachy(model, node.children[i], depth + 1);
        }
        return Status::Success;
    }

    Status LogModelTreeHierachy(Model* model)
    {
        return LogModelTreeHierachy(model, 0, 0);
    }
}