#include "game.h"

namespace command
{
  void Evaluate(const orxSTRING command)
  {
    orxCOMMAND_VAR _result;
    orxCommand_Evaluate(command, &_result);
  }

  void EvaluateWithGuid(const orxSTRING command, const orxU64 guid)
  {
    orxCOMMAND_VAR _result;
    orxCommand_EvaluateWithGUID(command, guid, &_result);
  }
}

namespace input
{
  const orxSTRING INPUT_SET_KEY = "Input";

  orxBOOL HasSet(const ScrollObject *obj)
  {
    obj->PushConfigSection();
    auto exists = orxConfig_HasValue(INPUT_SET_KEY);
    obj->PopConfigSection();
    return exists;
  }

  const orxSTRING GetSetName(const ScrollObject *obj)
  {
    obj->PushConfigSection();
    auto name = orxConfig_GetString(INPUT_SET_KEY);
    obj->PopConfigSection();
    return name;
  }

  void EnableSet(const ScrollObject *obj, bool enable)
  {
    orxInput_EnableSet(GetSetName(obj), enable);
  }

  const orxSTRING SelectSet(const ScrollObject *obj)
  {
    auto inputSet = orxInput_GetCurrentSet();
    orxInput_SelectSet(GetSetName(obj));
    return inputSet;
  }

  orxVECTOR GetVector(const orxSTRING left, const orxSTRING right, const orxSTRING up, const orxSTRING down)
  {
    orxVECTOR input = {
        orxInput_GetValue(right) - orxInput_GetValue(left),
        orxInput_GetValue(down) - orxInput_GetValue(up),
        0.0};
    if (orxVector_GetSquareSize(&input) > 1.0)
    {
      orxVector_Normalize(&input, &input);
    }
    return input;
  }
}

namespace runtime
{
  void PushRuntime()
  {
    orxConfig_PushSection("Runtime");
  }

  void PopRuntime()
  {
    orxConfig_PopSection();
  }

  void SetGUID(ScrollObject *o, const orxSTRING key)
  {
    PushRuntime();
    orxConfig_SetU64(key, o->GetGUID());
    PopRuntime();
  }

  orxU64 GetGUID(const orxSTRING name)
  {
    PushRuntime();
    auto guid = orxConfig_GetU64(name);
    PopRuntime();
    return guid;
  }
}
