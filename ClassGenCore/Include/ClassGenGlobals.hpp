#pragma once

#include "Classes/Extension/ExtensionLibrary.hpp"

inline ClassGen::ExtensionLibrary g_ExtensionLibrary;

inline Map<String, ClassGen::FunctionInfo> g_FunctionCache;
inline SortedMap<String, ClassGen::FileInfo> g_ClassGenCache;

inline Map<String, UniqueReference<ClassGen::FileEditor>> g_Editors;

inline Array<UniqueReference<ClassGen::ExtensionInterface>> g_Extensions;

namespace ClassGen
{

inline String ICON_ADD = "\xee\x85\x85";
inline String ICON_DELETE = "\xee\xa1\xb2";
inline String ICON_OPEN_IN_NEW = "\xee\xa2\x9e";

PUBLIC_API_EXPORT void LoadExtensions();
PUBLIC_API_EXPORT void Compile(const ClassGen::FileInfo& FileInfo);
PUBLIC_API_EXPORT void Compile(const System::Path &Path);
PUBLIC_API_EXPORT ClassGen::FileInfo FindClassByName(const String& name, const String& nameSpace);
PUBLIC_API_EXPORT ClassGen::FileInfo FindClassByName(const String& fullname);
PUBLIC_API_EXPORT ClassGen::FileInfo FindClassByName(const ClassGen::TypeInfo& type);

}
