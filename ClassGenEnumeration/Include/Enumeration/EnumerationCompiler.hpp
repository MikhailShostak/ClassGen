#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT EnumerationCompiler
    : public ClassGen::Compiler
{
    using This = EnumerationCompiler;
    using Super = ClassGen::Compiler;

    virtual ~EnumerationCompiler() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Compile(const SharedReference<ClassGen::BaseInfo> & BaseInfo, const System::Path & OutputFilePath);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
