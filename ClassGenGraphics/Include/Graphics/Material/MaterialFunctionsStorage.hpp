#pragma once

namespace ClassGen
{

inline DynamicAsset<Array<ClassGen::FunctionInfo>> MaterialFunctionsStorage = { "MaterialFunctionsStorage", [](auto &instance)
{
Serialization::FromString(R"(
- InputParameters:
    - Name: BaseColor
      Type:
        Name: Color
  Name: PixelOutput
- InputParameters:
    - Name: Position
      Type:
        Name: Float3
  Name: VertexOutput
- InputParameters:
    - Name: A
      Type:
        Name: Float
    - Name: B
      Type:
        Name: Float
  Name: Add
  OutputParameters:
    - Name: C
      Type:
        Name: Float
- InputParameters:
    - Name: A
      Type:
        Name: Float
    - Name: B
      Type:
        Name: Float
  Name: Subtract
  OutputParameters:
    - Name: C
      Type:
        Name: Float
- InputParameters:
    - Name: A
      Type:
        Name: Float
    - Name: B
      Type:
        Name: Float
  Name: Multiply
  OutputParameters:
    - Name: C
      Type:
        Name: Float
- InputParameters:
    - Name: A
      Type:
        Name: Float
    - Name: B
      Type:
        Name: Float
  Name: Divide
  OutputParameters:
    - Name: C
      Type:
        Name: Float
- InputParameters:
    - Name: A
      Type:
        Name: Float
    - Name: B
      Type:
        Name: Float
  Name: Floor
  OutputParameters:
    - Name: C
      Type:
        Name: Float
- InputParameters:
    - Name: A
      Type:
        Name: Float
    - Name: B
      Type:
        Name: Float
  Name: Ceil
  OutputParameters:
    - Name: C
      Type:
        Name: Float
- InputParameters:
    - Name: UV
      Type:
        Name: Float2
  Name: Texture2D
  OutputParameters:
    - Name: Out
      Type:
        Name: Float4
- InputParameters:
    - Name: UV
      Type:
        Name: Float3
  Name: Texture3D
  OutputParameters:
    - Name: Out
      Type:
        Name: Float4
)",
instance);
} };
}
