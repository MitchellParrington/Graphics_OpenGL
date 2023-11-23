#include <Build/Bamboo.hpp>

#include "ModelHandler.hpp"


void ModelDropdownHierachy_new1(Bam::Model* model)
{
	constexpr static const ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

	if (ImGui::BeginTable("ModelDropdownHierachy", 1, flags))
	{
		ImGui::TableSetupColumn(model->name.c_str(), ImGuiTableColumnFlags_NoClip | ImGuiTableColumnFlags_NoHide);
		ModelDropdownHierachy_new1(&model->children[0]);

		ImGui::EndTable();
	}	
}

void ModelDropdownHierachy_new1(Bam::Node* node)
{
	char buffer[128] = { 0x0 };

	ImGui::PushID((const void*)node);
	ImGui::TableNextRow();
	ImGui::TableSetColumnIndex(0);
	if (node->open)
		int fmtsuc = sprintf_s(buffer, "- %s", node->name.c_str());
	else
		int fmtsuc = sprintf_s(buffer, "> %s", node->name.c_str());
	uc8t clicked0 = ImGui::Selectable(buffer, false, ImGuiSelectableFlags_SpanAllColumns);
	uc8t clicked1 = ImGui::IsItemClicked(1);

	node->open = clicked0 ^ node->open;

	ImGui::SetNextWindowSize({ 600, 100 });
	if (ImGui::BeginPopup("Node Popup"))
	{
		EditNodeProperties(node);
		ImGui::EndPopup();
	}
	if (clicked1)
	{
		ImGui::OpenPopup("Node Popup");
	}

	ImGui::Indent(10.0f);
	for (ui32t i = 0; i < node->numMeshes * node->open; i++)
	{
		uc8t clicked0;
		Bam::Mesh* mesh = &node->model->meshes[node->meshes[i]];
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		int fmtsuc = sprintf_s(buffer, "- Mesh %i", node->meshes[i]);
		if (fmtsuc)
			clicked0 = ImGui::Selectable(buffer, false, ImGuiSelectableFlags_SpanAllColumns);
		else
			clicked0 = ImGui::Selectable("Unnamed Mesh", false, ImGuiSelectableFlags_SpanAllColumns);
		uc8t clicked1 = ImGui::IsItemClicked(1);

		if (clicked1)
		{
			ImGui::OpenPopup("Mesh Popup");
			ImGui::SetNextWindowSize({ 900, 200 });
		}
		if (ImGui::BeginPopup("Mesh Popup"))
		{
			//ViewRawVertexData(mesh);
			ImGui::TextDisabled("Mesh");
			ImGui::EndPopup();
		}

	}

	for (ui32t i = 0; i < node->numChildren * node->open; i++)
	{
		Bam::Node* child = &node->model->children[node->children[i]];
		ModelDropdownHierachy_new1(child);
	}
	ImGui::Unindent(10.0f);

	ImGui::PopID();
}

void EditNodeProperties(Bam::Node* node)
{
	if (node == nullptr) return;
	static char buffer[256]{ 0 };
	static Bam::Node* master = nullptr;

	if (node != master)
	{
		memset(buffer, 0x0, 256);
		if (node->name.size() < 255)
		{
			memcpy(buffer, node->name.data(), node->name.size());
		}
	}
	master = node;

	if (ImGui::Button("Clear"))
	{
		memset(buffer, 0x0, 256);
	}
	ImGui::SameLine();
	if (ImGui::Button("Rename"))
	{
		buffer[255] = 0x0;
		node->name = buffer;
	}
	ImGui::SameLine();
	//ImGui::InputText("##bufferinputbox", buffer, 255);
	ImGui::SetNextItemWidth(ImGui::GetContentRegionAvail().x);
	ImGui::InputTextWithHint("##bufferintputboxzx", node->name.c_str(), buffer, 255);
}


void ViewRawVertexData(Bam::Mesh* mesh)
{
	if (ImGui::BeginTable("ModelDropdownHierachy", 6))
	{
		ImGui::TableSetupColumn("Position");
		ImGui::TableSetupColumn("Normal");
		ImGui::TableSetupColumn("TexCoord");
		ImGui::TableSetupColumn("Tangent");
		ImGui::TableSetupColumn("Bitangent");
		ImGui::TableSetupColumn("Color");
		ImGui::TableHeadersRow();

		for (ui32t i = 0; i < mesh->data.vertices.count; i++)
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::SliderFloat3("##pos", &mesh->data.vertices.data[i].position[0], -1.0f, 1.0f);
			ImGui::TableSetColumnIndex(1);
			ImGui::SliderFloat3("##norm", &mesh->data.vertices.data[i].normal[0], -1.0f, 1.0f);
			ImGui::TableSetColumnIndex(2);
			ImGui::SliderFloat3("##tex", &mesh->data.vertices.data[i].texCoords[0], -1.0f, 1.0f);
			ImGui::TableSetColumnIndex(3);
			ImGui::SliderFloat3("##tan", &mesh->data.vertices.data[i].tangents[0], -1.0f, 1.0f);
			ImGui::TableSetColumnIndex(4);
			ImGui::SliderFloat3("##bit", &mesh->data.vertices.data[i].bitangents[0], -1.0f, 1.0f);
			ImGui::TableSetColumnIndex(5);
			ImGui::SliderFloat4("##col", &mesh->data.vertices.data[i].color[0], -1.0f, 1.0f);

		}

		ImGui::EndTable();
	}
}



