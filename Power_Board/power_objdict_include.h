/* 
 * File:   power_objdict_include.h
 * Author: ken
 *
 * Created on May 20, 2015, 7:05 PM
 */

#ifndef POWER_OBJDICT_INCLUDE_H
#define	POWER_OBJDICT_INCLUDE_H

#ifdef	__cplusplus
extern "C" {
#endif
#ifdef CONF73
#include "power_objdict_73.h"
#define CO(_X) power73_ ## _X
#else
#include "power_objdict_3.h"
#define CO(_X) power3_ ## _X
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* POWER_OBJDICT_INCLUDE_H */

