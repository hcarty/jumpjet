/**
 * @file jumpjet.cpp
 * @date 5-Aug-2023
 */

#define __SCROLL_IMPL__
#include "jumpjet.h"
#undef __SCROLL_IMPL__

#include "Object.h"

#define orxNUKLEAR_IMPL
#include "orxNuklear.h"
#undef orxNUKLEAR_IMPL

#define orxIMGUI_IMPL
#include "orxImGui.h"
#undef orxIMGUI_IMPL

#define orxBUNDLE_IMPL
#include "orxBundle.h"
#undef orxBUNDLE_IMPL

#include "orxLDtk.h"

#include "LDtkWorld.h"

#ifdef __orxMSVC__

/* Requesting high performance dedicated GPU on hybrid laptops */
__declspec(dllexport) unsigned long NvOptimusEnablement = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#endif // __orxMSVC__

/** Update function, it has been registered to be called every tick of the core clock
 */
void jumpjet::Update(const orxCLOCK_INFO &_rstInfo)
{
  // Should quit?
  if (orxInput_IsActive("Quit"))
  {
    // Send close event
    orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
  }
}

/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS jumpjet::Init()
{
  // Initialize Nuklear
  orxNuklear_Init();

  // Initialize Dear ImGui
  orxImGui_Init();

  // Is processing a new bundle?
  if (orxBundle_IsProcessing())
  {
    // Done!
    return orxSTATUS_SUCCESS;
  }

  // Initialize LDtk loading
  orxLDtk_Init(ldtkworld::GetCallbacks());

  // Create the scene
  CreateObject("Scene");

  // Done!
  return orxSTATUS_SUCCESS;
}

/** Run function, it should not contain any game logic
 */
orxSTATUS jumpjet::Run()
{
  // Return orxSTATUS_FAILURE to instruct orx to quit
  return orxSTATUS_SUCCESS;
}

/** Exit function, it is called before exiting from orx
 */
void jumpjet::Exit()
{
  // Exit from LDtk
  orxLDtk_Exit();

  // Exit from Nuklear
  orxNuklear_Exit();

  // Exit from Dear ImGui
  orxImGui_Exit();

  // Exit from bundle support
  orxBundle_Exit();

  // Let orx clean all our mess automatically. :)
}

/** BindObjects function, ScrollObject-derived classes are bound to config sections here
 */
void jumpjet::BindObjects()
{
  // Bind the Object class to the Object config section
  ScrollBindObject<Object>("Object");
}

/** Bootstrap function, it is called before config is initialized, allowing for early resource storage definitions
 */
orxSTATUS jumpjet::Bootstrap() const
{
  // Initialize bundle resource type
  orxBundle_Init();

  // Add config storage to find the initial config file
  orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, orxBUNDLE_KZ_RESOURCE_STORAGE, orxFALSE);
  orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, orxBUNDLE_KZ_RESOURCE_STORAGE "jumpjet.obr", orxFALSE);
  orxResource_AddStorage(orxCONFIG_KZ_RESOURCE_GROUP, "../data/config", orxFALSE);

  // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
  return orxSTATUS_SUCCESS;
}

/** Main function
 */
int main(int argc, char **argv)
{
  // Execute our game
  jumpjet::GetInstance().Execute(argc, argv);

  // Done!
  return EXIT_SUCCESS;
}
