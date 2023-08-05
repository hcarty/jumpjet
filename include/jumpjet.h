/**
 * @file jumpjet.h
 * @date 5-Aug-2023
 */

#ifndef __jumpjet_H__
#define __jumpjet_H__

#define __NO_SCROLLED__
#include "Scroll.h"

/** Game Class
 */
class jumpjet : public Scroll<jumpjet>
{
public:


private:

                orxSTATUS       Bootstrap() const;

                void            Update(const orxCLOCK_INFO &_rstInfo);

                orxSTATUS       Init();
                orxSTATUS       Run();
                void            Exit();
                void            BindObjects();


private:
};

#endif // __jumpjet_H__
