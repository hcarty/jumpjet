#include "Object.h"
#include "game.h"

void Object::OnCreate()
{
  orxConfig_SetBool("IsObject", orxTRUE);
  if (input::HasSet(this))
  {
    input::EnableSet(this);
  }
}

void Object::OnDelete()
{
}

void Object::Update(const orxCLOCK_INFO &_rstInfo)
{
  // Scale gravity by time delta
  orxVECTOR gravity = {0, 981, 0};
  orxVector_Mulf(&gravity, &gravity, _rstInfo.fDT);

  orxVECTOR speed;
  GetSpeed(speed);

  // Jump speed
  orxVECTOR jumpSpeed = {0, -400, 0};

  // Maximum possible speed
  orxVECTOR maxSpeedPos = {100, -jumpSpeed.fY * 2.0f, 0};
  orxVECTOR maxSpeedNeg = {-100, jumpSpeed.fY, 0};

  // Add world gravity
  orxVector_Add(&speed, &speed, &gravity);

  if (input::HasSet(this))
  {
    // Add influence from user input
    auto previousInput = input::SelectSet(this);
    auto speedDelta = input::GetVector("Left", "Right", "", "");
    auto jump = orxInput_HasBeenActivated("Up");
    orxInput_SelectSet(previousInput);

    // Apply walking movement
    orxVector_Mulf(&speedDelta, &speedDelta, 1000.0 * _rstInfo.fDT);

    // Apply jump
    if (jump && contacts >= 1)
    {
      orxVector_Add(&speedDelta, &speedDelta, &jumpSpeed);
    }

    // Add player input
    orxVector_Add(&speed, &speed, &speedDelta);

    // Slow down if there's no input
    if (orxVector_GetSquareSize(&speedDelta) == 0.0)
    {
      speed.fX /= 200.0 * _rstInfo.fDT;
    }
  }

  // Limit possible speed
  orxVector_Clamp(&speed, &speed, &maxSpeedNeg, &maxSpeedPos);

  // Update object speed
  SetSpeed(speed);
}

void Object::OnCollide(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart, const orxVECTOR &_rvPosition, const orxVECTOR &_rvNormal)
{
  contacts++;
}

void Object::OnSeparate(ScrollObject *_poCollider, orxBODY_PART *_pstPart, orxBODY_PART *_pstColliderPart)
{
  contacts--;
}
