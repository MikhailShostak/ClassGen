#pragma once

namespace ClassGen
{
struct MaterialFileEditor
    : public ClassGen::FileEditor
{
    using This = MaterialFileEditor;
    using Super = ClassGen::FileEditor;
    SharedReference<Graphics::Material> Material = {};
    System::Path LastPath = {};
    ClassGen::PreviewViewport PreviewViewport = {};

    virtual ~MaterialFileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderFile();
    virtual void DrawMaterialGraph(const System::Path & path, ClassGen::MaterialInfo & info);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
