#pragma once

namespace Graphics
{
    class Texture;
}

//#include <Graphics.pch.hpp>

//TODO: sort
#include "Classes/Declaration/BaseInfo.hpp"
#include "Classes/Declaration/FileInfo.hpp"
#include "Classes/Declaration/TypeInfo.hpp"
#include "Classes/Declaration/TypeInfoSerializer.hpp"
#include "Classes/Declaration/ParameterInfo.hpp"
#include "Classes/Declaration/EventInfo.hpp"
#include "Classes/Declaration/FunctionInfo.hpp"
#include "Classes/Declaration/PropertyInfo.hpp"
#include "Classes/Graph/ConnectionInfo.hpp"
#include "Classes/Graph/NodeInfo.hpp"
#include "Classes/Graph/GraphInfo.hpp"
#include "Classes/Declaration/ClassInfo.hpp"
#include "Classes/Declaration/AssetInfo.hpp"
#include "Classes/Compilers/Compiler.hpp"
#include "Classes/Compilers/ClassCompiler.hpp"
#include "Classes/Compilers/AssetCompiler.hpp"
#include "Classes/Editor/PropertyEditor.hpp"
#include "Classes/Editor/FileEditor.hpp"
#include "Classes/Extension/ExtensionLibrary.hpp"
#include "Classes/Extension/ExtensionInterface.hpp"
#include "Classes/Extension/Basic/InstanceInfo.hpp"
#include "Classes/Extension/Basic/ValuePropertyEditor.hpp"
#include "Classes/Extension/Basic/ValuePropertyEditor.inl"
#include "Classes/Extension/Basic/BooleanPropertyEditor.hpp"
#include "Classes/Extension/Basic/IntPropertyEditor.hpp"
#include "Classes/Extension/Basic/Int2PropertyEditor.hpp"
#include "Classes/Extension/Basic/Int3PropertyEditor.hpp"
#include "Classes/Extension/Basic/Int4PropertyEditor.hpp"
#include "Classes/Extension/Basic/FloatPropertyEditor.hpp"
#include "Classes/Extension/Basic/Float2PropertyEditor.hpp"
#include "Classes/Extension/Basic/Float3PropertyEditor.hpp"
#include "Classes/Extension/Basic/Float4PropertyEditor.hpp"
#include "Classes/Extension/Basic/ColorPropertyEditor.hpp"
#include "Classes/Extension/Basic/StringPropertyEditor.hpp"
#include "Classes/Extension/Basic/PathPropertyEditor.hpp"
#include "Classes/Extension/Basic/ArrayPropertyEditor.hpp"
#include "Classes/Extension/Basic/ObjectPropertyEditor.hpp"
#include "Classes/Extension/Basic/InstancePropertyEditor.hpp"
#include "Classes/Extension/Basic/BasicExtension.hpp"
#include "Classes/Extension/Class/ClassFileEditor.hpp"
#include "Classes/Extension/Class/AssetFileEditor.hpp"
#include "Classes/Extension/Class/ClassExtension.hpp"
#include "ClassGenGlobals.hpp"
