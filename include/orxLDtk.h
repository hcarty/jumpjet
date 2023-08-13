#pragma once

#include "orx.h"

#include "LDtkLoader/Project.hpp"

namespace orxldtk
{
  struct Source
  {
    const ldtk::Project &project;
    const ldtk::World &world;
    const ldtk::Level &level;
    const std::vector<ldtk::Layer> &layers;
    const ldtk::Layer &collisions;
    const ldtk::Layer &entities;

    Source(const ldtk::Project &project,
           const std::string &levelName, const std::string &collisionLayerName,
           const std::string &entityLayerName);
  };

  namespace entity
  {
    std::string DefaultConfigSection(const ldtk::Entity &entity, const Source &source);
    void CreateDefaultConfig(const ldtk::Entity &entity, const Source &source, const std::string sectionName);

    using Callbacks = std::map<std::string, std::function<void(const ldtk::Entity &, const Source &)>>;
    static Callbacks callbacks;
  }

  void Init(const orxldtk::entity::Callbacks &callbacks);
  void Exit();
}

void orxLDtk_Init(const orxldtk::entity::Callbacks &callbacks);
void orxLDtk_Exit();
