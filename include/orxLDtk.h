#include <filesystem>
#include <string>

#include "orx.h"

#include "LDtkLoader/Project.hpp"

namespace orx
{
  struct OrxProject
  {
    const std::filesystem::path texturePath;

    OrxProject(const std::filesystem::path texturePath);
  };

  struct Spec
  {
    const OrxProject orx;
    const std::filesystem::path source;
    const std::string level;
    const std::string collisionLayer;
    const std::string entityLayer;
    ldtk::Project project{};

    Spec(const OrxProject orx, const std::filesystem::path &sourceFile,
         const std::string &levelName, const std::string &collisionLayerName,
         const std::string &entityLayerName);
  };

  struct Source
  {
    const Spec &spec;
    const ldtk::Project &project;
    const ldtk::World &world;
    const ldtk::Level &level;
    const std::vector<ldtk::Layer> &layers;
    const ldtk::Layer &collisions;
    const ldtk::Layer &entities;

    Source(const Spec &spec);
  };

  namespace genericEntity
  {
    std::string DefaultConfigSection(const ldtk::Entity &entity, const Source &source);
    void CreateConfig(const ldtk::Entity &entity, const Source &source, const std::string sectionName);
  };

  using EntityCallbacks = std::map<std::string, std::function<void(const ldtk::Entity &, const Source &)>>;

  void ldtkToConfig(const OrxProject &orx, const std::string &path, const EntityCallbacks &EntityCallbacks = {});
};
