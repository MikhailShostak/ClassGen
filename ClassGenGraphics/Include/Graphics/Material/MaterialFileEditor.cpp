//#include <ClassGenLibrary.private.hpp>

#include <imgui_node_editor.h>

namespace ClassGen
{

extern SharedReference<Graphics::Mesh> PostEffectMesh;
extern SharedReference<Graphics::Material> PostEffectMaterial;
extern Graphics::RenderTarget PostEffectBuffer;

namespace 
{

static ax::NodeEditor::EditorContext* g_Context = nullptr;

String g_GraphName;
String g_GraphID;
ClassGen::GraphInfo* g_CurrentGraph = nullptr;

inline Map<String, ClassGen::FunctionInfo> g_MaterialFunctionCache;

}

void MaterialFileEditor::DrawMaterialGraph(const System::Path &path, ClassGen::MaterialInfo &info)
{
    if (g_MaterialFunctionCache.empty())
    {
        auto MaterialFunctions = MaterialFunctionsStorage.Load();
        for (auto &f : *MaterialFunctions)
        {
            g_MaterialFunctionCache[f.Name] = std::move(f);
        }
    }

    if (!g_Context)
    {
        g_Context = ax::NodeEditor::CreateEditor();
        //TODO: ax::NodeEditor::DestroyEditor(g_Context);
    }

    if (!g_CurrentGraph)
    {
        g_CurrentGraph = &info.Graph;
        return;
    }

    String tooltip;
    if (ImGui::Begin(("Graph: " + g_GraphName + "###ClassGen").data()))
    {
        ax::NodeEditor::SetCurrentEditor(g_Context);
        ax::NodeEditor::Begin("GraphEditor");

        ax::NodeEditor::NodeId contextNodeId = 0;
        ax::NodeEditor::PinId contextPinId = 0;
        ax::NodeEditor::LinkId contextLinkId = 0;

        for (const auto& node : g_CurrentGraph->Nodes)
        {
            ax::NodeEditor::BeginNode((ax::NodeEditor::NodeId)&node);
            ImGui::Text(node.Name.data());

            if (node.Name == "Input")
            {
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)0, ax::NodeEditor::PinKind::Output);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();

                auto it = g_MaterialFunctionCache.find(g_GraphID);
                if (it != g_MaterialFunctionCache.end())
                {
                    const ClassGen::FunctionInfo& f = it->second;
                    for (auto& p : f.InputParameters)
                    {
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Output);
                        ImGui::Text(p.Name.data());
                        ImGui::SameLine();
                        ImGui::Text("[ ]");
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                    }
                }
                ax::NodeEditor::EndNode();
                continue;
            }
            else if (node.Name == "Output")
            {
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)1, ax::NodeEditor::PinKind::Input);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();
                auto it = g_MaterialFunctionCache.find(g_GraphID);
                if (it != g_MaterialFunctionCache.end())
                {
                    const ClassGen::FunctionInfo& f = it->second;
                    for (auto& p : f.OutputParameters)
                    {
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Input);
                        ImGui::Text("[ ]");
                        ImGui::SameLine();
                        ImGui::Text(p.Name.data());
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                    }
                }
                ax::NodeEditor::EndNode();
                continue;
            }

            Array<String> id;
            boost::split(id, node.ID, boost::is_any_of("-"));
            auto it = g_MaterialFunctionCache.find(id[0]);
            if (it != g_MaterialFunctionCache.end())
            {
                const ClassGen::FunctionInfo& f = it->second;
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)0, ax::NodeEditor::PinKind::Input);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();
                ImGui::SameLine();
                ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)1, ax::NodeEditor::PinKind::Output);
                ImGui::Text("[ ]");
                ax::NodeEditor::EndPin();
                size_t s = std::max(f.InputParameters.size(), f.OutputParameters.size());
                for (size_t i = 0; i < s; ++i)
                {
                    bool sameLine = false;
                    if (i < f.InputParameters.size())
                    {
                        auto& p = f.InputParameters[i];
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Input);
                        ImGui::Text("[ ]");
                        ImGui::SameLine();
                        ImGui::Text(p.Name.data());
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                        sameLine = true;
                    }

                    if (i < f.OutputParameters.size())
                    {
                        auto& p = f.OutputParameters[i];
                        if (sameLine)
                        {
                            ImGui::SameLine();
                        }
                        ax::NodeEditor::BeginPin((ax::NodeEditor::PinId)&p, ax::NodeEditor::PinKind::Input);
                        ImGui::Text(p.Name.data());
                        ImGui::SameLine();
                        ImGui::Text("[ ]");
                        ax::NodeEditor::EndPin();
                        if (ImGui::IsItemHovered())
                        {
                            tooltip = writeRecursively(p.Type);
                        }
                    }
                }
            }

            ax::NodeEditor::EndNode();
        }
        ax::NodeEditor::Suspend();
        if (ax::NodeEditor::ShowNodeContextMenu(&contextNodeId))
        {
            ImGui::OpenPopup("Node Context Menu");
        }
        else if (ax::NodeEditor::ShowPinContextMenu(&contextPinId))
        {
            ImGui::OpenPopup("Pin Context Menu");
        }
        else if (ax::NodeEditor::ShowLinkContextMenu(&contextLinkId))
        {
            ImGui::OpenPopup("Link Context Menu");
        }
        if (ax::NodeEditor::ShowNodeContextMenu(&contextNodeId))
        {
            ImGui::OpenPopup("Node Context Menu");
        }
        else if (ax::NodeEditor::ShowBackgroundContextMenu())
        {
            ImGui::OpenPopup("Create New Node");
        }

        if (ImGui::BeginPopup("Node Context Menu"))
        {
            if (ImGui::MenuItem("Remove"))
            {
                ax::NodeEditor::DeleteNode(contextNodeId);
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("Create New Node"))
        {
            String name;
            if (ImGui::InputText("Find##GraphSearch", &name, ImGuiInputTextFlags_EnterReturnsTrue))
            {
                ClassGen::NodeInfo n;
                n.ID = fmt::format("{}-{:x}", name, std::chrono::duration_cast<DateTime::Milliseconds>(DateTime::System::Clock::now().time_since_epoch()).count());
                n.Name = name;
                g_CurrentGraph->Nodes.push_back(n);
                MarkFileDirty(path);
            }
            ImGui::EndPopup();
        }
        ax::NodeEditor::Resume();
        ax::NodeEditor::End();
    }
    ImGui::End();
    if (ImGui::Begin("Tooltip##ClassGen"))
    {
        ImGui::TextWrapped(tooltip.data());
    }
    ImGui::End();
}

