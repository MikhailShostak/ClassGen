#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT BaseInfo
{
    using This = BaseInfo;
    String Namespace {};

    virtual ~BaseInfo() {}
    template<typename T>
    void Serialize(T &&data)
    {
        data["Namespace"] & Namespace;
    }

    void Initialize()
    {
    }
};
}
