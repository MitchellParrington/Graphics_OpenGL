#include <Build/Bamboo.hpp>
#include "loop.hpp"

#include "ModelHandler.hpp"

int loop()
{
	BM_CORE_LOG_FATAL("Start Bamboo Graphics Engine from fooresets");
	BM_PROFILE_PREC("F:DoStuff", Precision::Sec);
	
	Bam::Window window;
	Bam::Gui gui;
	Bam::Viewport viewport;
	
	window.width = 1920; //1280
	window.height = 1018; //1080; //720
	window.title = "Bamboo tuerll";
	window.resizable = 1;
	window.fullscreen = 0;
	window.swapInterval = 1;
	
	viewport.x = 0;
	viewport.y = 0;
	viewport.width = window.width;
	viewport.height = window.height;
	
	gui.keyboard = true;
	gui.docking = true;
	gui.multiViewport = true;
	gui.dark = true;
	
	
	if (Bam::InitWindow(window) == Bam::Status::Fail)
	{
		Bam::ExitWindow(window);
		BM_EXIT();
	}
	
	if (Bam::InitGui(window, gui) == Bam::Status::Fail)
	{
		Bam::ExitGui(gui);
		Bam::ExitWindow(window);
		BM_EXIT();
	}
	
	Bam::SetViewport(viewport);
	
	
	f32ut tmpv[20] = {
		 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
	};
	
	ui32t tmpi[6] = {
		0, 1, 3,
		1, 2, 3
	};
	
	Bam::Shader shader;
	Bam::ShaderSource shaderSource;
	Bam::InitShaderSource(shaderSource, 2);
	shaderSource.files[0] = "../Bamboo/res/shaders/bam_1.vertex.shader"; //"../Bamboo/res/shaders/B_0.vertex.glsl.shader";
	shaderSource.files[1] = "../Bamboo/res/shaders/bam_1.fragment.shader"; //"../Bamboo/res/shaders/B_0.fragment.glsl.shader";
	shaderSource.types[0] = Bam::ShaderType::Vertex;
	shaderSource.types[1] = Bam::ShaderType::Fragment;
	Bam::CompileShaderSource(shaderSource);
	Bam::InitShader(shader, shaderSource);
	Bam::BindShader(shader);
	
	std::vector<std::future<Bam::Model*>> modelFutures;
	std::vector<Bam::Model*> models;
	
	modelFutures.push_back(ASYNC((Bam::Model * (*)(const char*))Bam::LoadAssimpModel, "../Bamboo/res/object/steampunk_underwater_explorer/scene.gltf"));
	
	Bam::VertexArray       va = Bam::InitVertexArray();
	Bam::VertexBuffer      vb = Bam::InitVertexBuffer(4 * 5 * sizeof(f32ut), tmpv, Bam::BufferState::DynamicDraw);
	Bam::IndexBuffer       ib = Bam::InitIndexBuffer(6 * sizeof(ui32t), tmpi, Bam::BufferState::StaticDraw);
	Bam::VertexArrayFormat vf = Bam::InitVertexArrayFormat(5 * sizeof(f32ut));
	Bam::FormatVertexArray(va, vf, 3);
	Bam::FormatVertexArray(va, vf, 2);
	
	
	Bam::SetVertexBufferData(&vb, 0, sizeof(tmpv), tmpv);
	
	
	Bam::FrameBuffer frameBuffer;
	Bam::InitFrameBuffer(frameBuffer, viewport);
	
	
	char inputBuffer[256] = { 0 };
	glm::vec3 view_pos = { 0, 0, 0 };
	glm::mat4 view(1.0f);
	glm::mat4 modelmat(1.0f);
	glm::mat4 projection = glm::perspective(45.0f, (f32ut)window.width / (f32ut)window.height, 0.01f, 500.0f);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	ui32t change = 0;
	while (Bam::ShouldWindowClose(window) == Bam::Status::False)
	{
		Bam::CheckWindowEvents(window);
		Bam::SetViewport(viewport);

		glm::mat4 projection = glm::perspective(45.0f, (f32ut)viewport.width / (f32ut)viewport.height, 0.01f, 500.0f);
	
		// FRAME_BUFFER
	
		view = glm::translate(glm::mat4(1.0f), view_pos);
		modelmat = modelmat;

		Bam::BindShader(shader);
		Bam::BindFrameBuffer(frameBuffer);
		glClearColor(0.235f, 0.286f, 0.247f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	
		//Bam::BindVertexArray(va);
		//BM_CATCH(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

		glm::mat4 mvp = projection * view * modelmat;
		glm::mat4 mv = view * modelmat;
		glm::mat3 mvn = glm::transpose(glm::inverse(view * modelmat));

		Bam::BindVertexArray(va.gluid);
		Bam::BindIndexBuffer(ib.gluid);
		
		SetUniformMatV(4, f, shader.gluid, "uMvp", &mvp[0][0]);
		SetUniformMatV(4, f, shader.gluid, "uMv", &mv[0][0]);
		SetUniformMatV(3, f, shader.gluid, "uMvNorm", &mvn[0][0]);
		//glUniformMatrix4fv(Bam::GetUniformLocation(shader.gluid, "uMvp"), 1, false, &mvp[0][0]);
		
		BM_CATCH(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));




		// SLOW
		for (Bam::Model* model : models)
		{
			if (model->renderIdsGenerated)
			{
				for (ui32t i = 0; i < model->numMeshes; i++)
				{
					Bam::Mesh& mesh = model->meshes[i];

					glm::mat4 mvp = projection * view * modelmat;
					glm::mat4 mv = view * modelmat;
					glm::mat3 mvn = glm::transpose(glm::inverse(view * modelmat));

					Bam::BindVertexArray(mesh.vertexArray.gluid);
					Bam::BindIndexBuffer(mesh.indexBuffer.gluid);
					Bam::BindShader(shader.gluid);

					SetUniformMatV(4, f, shader.gluid, "uMvp", &mvp[0][0]);
					SetUniformMatV(4, f, shader.gluid, "uMv", &mv[0][0]);
					SetUniformMatV(3, f, shader.gluid, "uMvNorm", &mvn[0][0]);

					//BM_TRACE("{}", mesh.indexBuffer.count);
					BM_CATCH(glDrawElements(GL_TRIANGLES, mesh.indexBuffer.count, GL_UNSIGNED_INT, nullptr));
				}
			}
		}
		
		Bam::BindShader(0);
		Bam::BindFrameBuffer(0);
	
		// END FRAME_BUFFER
	
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Bam::BindShader(0);
	

		Bam::StartGuiFrame();
		ImGui::DockSpaceOverViewport();
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Save Editor State"))
				{
					ImGui::SaveIniSettingsToDisk(gui.io->IniFilename);
				}
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				if (ImGui::MenuItem("Save Editor State"))
				{
					ImGui::SaveIniSettingsToDisk(gui.io->IniFilename);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
		ImGui::Begin("Viewport", 0, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);

		ImVec2 win_size = ImGui::GetContentRegionAvail();
		ImGui::Image((void*)frameBuffer.colorBuffer, win_size, { 0, 0 }, { 1, -1 });
		if (viewport.width != (ui32t)win_size.x || viewport.height != (ui32t)win_size.y)
		{
			viewport.width = (ui32t)win_size.x;
			viewport.height = (ui32t)win_size.y;
			Bam::SetFrameBuffer(frameBuffer, viewport);
	
		}

		if (ImGui::IsWindowFocused())
		{
			if (glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS);
			if (glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS);
			if (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS);
			if (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS);
		}

		ImGui::End();
		ImGui::PopStyleVar();
	

		ImGui::Begin("Left");
		if (ImGui::Button("Restart Shaders"))
		{
			BM_PROFILE_PREC("S:RestartShaders", Precision::Milli);
			Bam::CompileShaderSource(shaderSource);
			Bam::InitShader(shader, shaderSource);
		}


		if (ImGui::Button("Submit Models For Rendering"))
		{
			for (Bam::Model* model : models)
			{
				if (model->renderIdsGenerated == 0)
				{
					for (ui32t i = 0; i < model->numMeshes; i++)
					{
						Bam::Mesh& mesh = model->meshes[i];
						Bam::VertexArrayFormat vaf = Bam::InitVertexArrayFormat(sizeof(Bam::Vertex));
						mesh.vertexArray      = Bam::InitVertexArray();
						mesh.vertexBuffer     = Bam::InitVertexBuffer(&mesh.data.vertices, Bam::BufferState::DynamicDraw);
						mesh.indexBuffer      = Bam::InitIndexBuffer(&mesh.data.indices, Bam::BufferState::StaticDraw);

						Bam::FormatVertexArray(mesh.vertexArray, vaf, 3);
						Bam::FormatVertexArray(mesh.vertexArray, vaf, 3);
						Bam::FormatVertexArray(mesh.vertexArray, vaf, 3);
						Bam::FormatVertexArray(mesh.vertexArray, vaf, 3);
						Bam::FormatVertexArray(mesh.vertexArray, vaf, 3);
						Bam::FormatVertexArray(mesh.vertexArray, vaf, 4);
					}
					model->renderIdsGenerated = 1;
				}
			}
		}


		if (ImGui::Button("Clear##modelfilepathinputbuttonclear"))
		{
			memset((void*)inputBuffer, 0, 256);
			inputBuffer[0] = '/';
			inputBuffer[255] = 0x0;
		}
		ImGui::SameLine();
		if (ImGui::Button("Load##modelfilepathinputbuttonload"))
		{
			LoadModel(modelFutures, (const char*)inputBuffer);
			RetrieveModels(modelFutures, models);
		}
		ImGui::SameLine();
		if (ImGui::Button("#"))
		{
			RetrieveModels(modelFutures, models);
		}
		ImGui::SameLine();
		ImGui::InputText("##modelfilepathinputbox", inputBuffer, 255);

		ImGui::SameLine();
		if (ImGui::Button("Log Models"))
		{
			for (Bam::Model* model : models)
			{
				BM_INFO("Log Model {}", (void*)model);
			}
		}

		for (Bam::Model* model : models)
		{
			//ModelDropdownHierachy(model);
			ModelDropdownHierachy_new1(model);
		}
	
		
	
		ImGui::End();
	
		ImGui::Begin("Bottom");

		if (ImGui::Button("Save Editor State"))
		{
			ImGui::SaveIniSettingsToDisk(gui.io->IniFilename);
		}

		ImGui::End();
	
		ImGui::Begin("Right");
		
		ImGui::DragFloat3("camera pos", &view_pos.x);

		ImGui::End();
	
		ImGui::Begin("Spare");
		ImGui::End();
	
		ImGui::ShowDemoWindow();
	
	
		Bam::RenderGui(gui);
		Bam::RenderWindow(window);
	}
	
	Bam::DeleteIndexBuffer(&ib);
	Bam::DeleteVertexBuffer(&vb);
	Bam::DeleteVertexArray(va);
	Bam::DeleteFrameBuffer(frameBuffer);
	Bam::DeleteShaderSource(shaderSource);
	Bam::DeleteShader(shader);
	
	Bam::ExitGui(gui);
	Bam::ExitWindow(window);
	return -1;
}