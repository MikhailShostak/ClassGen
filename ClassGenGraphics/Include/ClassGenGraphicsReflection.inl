#pragma once

#include <.ClassGen.hpp>

namespace ClassGenGraphics { struct { struct Dummy { Dummy() {
    Reflection::Add<ClassGen::AnimationInfo>("ClassGen.AnimationInfo");
    Reflection::Add<ClassGen::AnimationCompiler>("ClassGen.AnimationCompiler");
    Reflection::Add<ClassGen::AnimationFileEditor>("ClassGen.AnimationFileEditor");
    Reflection::Add<ClassGen::TextureSamplerInfo>("ClassGen.TextureSamplerInfo");
    Reflection::Add<ClassGen::MaterialProperty>("ClassGen.MaterialProperty");
    Reflection::Add<ClassGen::MaterialInfo>("ClassGen.MaterialInfo");
    Reflection::Add<ClassGen::MaterialCompiler>("ClassGen.MaterialCompiler");
    Reflection::Add<ClassGen::MaterialFileEditor>("ClassGen.MaterialFileEditor");
    Reflection::Add<ClassGen::MeshInfo>("ClassGen.MeshInfo");
    Reflection::Add<ClassGen::MeshCompiler>("ClassGen.MeshCompiler");
    Reflection::Add<ClassGen::MeshFileEditor>("ClassGen.MeshFileEditor");
    Reflection::Add<ClassGen::ParticleSystemInfo>("ClassGen.ParticleSystemInfo");
    Reflection::Add<ClassGen::ParticleSystemCompiler>("ClassGen.ParticleSystemCompiler");
    Reflection::Add<ClassGen::ParticleSystemFileEditor>("ClassGen.ParticleSystemFileEditor");
    Reflection::Add<ClassGen::EntityInfo>("ClassGen.EntityInfo");
    Reflection::Add<ClassGen::SceneInfo>("ClassGen.SceneInfo");
    Reflection::Add<ClassGen::SceneCompiler>("ClassGen.SceneCompiler");
    Reflection::Add<ClassGen::SceneFileEditor>("ClassGen.SceneFileEditor");
    Reflection::Add<ClassGen::TextureInfo>("ClassGen.TextureInfo");
    Reflection::Add<ClassGen::TextureCompiler>("ClassGen.TextureCompiler");
    Reflection::Add<ClassGen::TextureFileEditor>("ClassGen.TextureFileEditor");
    Reflection::Add<ClassGen::GraphicsExtension>("ClassGen.GraphicsExtension");
} } Dummy; } Dummy; }
