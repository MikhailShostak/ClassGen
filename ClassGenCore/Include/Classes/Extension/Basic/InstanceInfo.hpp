#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT InstanceInfo
{
    using This = InstanceInfo;
    String Type {};
    SortedMap<String, Serialization::Data> Values {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Type"] & Type;
        data["Values"] & Values;
    }

    void Initialize()
    {
    }
};
}
