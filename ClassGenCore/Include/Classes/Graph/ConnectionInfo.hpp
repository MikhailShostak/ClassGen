#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT ConnectionInfo
{
    using This = ConnectionInfo;
    System::Path Source {};
    System::Path Destination {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Source"] & Source;
        data["Destination"] & Destination;
    }

    void Initialize()
    {
    }
};
}
