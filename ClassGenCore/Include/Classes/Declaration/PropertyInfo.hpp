#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT PropertyInfo
{
    using This = PropertyInfo;
    ClassGen::TypeInfo Type {};
    String Name {};
    String Initialization {};
    Array<String> Attributes {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Name"] & Name;
        data["Initialization"] & Initialization;
        data["Attributes"] & Attributes;
    }

    void Initialize()
    {
    }
};
}
