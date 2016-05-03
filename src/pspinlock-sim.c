/*
 * Copyright (C) 2016 Alexander Saprykin <xelfium@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA.
 */

#include "pmem.h"
#include "pmutex.h"
#include "pspinlock.h"

struct _PSpinLock {
	PMutex *mutex;
};

P_LIB_API PSpinLock *
p_spinlock_new (void)
{
	PSpinLock *ret;

	if ((ret = p_malloc0 (sizeof (PSpinLock))) == NULL) {
		P_ERROR ("PSpinLock: failed to allocate memory");
		return NULL;
	}

	if ((ret->mutex = p_mutex_new ()) == NULL) {
		P_ERROR ("PSpinLock: failed to create mutex object");
		p_free (ret);
		return NULL;
	}

	return ret;
}

P_LIB_API pboolean
p_spinlock_lock (PSpinLock *spinlock)
{
	if (spinlock == NULL)
		return FALSE;

	return p_mutex_lock (spinlock->mutex);
}

P_LIB_API pboolean
p_spinlock_trylock (PSpinLock *spinlock)
{
	if (spinlock == NULL)
		return FALSE;

	return p_mutex_trylock (spinlock->mutex);
}

P_LIB_API pboolean
p_spinlock_unlock (PSpinLock *spinlock)
{
	if (spinlock == NULL)
		return FALSE;

	return p_mutex_unlock (spinlock->mutex);
}

P_LIB_API void
p_spinlock_free (PSpinLock *spinlock)
{
	if (spinlock == NULL)
		return;

	p_mutex_free (spinlock->mutex);
	p_free (spinlock);
}