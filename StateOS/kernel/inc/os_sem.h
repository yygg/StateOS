/******************************************************************************

    @file    StateOS: os_sem.h
    @author  Rajmund Szymanski
    @date    22.10.2017
    @brief   This file contains definitions for StateOS.

 ******************************************************************************

    StateOS - Copyright (C) 2013 Rajmund Szymanski.

    This file is part of StateOS distribution.

    StateOS is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published
    by the Free Software Foundation; either version 3 of the License,
    or (at your option) any later version.

    StateOS is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <http://www.gnu.org/licenses/>.

 ******************************************************************************/

#ifndef __STATEOS_SEM_H
#define __STATEOS_SEM_H

#include "oskernel.h"

#ifdef __cplusplus
extern "C" {
#endif

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : semaphore                                                                                      *
 *                     like a POSIX semaphore                                                                         *
 *                                                                                                                    *
 **********************************************************************************************************************/

typedef struct __sem sem_t, * const sem_id;

struct __sem
{
	tsk_t  * queue; // next process in the DELAYED queue
	void   * res;   // allocated semaphore object's resource
	unsigned count; // semaphore's current value
	unsigned limit; // semaphore's value limit
};

/* -------------------------------------------------------------------------- */

#define semBinary    (  1U ) // binary semaphore
#define semNormal    ( ~0U ) // counting semaphore
#define semCounting  ( ~0U ) // counting semaphore
#define semMASK      ( ~0U )

/* -------------------------------------------------------------------------- */

#define UMIN( a, b ) \
 ((unsigned)( a )<(unsigned)( b )?(unsigned)( a ):(unsigned)( b ))

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : _SEM_INIT                                                                                      *
 *                                                                                                                    *
 * Description       : create and initilize a semaphore object                                                        *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 * Return            : semaphore object                                                                               *
 *                                                                                                                    *
 * Note              : for internal use                                                                               *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define               _SEM_INIT( _init, _limit ) { 0, 0, UMIN(_init,_limit), _limit }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : OS_SEM                                                                                         *
 *                                                                                                                    *
 * Description       : define and initilize a semaphore object                                                        *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : name of a pointer to semaphore object                                                          *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define             OS_SEM( sem, init, limit )                     \
                       sem_t sem##__sem = _SEM_INIT( init, limit ); \
                       sem_id sem = & sem##__sem

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : static_SEM                                                                                     *
 *                                                                                                                    *
 * Description       : define and initilize a static semaphore object                                                 *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : name of a pointer to semaphore object                                                          *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 **********************************************************************************************************************/

#define         static_SEM( sem, init, limit )                     \
                static sem_t sem##__sem = _SEM_INIT( init, limit ); \
                static sem_id sem = & sem##__sem

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : SEM_INIT                                                                                       *
 *                                                                                                                    *
 * Description       : create and initilize a semaphore object                                                        *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 * Return            : semaphore object                                                                               *
 *                                                                                                                    *
 * Note              : use only in 'C' code                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

#ifndef __cplusplus
#define                SEM_INIT( init, limit ) \
                      _SEM_INIT( init, limit )
#endif

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : SEM_CREATE                                                                                     *
 * Alias             : SEM_NEW                                                                                        *
 *                                                                                                                    *
 * Description       : create and initilize a semaphore object                                                        *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 * Return            : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Note              : use only in 'C' code                                                                           *
 *                                                                                                                    *
 **********************************************************************************************************************/

#ifndef __cplusplus
#define                SEM_CREATE( init, limit ) \
             & (sem_t) SEM_INIT  ( init, limit )
#define                SEM_NEW \
                       SEM_CREATE
#endif

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_init                                                                                       *
 *                                                                                                                    *
 * Description       : initilize a semaphore object                                                                   *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 * Return            : none                                                                                           *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

void sem_init( sem_t *sem, unsigned init, unsigned limit );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_create                                                                                     *
 * Alias             : sem_new                                                                                        *
 *                                                                                                                    *
 * Description       : create and initilize a new semaphore object                                                    *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore                                                     *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 * Return            : pointer to semaphore object (semaphore successfully created)                                   *
 *   0               : semaphore not created (not enough free memory)                                                 *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

sem_t *sem_create( unsigned init, unsigned limit );
__STATIC_INLINE
sem_t *sem_new   ( unsigned init, unsigned limit ) { return sem_create(init, limit); }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_kill                                                                                       *
 *                                                                                                                    *
 * Description       : reset the semaphore object and wake up all waiting tasks with 'E_STOPPED' event value          *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return            : none                                                                                           *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

void sem_kill( sem_t *sem );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_delete                                                                                     *
 *                                                                                                                    *
 * Description       : reset the semaphore object and free allocated resource                                         *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return            : none                                                                                           *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

void sem_delete( sem_t *sem );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_waitUntil                                                                                  *
 *                                                                                                                    *
 * Description       : try to lock the semaphore object,                                                              *
 *                     wait until given timepoint if the semaphore object can't be locked immediately                 *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *   time            : timepoint value                                                                                *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully locked                                                       *
 *   E_STOPPED       : semaphore object was killed before the specified timeout expired                               *
 *   E_TIMEOUT       : semaphore object was not locked before the specified timeout expired                           *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

unsigned sem_waitUntil( sem_t *sem, uint32_t time );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_waitFor                                                                                    *
 *                                                                                                                    *
 * Description       : try to lock the semaphore object,                                                              *
 *                     wait for given duration of time if the semaphore object can't be locked immediately            *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *   delay           : duration of time (maximum number of ticks to wait for lock the semaphore object)               *
 *                     IMMEDIATE: don't wait if the semaphore object can't be locked immediately                      *
 *                     INFINITE:  wait indefinitly until the semaphore object has been locked                         *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully locked                                                       *
 *   E_STOPPED       : semaphore object was killed before the specified timeout expired                               *
 *   E_TIMEOUT       : semaphore object was not locked before the specified timeout expired                           *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

unsigned sem_waitFor( sem_t *sem, uint32_t delay );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_wait                                                                                       *
 *                                                                                                                    *
 * Description       : try to lock the semaphore object,                                                              *
 *                     wait indefinitly if the semaphore object can't be locked immediately                           *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully locked                                                       *
 *   E_STOPPED       : semaphore object was killed                                                                    *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

__STATIC_INLINE
unsigned sem_wait( sem_t *sem ) { return sem_waitFor(sem, INFINITE); }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_take                                                                                       *
 *                                                                                                                    *
 * Description       : try to lock the semaphore object,                                                              *
 *                     don't wait if the semaphore object can't be locked immediately                                 *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully locked                                                       *
 *   E_TIMEOUT       : semaphore object can't be locked immediately                                                   *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

__STATIC_INLINE
unsigned sem_take( sem_t *sem ) { return sem_waitFor(sem, IMMEDIATE); }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_takeISR                                                                                    *
 *                                                                                                                    *
 * Description       : try to lock the semaphore object,                                                              *
 *                     don't wait if the semaphore object can't be locked immediately                                 *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully locked                                                       *
 *   E_TIMEOUT       : semaphore object can't be locked immediately                                                   *
 *                                                                                                                    *
 * Note              : use only in handler mode                                                                       *
 *                                                                                                                    *
 **********************************************************************************************************************/

__STATIC_INLINE
unsigned sem_takeISR( sem_t *sem ) { return sem_waitFor(sem, IMMEDIATE); }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_sendUntil                                                                                  *
 *                                                                                                                    *
 * Description       : try to unlock the semaphore object,                                                            *
 *                     wait until given timepoint if the semaphore object can't be unlocked immediately               *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *   time            : timepoint value                                                                                *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully unlocked                                                     *
 *   E_STOPPED       : semaphore object was killed before the specified timeout expired                               *
 *   E_TIMEOUT       : semaphore object was not unlocked before the specified timeout expired                         *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

unsigned sem_sendUntil( sem_t *sem, uint32_t time );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_sendFor                                                                                    *
 *                                                                                                                    *
 * Description       : try to unlock the semaphore object,                                                            *
 *                     wait for given duration of time if the semaphore object can't be unlocked immediately          *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *   delay           : duration of time (maximum number of ticks to wait for unlock the semaphore object)             *
 *                     IMMEDIATE: don't wait if the semaphore object can't be unlocked immediately                    *
 *                     INFINITE:  wait indefinitly until the semaphore object has been unlocked                       *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully unlocked                                                     *
 *   E_STOPPED       : semaphore object was killed before the specified timeout expired                               *
 *   E_TIMEOUT       : semaphore object was not unlocked before the specified timeout expired                         *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

unsigned sem_sendFor( sem_t *sem, uint32_t delay );

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_send                                                                                       *
 *                                                                                                                    *
 * Description       : try to unlock the semaphore object,                                                            *
 *                     wait indefinitly if the semaphore object can't be unlocked immediately                         *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully unlocked                                                     *
 *   E_STOPPED       : semaphore object was killed                                                                    *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

__STATIC_INLINE
unsigned sem_send( sem_t *sem ) { return sem_sendFor(sem, INFINITE); }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_give                                                                                       *
 *                                                                                                                    *
 * Description       : try to unlock the semaphore object,                                                            *
 *                     don't wait if the semaphore object can't be unlocked immediately                               *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully unlocked                                                     *
 *   E_TIMEOUT       : semaphore object can't be unlocked immediately                                                 *
 *                                                                                                                    *
 * Note              : use only in thread mode                                                                        *
 *                                                                                                                    *
 **********************************************************************************************************************/

__STATIC_INLINE
unsigned sem_give( sem_t *sem ) { return sem_sendFor(sem, IMMEDIATE); }

/**********************************************************************************************************************
 *                                                                                                                    *
 * Name              : sem_giveISR                                                                                    *
 *                                                                                                                    *
 * Description       : try to unlock the semaphore object,                                                            *
 *                     don't wait if the semaphore object can't be unlocked immediately                               *
 *                                                                                                                    *
 * Parameters                                                                                                         *
 *   sem             : pointer to semaphore object                                                                    *
 *                                                                                                                    *
 * Return                                                                                                             *
 *   E_SUCCESS       : semaphore object was successfully unlocked                                                     *
 *   E_TIMEOUT       : semaphore object can't be unlocked immediately                                                 *
 *                                                                                                                    *
 * Note              : use only in handler mode                                                                       *
 *                                                                                                                    *
 **********************************************************************************************************************/

__STATIC_INLINE
unsigned sem_giveISR( sem_t *sem ) { return sem_sendFor(sem, IMMEDIATE); }

#ifdef __cplusplus
}
#endif

