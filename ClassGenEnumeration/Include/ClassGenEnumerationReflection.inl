#include <.ClassGen.hpp>
namespace ClassGenEnumeration { struct { struct Dummy { Dummy() {
    Reflection::Add<ClassGen::EnumerationInfo>("ClassGen.EnumerationInfo");
    Reflection::Add<ClassGen::EnumerationExtension>("ClassGen.EnumerationExtension");
    Reflection::Add<ClassGen::EnumerationFileEditor>("ClassGen.EnumerationFileEditor");
    Reflection::Add<ClassGen::EnumerationPropertyEditor>("ClassGen.EnumerationPropertyEditor");
    Reflection::Add<ClassGen::EnumerationCompiler>("ClassGen.EnumerationCompiler");
} } Dummy; } Dummy; }
