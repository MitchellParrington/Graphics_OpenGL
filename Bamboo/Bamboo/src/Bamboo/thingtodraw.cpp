#include "bmpch.hpp"
//#include "thingtodraw.hpp"
//
//#include "Vendor/Glfw.hpp"
//#include "Vendor/Glad.hpp"
//#include "Vendor/Imgui.hpp"
//#include "Vendor/Entt.hpp"
//
//#include "Window.hpp"
//#include "Shader.hpp"
//#include "Mesh.hpp"
//#include "Timer.hpp"
//#include "Async.hpp"
//
//#include "Viewport/Viewport.hpp"
//#include "Viewport/FrameBuffer.hpp"
//#include "Viewport/VertexArray.hpp"
//#include "Viewport/VertexBuffer.hpp"
//#include "Viewport/IndexBuffer.hpp"
//#include "Viewport/BufferAttrib.hpp"
//
//#include "Asset/Model.hpp"
//#include "Asset/LoadModel.hpp"
//
//#include "Gui/Gui.hpp"
//
//namespace Bam
//{
//	void DoStuff()
//	{
//		BM_CORE_LOG_FATAL("Start Bamboo Graphics Engine from sandbox");
//		BM_PROFILE_PREC("F:DoStuff", Bam::Precision::Sec);
//
//		Bam::Window window;
//		Bam::Gui gui;
//		Bam::Viewport viewport;
//
//		window.width = 1920; //1280
//		window.height = 1018; //1080; //720
//		window.title = "Bamboo tuerl";
//		window.resizable = 1;
//		window.fullscreen = 0;
//		window.swapInterval = 1;
//
//		viewport.x = 0;
//		viewport.y = 0;
//		viewport.width = window.width;
//		viewport.height = window.height;
//
//		gui.keyboard = true;
//		gui.docking = true;
//		gui.multiViewport = true;
//		gui.dark = true;
//
//
//		if (Bam::InitWindow(window) == Bam::Status::Fail)
//		{
//			Bam::ExitWindow(window);
//			BM_EXIT();
//		}
//
//		if (Bam::InitGui(window, gui) == Bam::Status::Fail)
//		{
//			Bam::ExitGui(gui);
//			Bam::ExitWindow(window);
//			BM_EXIT();
//		}
//
//		Bam::SetViewport(viewport);
//
//
//		Bam::f32ut tmpv[20] = {
//			 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, // top right
//			 0.5f, -0.5f, 0.0f,   1.0f, 0.0f, // bottom right
//			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, // bottom left
//			-0.5f,  0.5f, 0.0f,   0.0f, 1.0f  // top left 
//		};
//
//		ui32t tmpi[6] = {
//			0, 1, 3,
//			1, 2, 3
//		};
//
//		Bam::Shader shader;
//		Bam::ShaderSource shaderSource;
//		Bam::InitShaderSource(shaderSource, 2);
//		shaderSource.files[0] = "../Bamboo/res/shaders/B_0.vertex.glsl.shader";
//		shaderSource.files[1] = "../Bamboo/res/shaders/B_0.fragment.glsl.shader";
//		shaderSource.types[0] = Bam::ShaderType::Vertex;
//		shaderSource.types[1] = Bam::ShaderType::Fragment;
//		Bam::CompileShaderSource(shaderSource);
//		Bam::InitShader(shader, shaderSource);
//		Bam::BindShader(shader);
//
//		std::vector<std::future<Bam::Model*>> modelFutures;
//		std::vector<Bam::Model*> models;
//
//		modelFutures.push_back(ASYNC((Bam::Model * (*)(const char*))Bam::LoadAssimpModel, "../Bamboo/res/object/buster_drone/scene.gltf"));
//
//		Bam::VertexArray       va = Bam::InitVertexArray();
//		Bam::VertexBuffer      vb = Bam::InitVertexBuffer(4 * 5 * sizeof(Bam::f32ut), tmpv, Bam::BufferState::DynamicDraw);
//		Bam::IndexBuffer       ib = Bam::InitIndexBuffer(6 * sizeof(ui32t), tmpi, Bam::BufferState::StaticDraw);
//		Bam::VertexArrayFormat vf = Bam::InitVertexArrayFormat(5 * sizeof(Bam::f32ut));
//		Bam::FormatVertexArray(va, vf, 3);
//		Bam::FormatVertexArray(va, vf, 2);
//
//
//		Bam::SetVertexBufferData(vb, 0, sizeof(tmpv), tmpv);
//
//
//		Bam::FrameBuffer frameBuffer;
//		Bam::InitFrameBuffer(frameBuffer, viewport);
//
//
//		char inputBuffer[256] = { 0 };
//
//
//		ui32t change = 0;
//		while (Bam::ShouldWindowClose(window) == Bam::Status::False)
//		{
//			Bam::CheckWindowEvents(window);
//			Bam::SetViewport(viewport);
//
//			// FRAME_BUFFER
//
//			Bam::BindShader(shader);
//			Bam::BindFrameBuffer(frameBuffer);
//			glClearColor(0.235f, 0.286f, 0.247f, 1.0f);
//			glClear(GL_COLOR_BUFFER_BIT);
//
//			Bam::BindVertexArray(va);
//			BM_CATCH(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));
//
//			Bam::BindShader(0);
//			Bam::BindFrameBuffer(0);
//
//			// END FRAME_BUFFER
//
//			glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
//			glClear(GL_COLOR_BUFFER_BIT);
//			Bam::BindShader(0);
//
//			Bam::StartGuiFrame();
//			ImGui::DockSpaceOverViewport();
//
//			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0, 0 });
//			ImGui::Begin("Viewport", 0, ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoScrollbar);
//			ImVec2 win_size = ImGui::GetContentRegionAvail();
//			ImGui::Image((void*)frameBuffer.colorBuffer, win_size, { 0, 0 }, { 1, -1 });
//			if (viewport.width != (ui32t)win_size.x || viewport.height != (ui32t)win_size.y)
//			{
//				viewport.width = (ui32t)win_size.x;
//				viewport.height = (ui32t)win_size.y;
//				Bam::SetFrameBuffer(frameBuffer, viewport);
//
//			}
//			ImGui::End();
//			ImGui::PopStyleVar();
//
//			ImGui::Begin("Left");
//			if (ImGui::Button("Restart Shaders"))
//			{
//				BM_PROFILE_PREC("S:RestartShaders", Bam::Precision::Milli);
//				Bam::CompileShaderSource(shaderSource);
//				Bam::InitShader(shader, shaderSource);
//			}
//			if (ImGui::Button("Import Ready Models"))
//			{
//				ui32t count = 0;
//				ui32t failed = 0;
//				ui32t total = modelFutures.size();
//				modelFutures.erase(
//					std::remove_if(
//						modelFutures.begin(),
//						modelFutures.end(),
//						[&](std::future<Bam::Model*>& future) -> bool {
//							if (future.valid() == true && future.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
//							{
//								Bam::Model* model = future.get();
//								if (model != nullptr)
//								{
//									count++;
//									models.push_back(model);
//								}
//								else
//								{
//									failed++;
//								}
//								return true;
//							}
//							else
//							{
//								return false;
//							}
//						}
//					),
//					modelFutures.end());
//				BM_INFO("Importing Ready Models : {} of {} ({} failed) with {} remaining", count, total, failed, modelFutures.size());
//			}
//
//			if (ImGui::Button("Log Models"))
//			{
//				for (Bam::Model* model : models)
//				{
//					BM_INFO("Log Model {}", (void*)model);
//				}
//			}
//
//			if (ImGui::Button("Clear##modelfilepathinputbuttonclear"))
//			{
//				memset((void*)inputBuffer, 0, 256);
//				inputBuffer[0] = '/';
//				inputBuffer[255] = 0x0;
//			}
//			ImGui::SameLine();
//			if (ImGui::Button("Load##modelfilepathinputbuttonload"))
//			{
//				modelFutures.push_back(ASYNC((Bam::Model * (*)(const char*))Bam::LoadAssimpModel, (const char*)inputBuffer));
//			}
//			ImGui::SameLine();
//			ImGui::PushItemWidth(-1);
//			ImGui::InputText("##modelfilepathinputbox", inputBuffer, 255);
//			ImGui::PopItemWidth();
//
//			ImGui::End();
//
//			ImGui::Begin("Bottom");
//			ImGui::End();
//
//			ImGui::Begin("Right");
//			ImGui::End();
//
//			ImGui::Begin("Spare");
//			ImGui::End();
//
//			ImGui::ShowDemoWindow();
//
//
//			Bam::RenderGui(gui);
//			Bam::RenderWindow(window);
//		}
//
//		Bam::DeleteIndexBuffer(ib);
//		Bam::DeleteVertexBuffer(vb);
//		Bam::DeleteVertexArray(va);
//		Bam::DeleteFrameBuffer(frameBuffer);
//		Bam::DeleteShaderSource(shaderSource);
//		Bam::DeleteShader(shader);
//
//		Bam::ExitGui(gui);
//		Bam::ExitWindow(window);
//	}
//}