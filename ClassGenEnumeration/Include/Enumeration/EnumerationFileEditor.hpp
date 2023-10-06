#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT EnumerationFileEditor
    : public ClassGen::FileEditor
{
    using This = EnumerationFileEditor;
    using Super = ClassGen::FileEditor;

    virtual ~EnumerationFileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void RenderFile();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
