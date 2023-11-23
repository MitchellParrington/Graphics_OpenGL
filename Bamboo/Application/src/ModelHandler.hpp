#pragma once
#include <build/Bamboo.hpp>

void EditNodeProperties(Bam::Node* node);
void ViewRawVertexData(Bam::Mesh* mesh);

void ModelDropdownHierachy(Bam::Model* model);
void ModelDropdownHierachy(Bam::Node* node);

void ModelDropdownHierachy_new1(Bam::Model* model);
void ModelDropdownHierachy_new1(Bam::Node* node);

std::future<Bam::Model*>* LoadModel(std::vector<std::future<Bam::Model*>>& futures, const char* filepath);
std::vector<Bam::Model*>& RetrieveModels(std::vector<std::future<Bam::Model*>>& futures, std::vector<Bam::Model*>& models);