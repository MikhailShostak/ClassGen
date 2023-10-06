namespace ClassGen
{

void LoadExtensions()
{
    auto extensions = Reflection::FindAll<ClassGen::ExtensionInterface>();
    for (auto& e : extensions)
    {
        auto i = e->Create();
        i->Load(g_ExtensionLibrary);
        g_Extensions.push_back(std::move(i));
    }
}

void Compile(const ClassGen::FileInfo& FileInfo)
{
    auto it = g_ExtensionLibrary.Compilers.find(FileInfo.Type);
    if (it == g_ExtensionLibrary.Compilers.end())
    {
        fmt::print("Warning: ClassGen compiler is not found for type \"{}\"", FileInfo.Type);
        return;
    }

    auto outputFile = System::Path(FileInfo.Path).replace_extension(".hpp");
    if (System::GetLastWriteTime(FileInfo.Path) > System::GetLastWriteTime(outputFile))
    {
        auto compiler = UniqueReference<ClassGen::Compiler>(it->second->Create());
        compiler->Compile(FileInfo.Instance, outputFile);
    }
}

void Compile(const System::Path &Path)
{
    auto [FileInfo] = g_ExtensionLibrary.LoadFile(Path);
    Compile(FileInfo);
}

ClassGen::FileInfo FindClassByName(const String& name, const String& nameSpace)
{
    ClassGen::FileInfo node;

    auto it = ranges::find_if(g_ClassGenCache, [&](const auto& v)
    {
        bool result = true;
        if (!nameSpace.empty() && v.second.Instance && !v.second.Instance->Namespace.empty())
        {
            result = v.second.Instance->Namespace == nameSpace;
        }

        return result && System::Path(v.first).stem().generic_string() == name;
    });
    if (it != g_ClassGenCache.end())
    {
        node = it->second;
    }

    return node;
}

ClassGen::FileInfo FindClassByName(const String& fullname)
{
    System::Path p(fullname);
    if (p.has_extension())
    {
        auto name = p.extension().generic_string();
        boost::trim_left_if(name, boost::is_any_of("."));
        return FindClassByName(name, p.stem().generic_string());
    }
    else
    {
        return FindClassByName(p.stem().generic_string(), String());
    }
}

ClassGen::FileInfo FindClassByName(const ClassGen::TypeInfo& type)
{
    return FindClassByName(type.Name);
}

}