void ModelDropdownHierachy(Bam::Model* model)
{
	constexpr static const ImGuiTableFlags flags = ImGuiTableFlags_BordersV | ImGuiTableFlags_BordersOuterH | ImGuiTableFlags_Resizable | ImGuiTableFlags_RowBg | ImGuiTableFlags_NoBordersInBody;

	if (ImGui::BeginTable("ModelDropdownHierachy", 6, flags))
	{
		// The first column will use the default _WidthStretch when ScrollX is Off and _WidthFixed when ScrollX is On
		ImGui::TableSetupColumn(model->name.c_str(), ImGuiTableColumnFlags_NoClip | ImGuiTableColumnFlags_NoHide); //model->name
		ImGui::TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x * 0.1f);
		ImGui::TableSetupColumn("Children", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x * 0.1f);
		ImGui::TableSetupColumn("Meshes", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x * 0.1f);
		ImGui::TableSetupColumn("Vertices", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x * 0.1f);
		ImGui::TableSetupColumn("Indices", ImGuiTableColumnFlags_WidthFixed, ImGui::GetContentRegionAvail().x * 0.1f);
		ImGui::TableHeadersRow();


		ModelDropdownHierachy(&model->children[0]);

		ImGui::EndTable();
	}
}

void ModelDropdownHierachy(Bam::Node* node)
{
	ImGui::PushID((const void*)node);
	ImGui::TableNextRow();

	// Name
	ImGui::TableSetColumnIndex(0);
	ImGui::GetStyle().IndentSpacing = 7.0f;
	//bool open = ImGui::TreeNodeEx((const void*)node, ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen, "Node %i %p", node->index, (const void*)node);
	if (ImGui::BeginPopup("Node Popup"))
	{
		ImGui::Text("hello ther siir");
		ImGui::EndPopup();
	}
	bool open = ImGui::TreeNodeEx((const void*)node, ImGuiTreeNodeFlags_SpanFullWidth | ImGuiTreeNodeFlags_DefaultOpen, "%s", node->name.c_str());
	bool a = ImGui::IsItemClicked(1);
	//bool a = ImGui::IsItemClicked();
	//ImGui::OpenPopupOnItemClick("Node Popup", ImGuiPopupFlags_MouseButtonRight);
	

	if (a) ImGui::OpenPopup("Node Popup");

	// Type
	ImGui::TableSetColumnIndex(1);
	ImGui::TextDisabled("Node");

	// Childs / Vertices
	ImGui::TableSetColumnIndex(2);
	ImGui::TextDisabled("%i", node->numChildren);
	
	// Meshes / Indices	
	ImGui::TableSetColumnIndex(3);
	ImGui::TextDisabled("%i", node->numMeshes);

	// Childs / Vertices
	ImGui::TableSetColumnIndex(4);
	ImGui::TextDisabled("--");

	// Meshes / Indices	
	ImGui::TableSetColumnIndex(5);
	ImGui::TextDisabled("--");

	if (open)
	{
		for (ui32t i = 0; i < node->numMeshes; i++)
		{
			Bam::Mesh* mesh = &node->model->meshes[node->meshes[i]];
			ImGui::TableNextRow();

			// Name
			ImGui::TableSetColumnIndex(0);
			ImGui::TreeNodeEx((const void*)node, ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_SpanFullWidth, "Mesh %i %p", node->meshes[i], (const void*)mesh);
			bool a = ImGui::IsItemHovered();

			// Type
			ImGui::TableSetColumnIndex(1);
			ImGui::TextDisabled("Mesh");

			// Children
			ImGui::TableSetColumnIndex(2);
			ImGui::TextDisabled("--");

			// Meshes	
			ImGui::TableSetColumnIndex(3);
			ImGui::TextDisabled("--");

			// Vertices
			ImGui::TableSetColumnIndex(4);
			ImGui::TextDisabled("%i %i", mesh->data.vertices.count, mesh->vertexBuffer.gluid);

			// Indices	
			ImGui::TableSetColumnIndex(5);
			ImGui::TextDisabled("%i %i", mesh->data.indices.count, mesh->indexBuffer.gluid);
		}

		for (ui32t i = 0; i < node->numChildren; i++)
		{
			Bam::Node* child = &node->model->children[node->children[i]];
			ModelDropdownHierachy(child);
		}
		ImGui::TreePop();
	}

	ImGui::PopID();
}

std::future<Bam::Model*>* LoadModel(std::vector<std::future<Bam::Model*>>& futures, const char* filepath)
{
	futures.push_back(ASYNC((Bam::Model * (*)(const char*))Bam::LoadAssimpModel, filepath));
	return &futures.back();
}

std::vector<Bam::Model*>& RetrieveModels(std::vector<std::future<Bam::Model*>>& futures, std::vector<Bam::Model*>& models)
{
	ui32t count = 0;
	ui32t failed = 0;
	ui32t total = futures.size();
	futures.erase(
		std::remove_if(
			futures.begin(),
			futures.end(),
			[&](std::future<Bam::Model*>& future) -> bool {
				if (future.valid() == true && future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
				{
					Bam::Model* model = future.get();
					if (model != nullptr)
					{
						count++;
						models.push_back(model);
					}
					else
					{
						failed++;
					}
					return true;
				}
				else
				{
					return false;
				}
			}
		),
		futures.end());
	BM_INFO("Importing Ready Models : {} of {} ({} failed) with {} remaining", count, total, failed, futures.size());
	return models;
}