/* -------------------------------------------------------------------------- */

#ifdef __cplusplus

/**********************************************************************************************************************
 *                                                                                                                    *
 * Class             : Semaphore                                                                                      *
 *                                                                                                                    *
 * Description       : create and initilize a semaphore object                                                        *
 *                                                                                                                    *
 * Constructor parameters                                                                                             *
 *   init            : initial value of semaphore counter                                                             *
 *   limit           : maximum value of semaphore counter                                                             *
 *                     semBinary: binary semaphore                                                                    *
 *                     semNormal, semCounting: counting semaphore (default)                                           *
 *                     otherwise: limited semaphore                                                                   *
 *                                                                                                                    *
 **********************************************************************************************************************/

struct Semaphore : public __sem
{
	 explicit
	 Semaphore( const unsigned _init, const unsigned _limit = semCounting ): __sem _SEM_INIT(_init, _limit) {}
	~Semaphore( void ) { assert(queue == nullptr); }

	void     kill     ( void )            {        sem_kill     (this);         }
	unsigned waitUntil( uint32_t _time )  { return sem_waitUntil(this, _time);  }
	unsigned waitFor  ( uint32_t _delay ) { return sem_waitFor  (this, _delay); }
	unsigned wait     ( void )            { return sem_wait     (this);         }
	unsigned take     ( void )            { return sem_take     (this);         }
	unsigned takeISR  ( void )            { return sem_takeISR  (this);         }
	unsigned sendUntil( uint32_t _time )  { return sem_sendUntil(this, _time);  }
	unsigned sendFor  ( uint32_t _delay ) { return sem_sendFor  (this, _delay); }
	unsigned send     ( void )            { return sem_send     (this);         }
	unsigned give     ( void )            { return sem_give     (this);         }
	unsigned giveISR  ( void )            { return sem_giveISR  (this);         }
};

/**********************************************************************************************************************
 *                                                                                                                    *
 * Class             : BinarySemaphore                                                                                *
 *                                                                                                                    *
 * Description       : create and initilize a binary semaphore object                                                 *
 *                                                                                                                    *
 * Constructor parameters                                                                                             *
 *   init            : initial value of semaphore counter                                                             *
 *                                                                                                                    *
 **********************************************************************************************************************/

struct BinarySemaphore : public Semaphore
{
	explicit
	BinarySemaphore( const unsigned _init = 0 ): Semaphore(_init, semBinary) {}
};

#endif

/* -------------------------------------------------------------------------- */

#endif//__STATEOS_SEM_H
