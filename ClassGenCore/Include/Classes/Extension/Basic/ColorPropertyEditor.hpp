#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT ColorPropertyEditor
    : public ClassGen::ValuePropertyEditor<Float4>
{
    using This = ColorPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<Float4>;

    virtual ~ColorPropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Draw();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