void MaterialFileEditor::RenderFile()
{
    PreviewViewport.Load(*g_GraphicsContext);

    auto& info = *DynamicCast<ClassGen::MaterialInfo>(Data.Instance);

    if (ImGui::Begin("Properties"))
    {
        //ImGui::Columns(2);

        /*auto width = ImGui::GetColumnWidth();
        PreviewViewport.Camera.Resolution.x = width - 5;
        if ((int32_t)PreviewViewport.Camera.Resolution.x != (int32_t)PreviewViewport.GBuffer.Targets[0]->Size.x)
        {
            PreviewViewport.GBuffer.Resize(PreviewViewport.Camera.Resolution);
            g_GraphicsContext->CreateRenderTarget(PreviewViewport.GBuffer);

            PostEffectBuffer.Resize(PreviewViewport.Camera.Resolution);
            g_GraphicsContext->CreateRenderTarget(PostEffectBuffer);
            g_GraphicsContext->InvalidateMaterial(*PostEffectMaterial);
            PostEffectMaterial->RenderBuffer = PostEffectBuffer.GetBuffer();
        }*/

        //ImGui::NextColumn();

        if (ImGui::InputText("Namespace", &info.Namespace))
        {
            MarkFileDirty(Data.Path);
        }

        if (ImGui::CollapsingHeader("Properties##Header", nullptr))
        {
            int32_t i = info.Properties.size();
            if (ImGui::SliderInt("Properties", &i, 0, 64))
            {
                info.Properties.resize(i);
            }
            ImGui::Indent();
            for (size_t i = 0; i < info.Properties.size(); ++i)
            {
                auto& Property = info.Properties[i];
                if (ImGui::InputText(fmt::format("[{}] Name##{}", i, fmt::ptr(&Property)).data(), &Property.Name))
                {
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::DragFloat4(fmt::format("[{}] Value##{}", i, fmt::ptr(&Property)).data(), Property.Value.f32, 0.01f))
                {
                    info.Update();
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::InputText(fmt::format("[{}] Attribute##{}", i, fmt::ptr(&Property)).data(), &Property.Attribute))
                {
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::Checkbox(fmt::format("[{}] Use in Vertex Shader##{}", i, fmt::ptr(&Property)).data(), &Property.UseInVertexShader))
                {
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::Checkbox(fmt::format("[{}] Use in Pixel Shader##{}", i, fmt::ptr(&Property)).data(), &Property.UseInPixelShader))
                {
                    MarkFileDirty(Data.Path);
                }
            }
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Samplers##Header", nullptr))
        {
            int32_t i = info.Textures.size();
            if (ImGui::SliderInt("Samplers", &i, 0, 8))
            {
                info.Textures.resize(i);
            }
            ImGui::Indent();
            for (size_t i = 0; i < info.Textures.size(); ++i)
            {
                auto& texture = info.Textures[i];
                if (ImGui::InputText(fmt::format("[{}] Sampler Name##{}", i, fmt::ptr(&texture)).data(), &texture.SamplerName))
                {
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::InputText(fmt::format("[{}] Texture Name##{}", i, fmt::ptr(&texture)).data(), &texture.TextureName))
                {
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::Checkbox(fmt::format("[{}] Use in Vertex Shader##{}", i, fmt::ptr(&texture)).data(), &texture.UseInVertexShader))
                {
                    MarkFileDirty(Data.Path);
                }
                if (ImGui::Checkbox(fmt::format("[{}] Use in Pixel Shader##{}", i, fmt::ptr(&texture)).data(), &texture.UseInPixelShader))
                {
                    MarkFileDirty(Data.Path);
                }
            }
            ImGui::Unindent();
        }

        if (ImGui::CollapsingHeader("Import", nullptr))
        {
            String s = info.Path.generic_string();
            if (ImGui::InputText("Path", &s))
            {
                info.Path = s;
                MarkFileDirty(Data.Path);
            }
            if (ImGui::InputText("Name", &info.Name))
            {
                MarkFileDirty(Data.Path);
            }

            String vsp = info.VertexShader.generic_string();
            if (ImGui::InputText("Vertex Shader", &vsp))
            {
                info.VertexShader = vsp;
                MarkFileDirty(Data.Path);
            }

            String psp = info.PixelShader.generic_string();
            if (ImGui::InputText("Pixel Shader", &psp))
            {
                info.PixelShader = psp;
                MarkFileDirty(Data.Path);
            }
        }
    }
    ImGui::End();

    PreviewViewport.Draw(*g_GraphicsContext, [&]() {
        ImGui::SameLine();
        if (ImGui::Button(ICON_BUILD.data()))
        {
            if (info.MaterialInstance)
            {
                g_GraphicsContext->InvalidateMaterial(*info.MaterialInstance);
                info.MaterialInstance = nullptr;
            }
            this->PreviewViewport.SetMaterial(info.Load(*g_GraphicsContext));
        }
    });

    DrawMaterialGraph(Data.Path, info);
}

}
