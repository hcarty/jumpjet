#include <filesystem>
#include <string>

#include "orx.h"

#include "LDtkLoader/Project.hpp"

namespace orx
{
  struct Spec
  {
    const ldtk::Project &project;
    const std::string level;
    const std::string collisionLayer;
    const std::string entityLayer;

    Spec(const ldtk::Project &project,
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

  void ldtkToConfig(const orxSTRING mapLocation, const EntityCallbacks &entityCallbacks = {});
};
