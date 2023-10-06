#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT ParameterInfo
{
    using This = ParameterInfo;
    ClassGen::TypeInfo Type {};
    String Name {};
    bool Writable {};
    bool Copy {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
        data["Writable"] & Writable;
        data["Copy"] & Copy;
    }

    void Initialize()
    {
    }
};
}
