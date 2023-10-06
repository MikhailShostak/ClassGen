#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT FloatPropertyEditor
    : public ClassGen::ValuePropertyEditor<float>
{
    using This = FloatPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<float>;

    virtual ~FloatPropertyEditor() {}
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
