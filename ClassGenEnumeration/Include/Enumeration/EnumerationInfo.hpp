#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT EnumerationInfo
    : public ClassGen::BaseInfo
{
    using This = EnumerationInfo;
    using Super = ClassGen::BaseInfo;
    Array<String> Values {};

    virtual ~EnumerationInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Values"] & Values;
    }

    void Initialize()
    {
        Super::Initialize();
    }
};
}
