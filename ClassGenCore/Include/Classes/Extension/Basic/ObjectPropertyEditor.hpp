#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT ObjectPropertyEditor
    : public ClassGen::ValuePropertyEditor<SortedMap<String, Serialization::Data>>
{
    using This = ObjectPropertyEditor;
    using Super = ClassGen::ValuePropertyEditor<SortedMap<String, Serialization::Data>>;
    Map<String, UniqueReference<ClassGen::PropertyEditor>> PropertyEditors {};
    ObjectPropertyEditor() = default;
    ObjectPropertyEditor(const ObjectPropertyEditor &other) = delete;
    ObjectPropertyEditor &operator =(const ObjectPropertyEditor &other) = delete;

    virtual ~ObjectPropertyEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void DrawLabel(const String & Name);
    virtual void Draw();
    virtual void DrawProperties(ClassGen::ClassInfo & ClassInfo);
    virtual void DrawAllProperties();
    virtual void Clear();

    void Initialize()
    {
        Super::Initialize();
    }
};
}
