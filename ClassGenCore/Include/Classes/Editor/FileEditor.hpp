#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT FileEditor
{
    using This = FileEditor;
    ClassGen::FileInfo Data {};
    System::Path Path {};
    Map<String, UniqueReference<ClassGen::PropertyEditor>> PropertyEditors {};
    FileEditor() = default;
    FileEditor(const FileEditor &other) = delete;
    FileEditor &operator =(const FileEditor &other) = delete;

    virtual ~FileEditor() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    Meta::Function<void, const System::Path & /*FilePath*/> MarkFileDirty;
    virtual void RenderFile();

    void Initialize()
    {
    }
};
}
