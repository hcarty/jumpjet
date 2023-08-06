#pragma once

#include <string>

#include "orx.h"
#include "Scroll/Scroll.h"

namespace command
{
  void Evaluate(const orxSTRING command);
  void EvaluateWithGuid(const orxSTRING command, const orxU64 guid);
}

namespace input
{
  orxBOOL HasSet(const ScrollObject *obj);

  const orxSTRING GetSetName(const ScrollObject *obj);

  void EnableSet(const ScrollObject *obj, bool enable = true);

  const orxSTRING SelectSet(const ScrollObject *obj);

  orxVECTOR GetVector(const orxSTRING left = "Left", const orxSTRING right = "Right", const orxSTRING up = "Up", const orxSTRING down = "Down");
}

namespace runtime
{
  void PushRuntime();
  void PopRuntime();

  void SetGUID(ScrollObject *o, const orxSTRING key);
  orxU64 GetGUID(const orxSTRING name);
}
