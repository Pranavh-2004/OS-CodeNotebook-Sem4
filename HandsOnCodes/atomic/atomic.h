// Source: http://golubenco.org/atomic-operations.html
#ifndef _ATOMIC_H
#define _ATOMIC_H

/* Check GCC version, just to be safe */
#if !defined(__GNUC__) || (__GNUC__ < 4) || (__GNUC_MINOR__ < 1)
#error atomic.h works only with GCC newer than version 4.1
#endif /* GNUC >= 4.1 */

/**
 * Atomic type.
 */
typedef struct
{
    volatile int counter;
} atomic_t;

#define ATOMIC_INIT(i) {(i)}

/**
 * Read atomic variable
 * @param v pointer of type atomic_t
 *
 * Atomically reads the value of @v.
 */
#define atomic_read(v) ((v)->counter)

/**
 * Set atomic variable
 * @param v pointer of type atomic_t
 * @param i required value
 */
#define atomic_set(v, i) (((v)->counter) = (i))

/**
 * Add value to atomic variable
 * @param i value to add
 * @param v pointer of type atomic_t
 */
#define atomic_add(i, v) __sync_fetch_and_add(&(v)->counter, (i))

/**
 * Subtract value from atomic variable
 * @param i value to subtract
 * @param v pointer of type atomic_t
 */
#define atomic_sub(i, v) __sync_fetch_and_sub(&(v)->counter, (i))

/**
 * Increment atomic variable
 * @param v pointer of type atomic_t
 */
#define atomic_inc(v) __sync_fetch_and_add(&(v)->counter, 1)

/**
 * Decrement atomic variable
 * @param v pointer of type atomic_t
 */
#define atomic_dec(v) __sync_fetch_and_sub(&(v)->counter, 1)

#endif /* _ATOMIC_H */