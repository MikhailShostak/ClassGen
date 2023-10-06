#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT EnumerationExtension
    : public ClassGen::ExtensionInterface
{
    using This = EnumerationExtension;
    using Super = ClassGen::ExtensionInterface;

    virtual ~EnumerationExtension() {}
    template<typename T>
    void Serialize(T &&data)
    {
    }
    virtual void Load(ClassGen::ExtensionLibrary & Library);

    void Initialize()
    {
        Super::Initialize();
    }
};
}
