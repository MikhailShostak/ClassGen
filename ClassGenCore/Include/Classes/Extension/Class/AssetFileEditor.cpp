
namespace ClassGen
{

namespace
{

constexpr int ButtonSize = 26;

float padding = 0;
const float PaddingSize = 16;
void PushPadding() { padding += PaddingSize; }
void PopPadding() { padding -= PaddingSize; }
void ApplyPadding() { ImGui::SetCursorPosX(ImGui::GetCursorPosX() + padding); }


/*namespace
{

template<class Key, class T, class Compare, class Alloc, class Pred>
typename std::map<Key, T, Compare, Alloc>::size_type erase_if(std::map<Key, T, Compare, Alloc> &c, Pred pred)
{
    auto old_size = c.size();
    for (auto i = c.begin(), last = c.end(); i != last; ) {
        if (pred(*i)) {
            i = c.erase(i);
        }
        else {
            ++i;
        }
    }
    return old_size - c.size();
}

template<class Key, class T, class Compare, class Alloc, class Pred>
typename std::unordered_map<Key, T, Compare, Alloc>::size_type erase_if(std::unordered_map<Key, T, Compare, Alloc> &c, Pred pred)
{
    auto old_size = c.size();
    for (auto i = c.begin(), last = c.end(); i != last; ) {
        if (pred(*i)) {
            i = c.erase(i);
        }
        else {
            ++i;
        }
    }
    return old_size - c.size();
}

}

void ClearIndex(const String &namespaceName)
{
    auto prefix = namespaceName + ".";
    erase_if(g_FunctionCache, [&](auto &pair) {
        return boost::starts_with(pair.first, prefix);
    });
}

void IndexFunctions(const Array<ClassGen::FunctionInfo> &functions, const String &namespaceName)
{
    for (const auto &f : functions)
    {
        ClassGen::FunctionInfo function = f;
        function.Name = namespaceName + "." + function.Name;
        g_FunctionCache[function.Name] = std::move(function);
    }
}

void IndexProperties(const Array<ClassGen::PropertyInfo> &properties, const String &namespaceName)
{
    for (const auto &p : properties)
    {
        ClassGen::FunctionInfo getter;
        getter.Name = namespaceName + ".Get" + p.Name;
        getter.InputParameters = { ClassGen::ParameterInfo{ p.Type, p.Name } };
        g_FunctionCache[getter.Name] = std::move(getter);

        ClassGen::FunctionInfo setter;
        setter.Name = namespaceName + ".Set" + p.Name;
        setter.OutputParameters = { ClassGen::ParameterInfo{ p.Type, p.Name } };
        g_FunctionCache[setter.Name] = std::move(setter);
    }
}*/

void IndexFileData(const System::Path &path, const ClassGen::BaseInfo &baseInfo)
{
    return;
    /*auto namespaceName = path.stem().generic_string();
    if (!baseInfo.Namespace.empty())
    {
        namespaceName = baseInfo.Namespace + "." + namespaceName;
    }

    ClearIndex(namespaceName);

    auto classInfo = dynamic_cast<const ClassGen::ClassInfo *>(&baseInfo);
    if (!classInfo)
    {
        return;
    }

    IndexProperties(classInfo->Properties, namespaceName);
    IndexFunctions(classInfo->Functions, namespaceName);*/
}

template<typename Type>
auto SamePointer(const Type& value)
{
    return [&value](auto& item)
    {
        return &item == value;
    };
}

bool DrawTypeEditor(ClassGen::TypeInfo& typeInfo)
{
    ClassGen::FileInfo baseTypeInfo = FindClassByName(typeInfo.Name);
    auto ButtonOffset = !baseTypeInfo.Type.empty() ? -ButtonSize - ImGui::GetStyle().ItemInnerSpacing.x : 0;
    ImGui::PushItemWidth(ButtonOffset - 1);
    String baseType = writeRecursively(typeInfo);
    if (ImGui::InputText(fmt::format("##{}", fmt::ptr(&typeInfo)).data(), &baseType))
    {
        readRecursively(baseType, typeInfo);
        return true;
    }
    if (!baseTypeInfo.Type.empty())
    {
        ImGui::SameLine();
        ImGui::SetCursorPosX(ImGui::GetCursorPosX() + ImGui::GetStyle().ItemInnerSpacing.x - ImGui::GetStyle().ItemSpacing.x);
        if (ImGui::Button(fmt::format("{}##Navigation{}", ICON_OPEN_IN_NEW, fmt::ptr(&typeInfo)).data()))
        {
            g_ExtensionLibrary.Navigate(baseTypeInfo);
        }
    }
    ImGui::PopItemWidth();
    return false;
}
}

void AssetFileEditor::RenderDetails(const System::Path &path, ClassGen::AssetInfo &assetInfo)
{
    if (ImGui::CollapsingHeader("Details", ImGuiTreeNodeFlags_DefaultOpen))
    {
        ImGui::Columns(2);

        ImGui::Text("Namespace");
        ImGui::NextColumn();
        ImGui::PushItemWidth(-1);
        if (ImGui::InputText("##Namespace", &assetInfo.Namespace))
        {
            IndexFileData(path, assetInfo);
            MarkFileDirty(path);
        }
        ImGui::PopItemWidth();
        ImGui::NextColumn();

        ImGui::Text("Base Type");
        ImGui::NextColumn();
        if (DrawTypeEditor(assetInfo.BaseType))
        {
            IndexFileData(path, assetInfo);
            MarkFileDirty(path);
        }
        ImGui::Columns(1);
    }
}


inline static ImGuiTableFlags DefaultTableFlags =
ImGuiTableFlags_SizingFixedFit |
ImGuiTableFlags_RowBg |
ImGuiTableFlags_Borders |
ImGuiTableFlags_Resizable |
ImGuiTableFlags_Hideable;

void AssetFileEditor::RenderData(const System::Path &path, ClassGen::AssetInfo &assetInfo)
{
    //TODO: Check FileData
    ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));

    auto assetFileInfo = FindClassByName(assetInfo.BaseType);
    auto assetClassInfo = DynamicCast<ClassGen::ClassInfo>(assetFileInfo.Instance);

    if (Data.Type == "DataTable")
    {
        if (assetClassInfo->Properties.empty())
        {
            ImGui::PopStyleVar();
            return;
        }
        if (ImGui::BeginTable(fmt::format("##{}", fmt::ptr(&DataEditor)).data(), assetClassInfo->Properties.size() + 1, DefaultTableFlags))
        {
            for (const auto& p : assetClassInfo->Properties)
            {
                ImGui::TableSetupColumn(p.Name.data(), ImGuiTableColumnFlags_WidthFixed);
            }
            ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed);
            auto DataTableRows = Serialization::Deserialize<Array<Serialization::Data>>(assetInfo.Values["DataTable"]);
            ImGui::TableHeadersRow();
            static size_t selectedRow = 0;
            size_t i = 0;
            size_t rowToDelete = -1;
            selectedRow = std::clamp<size_t>(selectedRow, 0, DataTableRows.size() - 1);
            for (auto &Row : DataTableRows)
            {
                ImGui::TableNextRow();
                auto Values = Serialization::Deserialize<Map<String, Serialization::Data>>(Row);
                size_t j = 0;
                for (auto& p : assetClassInfo->Properties)
                {
                    String text;
                    ImGui::TableSetColumnIndex(j);
                    auto it = Values.find(p.Name);
                    if (it != Values.end())
                    {
                        text = Serialization::ToString(it->second);
                        auto lines = Str::Split(text, "\n");
                        if (lines.size() > 1)
                        {
                            text = lines[0] + "...";
                        }
                    }
                    bool isSelected = selectedRow == i;
                    if (ImGui::Selectable(fmt::format("{}##{}_{}", text, i, j).data(), &isSelected))
                    {
                        selectedRow = i;
                        DataEditor.Changed = nullptr;
                    }
                    ++j;
                }
                ImGui::TableSetColumnIndex(j);
                if (ImGui::Button(fmt::format("{}##{}", ICON_DELETE, i).data()))
                {
                    rowToDelete = i;
                }
                ++i;
            }
            ImGui::EndTable();
            if (rowToDelete != -1)
            {
                DataTableRows.erase(DataTableRows.begin() + rowToDelete);
                assetInfo.Values["DataTable"] = Serialization::Serialize(DataTableRows);
                rowToDelete = -1;
            }
            if (ImGui::Button(ICON_ADD.data()))
            {
                DataTableRows.resize(DataTableRows.size() + 1);
                assetInfo.Values["DataTable"] = Serialization::Serialize(DataTableRows);
            }
            //auto &row = DataTableRows[selectedRow];
            //auto map = Serialization::Deserialize<Map<String, Serialization::Data>>(row);
            if (!DataEditor.Changed)
            {
                DataEditor.Value.clear();
                DataEditor.PropertyEditors.clear();
                Serialization::Deserialize(DataTableRows[selectedRow], DataEditor.Value);
                DataEditor.Changed = [&]()
                {
                    auto DataTableRows = Serialization::Deserialize<Array<Serialization::Data>>(assetInfo.Values["DataTable"]);
                    DataTableRows[selectedRow] = Serialization::Serialize(DataEditor.Value);
                    assetInfo.Values["DataTable"] = Serialization::Serialize(DataTableRows);
                    MarkFileDirty(path);
                };
            }
            DataEditor.TypeInfo = assetInfo.BaseType;
            DataEditor.FileInfo = assetFileInfo;
            DataEditor.ID = fmt::format("##PropertyValue{}", fmt::ptr(&DataEditor));

            ImGui::Columns(2);
            DataEditor.DrawAllProperties();
            ImGui::Columns(1);
        }
        ImGui::PopStyleVar();
        return;
    }

    if (!DataEditor.Changed)
    {
        DataEditor.Value = assetInfo.Values;
        DataEditor.Changed = [&]()
        {
            assetInfo.Values = DataEditor.Value;
            MarkFileDirty(path);
        };
    }
    DataEditor.TypeInfo = assetInfo.BaseType;
    DataEditor.FileInfo = assetFileInfo;
    DataEditor.ID = fmt::format("##PropertyValue{}", fmt::ptr(&DataEditor));

    ImGui::Columns(2);
    DataEditor.DrawAllProperties();
    ImGui::Columns(1);
    ImGui::PopStyleVar();
}

void AssetFileEditor::RenderFile()
{
    auto &fileInfo = Data;
    auto &assetInfo = *DynamicCast<ClassGen::AssetInfo>(fileInfo.Instance);

    if (ImGui::BeginTabBar("##ClassTabBarDetails"))
    {
        if (ImGui::BeginTabItem("Details"))
        {
            RenderDetails(Path, assetInfo);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    if (ImGui::BeginTabBar("##ClassTabBarData"))
    {
        if (ImGui::BeginTabItem("Data"))
        {
            RenderData(Path, assetInfo);
            ImGui::EndTabItem();
        }
        if (!assetInfo.Values.empty())
        {
            if (ImGui::BeginTabItem(fmt::format("{}##{}", ICON_DELETE, fmt::ptr(&DataEditor)).data()))
            {
                assetInfo.Values.clear();
                DataEditor.Clear();
                MarkFileDirty(Path);
                ImGui::EndTabItem();
            }
        }
        ImGui::EndTabBar();
    }
}
}
