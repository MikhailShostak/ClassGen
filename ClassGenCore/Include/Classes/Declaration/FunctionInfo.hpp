#pragma once

namespace ClassGen
{
struct PUBLIC_API_EXPORT FunctionInfo
{
    using This = FunctionInfo;
    String Name {};
    Array<ClassGen::ParameterInfo> InputParameters {};
    Array<ClassGen::ParameterInfo> OutputParameters {};
    Array<String> ExecutionBranches {};
    bool Constant {};

    template<typename T>
    void Serialize(T &&data)
    {
        data["Name"] & Name;
        data["InputParameters"] & InputParameters;
        data["OutputParameters"] & OutputParameters;
        data["ExecutionBranches"] & ExecutionBranches;
        data["Constant"] & Constant;
    }

    void Initialize()
    {
    }
};
}
