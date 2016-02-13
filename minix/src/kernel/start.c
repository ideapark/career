/* This file contains the C startup code for Minix on Intel processors.
 * It cooperates with mpx.s to set up a good environment for main().
 *
 * This code runs in real mode for a 16 bit kernel and may have to switch
 * to protected mode for a 286.
 * For a 32 bit kernel this already runs in protected mode but the selector
 * are still those given by the BIOS with interrupts disabled, so the
 * descriptors need to be reloaded and interrupt descriptor made.
 */

#include "kernel.h"
#include "protect.h"
#include "proc.h"
#include <stdlib.h>
#include <string.h>

FORWARD _PROTOTYPE(char *get_value, (_CONST char *params, _CONST char *key))

/*===========================================================================
 *                              cstart
 *===========================================================================
 */
PUBLIC void cstart(cs, ds, mds, parmoff, parmsize)
U16_t cs, ds;              /* kernel code and data segment */
U16_t mds;                 /* monitor data segment */
U16_t parmoff, paramsize;  /* boot parameters offset and length */
{
    /* Perform system initializations prior to calling main(). Most settings are
     * determined with help of the environment strings passed by MINIX's loader.
     */
    char params[128*sizeof(char *)];  /* boot monitor parameters */
    register char *value;             /* value in key=value pair */
    extern int etext, end;

    /* Decide if mode is protected; 386 or hgiher implies protected mode.
     * This must be done first, because it is needed for, e.g., seg2phys().
     * For 286 machines we cannot decide on protected mode, yet. This is
     * done below.
     */

}
