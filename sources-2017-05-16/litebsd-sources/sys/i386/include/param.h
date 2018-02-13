/*-
 * Copyright (c) 1990, 1993
 *  The Regents of the University of California.  All rights reserved.
 *
 * This code is derived from software contributed to Berkeley by
 * William Jolitz.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *  This product includes software developed by the University of
 *  California, Berkeley and its contributors.
 * 4. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *  @(#)param.h 8.3 (Berkeley) 5/14/95
 */

/*
 * Machine dependent constants for Intel 386.
 */

#define MACHINE "i386"
#define NCPUS 1

/*
 * Round p (pointer or byte index) up to a correctly-aligned value for all
 * data types (int, long, ...).   The result is u_int and must be cast to
 * any desired pointer type.
 */
#define ALIGNBYTES  3
#define ALIGN(p)    (((u_int)(p) + ALIGNBYTES) &~ ALIGNBYTES)

#define NBPG        4096        /* bytes/page */
#define PGOFSET     (NBPG-1)    /* byte offset into page */
#define PGSHIFT     12      /* LOG2(NBPG) */
#define NPTEPG      (NBPG/(sizeof (struct pte)))

#define NBPDR       (1024*NBPG) /* bytes/page dir */
#define PDROFSET    (NBPDR-1)   /* byte offset into page dir */
#define PDRSHIFT    22      /* LOG2(NBPDR) */

#define KERNBASE        0xFE000000  /* start of kernel virtual */
#define BTOPKERNBASE    ((u_long)KERNBASE >> PGSHIFT)

#define DEV_BSIZE       512
#define DEV_BSHIFT      9       /* log2(DEV_BSIZE) */
#define BLKDEV_IOSIZE   2048
#define MAXPHYS         (64 * 1024) /* max raw I/O transfer size */

#define CLSIZE      1
#define CLSIZELOG2  0

/* NOTE: SSIZE, SINCR and UPAGES must be multiples of CLSIZE */
#define SSIZE   1       /* initial stack size/NBPG */
#define SINCR   1       /* increment of stack/NBPG */

#define UPAGES  2       /* pages of u-area */

/*
 * Constants related to network buffer management.
 * MCLBYTES must be no larger than CLBYTES (the software page size), and,
 * on machines that exchange pages of input or output buffers with mbuf
 * clusters (MAPPED_MBUFS), MCLBYTES must also be an integral multiple
 * of the hardware page size.
 */
#define MSIZE       128     /* size of an mbuf */
#define MCLBYTES    1024
#define MCLSHIFT    10
#define MCLOFSET    (MCLBYTES - 1)
#ifndef NMBCLUSTERS
#ifdef GATEWAY
#define NMBCLUSTERS 512     /* map size, max cluster allocation */
#else
#define NMBCLUSTERS 256     /* map size, max cluster allocation */
#endif
#endif

/*
 * Size of kernel malloc arena in CLBYTES-sized logical pages
 */
#ifndef NKMEMCLUSTERS
#define NKMEMCLUSTERS   (2048*1024/CLBYTES)
#endif
/*
 * Some macros for units conversion
 */
/* Core clicks (4096 bytes) to segments and vice versa */
#define ctos(x) (x)
#define stoc(x) (x)

/* Core clicks (4096 bytes) to disk blocks */
#define ctod(x) ((x)<<(PGSHIFT-DEV_BSHIFT))
#define dtoc(x) ((x)>>(PGSHIFT-DEV_BSHIFT))
#define dtob(x) ((x)<<DEV_BSHIFT)

/* clicks to bytes */
#define ctob(x) ((x)<<PGSHIFT)

/* bytes to clicks */
#define btoc(x) (((unsigned)(x)+(NBPG-1))>>PGSHIFT)

#define btodb(bytes)            /* calculates (bytes / DEV_BSIZE) */ \
    ((bytes) >> DEV_BSHIFT)
#define dbtob(db)           /* calculates (db * DEV_BSIZE) */ \
    ((db) << DEV_BSHIFT)

/*
 * Map a ``block device block'' to a file system block.
 * This should be device dependent, and will be if we
 * add an entry to cdevsw/bdevsw for that purpose.
 * For now though just use DEV_BSIZE.
 */
#define bdbtofsb(bn)    ((bn) / (BLKDEV_IOSIZE/DEV_BSIZE))

/*
 * Mach derived conversion macros
 */
#define i386_round_pdr(x)   ((((unsigned)(x)) + NBPDR - 1) & ~(NBPDR-1))
#define i386_trunc_pdr(x)   ((unsigned)(x) & ~(NBPDR-1))
#define i386_round_page(x)  ((((unsigned)(x)) + NBPG - 1) & ~(NBPG-1))
#define i386_trunc_page(x)  ((unsigned)(x) & ~(NBPG-1))
#define i386_btod(x)        ((unsigned)(x) >> PDRSHIFT)
#define i386_dtob(x)        ((unsigned)(x) << PDRSHIFT)
#define i386_btop(x)        ((unsigned)(x) >> PGSHIFT)
#define i386_ptob(x)        ((unsigned)(x) << PGSHIFT)

#ifndef KERNEL
/* DELAY is in locore.s for the kernel */
#define DELAY(n)    { register int N = (n); while (--N > 0); }
#endif

#ifndef _SIMPLELOCK_H_
#define _SIMPLELOCK_H_
/*
 * A simple spin lock.
 *
 * This structure only sets one bit of data, but is sized based on the
 * minimum word size that can be operated on by the hardware test-and-set
 * instruction. It is only needed for multiprocessors, as uniprocessors
 * will always run to completion or a sleep. It is an error to hold one
 * of these locks while a process is sleeping.
 */
struct simplelock {
    int lock_data;
};

#if !defined(DEBUG) && NCPUS > 1
/*
 * The simple-lock routines are the primitives out of which the lock
 * package is built. The machine-dependent code must implement an
 * atomic test_and_set operation that indivisibly sets the simple lock
 * to non-zero and returns its old value. It also assumes that the
 * setting of the lock to zero below is indivisible. Simple locks may
 * only be used for exclusive locks.
 */
static __inline void
simple_lock_init(lkp)
    struct simplelock *lkp;
{

    lkp->lock_data = 0;
}

static __inline void
simple_lock(lkp)
    __volatile struct simplelock *lkp;
{

    while (test_and_set(&lkp->lock_data))
        continue;
}

static __inline int
simple_lock_try(lkp)
    __volatile struct simplelock *lkp;
{

    return (!test_and_set(&lkp->lock_data))
}

static __inline void
simple_unlock(lkp)
    __volatile struct simplelock *lkp;
{

    lkp->lock_data = 0;
}
#endif /* NCPUS > 1 */
#endif /* !_SIMPLELOCK_H_ */