#ifndef HWIO_H
#define HWIO_H
/*===========================================================================
 *
 * HWIO REGISTER INPUT/OUTPUT HEADER FILE
 *
 * DESCRIPTION
 * This interface is a replacement for that represented by 
 * msm<ASIC>reg.h, msm<ASIC>io.h and msm<ASIC>redefs.h. For further background
 * and documentation on this interface, please see word docs and ppt docs at 
 *
 * http://lvcrpprd.qualcomm.com/livelink/livelink?func=ll&objId=22836802&objAction=browse&sort=name
 *
 * This file, together with msmhwioreg.h, provides a portable interface
 * from the perspective of chip address file coupling to DMSS register
 * I/O software. The interface defined by msmhwio.h and msmhwioreg.h
 * encapsulates register name, size, type and access method.
 *
 * msmhwioreg.h is an auto-generated file that may be subsequently edited
 * by hand to handle arbitrary register and bit field name changes, and 
 * register type and size changes. When hand editing, one does not directly
 * hand edit msmhwioreg.h or msm<ASIC>reg.h except to cut/paste registers
 * or bitmasks from msm<ASIC>reg.h to msm<ASIC>reg_port.h or from msmhwioreg.h 
 * to msmhwioreg_port.h. One edits an msmreg.pl input file, possibly named
 * something like msmreg_port.dat, to add patterns which msmreg.pl matches 
 * during chip address file parsing. If a pattern from input the port.dat input
 * file is matched, that register or bitmask is not ouput to the register
 * header files, but is output to the *_port.h versions of the register header
 * files. This mechanism allows hand edit of register header file without loss
 * of hand edits on each successive re-parse of chip address file. See msmreg.pl
 * header comments for more information.
 * 
 * msmhwioreg.h also handles register access method changes by allowing users
 * to change a registers I/O functions on a per register basis. By default, 
 * when auto-generated, all register I/O functions are selected from the
 * inline functions listed below.
 *
 * (Note that currently inline functions are not used. This is because
 * rex_int_lock/rex_int_free are not inline and there the masked IO functions
 * would not inline since the compiler will not inline a function that calls
 * a function. The task of figuring out how to inline rex_int_lock has been
 * deferred. So, for the time being, the functions described below are
 * implemented as #define marcos.)
 *
 * To customize register I/O for a single register, one follows the porting
 * mechanism mentioned above and changes the input/output function for the 
 * desired register.
 * 
 * Direct, un-encapsulated, use of register addresses or register header file
 * components is discouraged. To that end, the interface described here fully
 * encapsulates all the CAF components including register address, bit field mask,
 * and bit field shift values in addition to register input and output.
 *
 * INLINE byte in_byte(dword addr) 
 * INLINE byte in_byte_masked(dword addr, dword mask) 
 * INLINE void out_byte(dword addr, byte val) 
 * INLINE void out_byte_masked(dword io, dword mask, byte val) 
 * 
 * INLINE word in_word(dword addr) 
 * INLINE word in_word_masked(dword addr, dword mask) 
 * INLINE void out_word(dword addr, word val) 
 * INLINE void out_word_masked(dword io, dword mask, word val) 
 * 
 * INLINE dword in_dword(dword addr) 
 * INLINE dword in_dword_masked(dword addr, dword mask) 
 * INLINE void out_dword(dword addr, dword val) 
 * INLINE void out_dword_masked(dword io, dword mask, dword val) 
 *
 * Initially, then there is a one-to-one correspondance between the inline
 * functions above and the macro interface below with the inline functions
 * intended as implementation detail of the macro interface. Register access
 * method changes of arbitrary complexity are handled by writing the 
 * appropriate new I/O function and replacing the existing one for the 
 * register under consideration.
 *
 * The interface described below takes chip address file (CAF) symbols as input.
 * Wherever hwiosym, hsio_regsym, or hwio_fldsym appears below, that is 
 * a CAF register or bit field name.
 * 
 * 
 * #define HWIO_IN(hwiosym)
 *    Perform input on register hwiosym. Replaces MSM_IN, MSM_INH and MSM_INW.
 *
 * #define HWIO_INM(hwiosym, m)
 *    Perform masked input on register hwiosym applying mask m. 
 *    Replaces MSM_INM, MSM_INHM, and MSM_INWM.
 *
 * #define HWIO_OUT(hwiosym, val)
 *    Write input val on register hwiosym. Replaces MSM_OUT, MSM_OUTH, and 
 *    MSM_OUTW.
 *
 * #define HWIO_OUTM(hwiosym, mask, val)
 *    Write input val on register hwiosym. Input mask is applied to shadow 
 *    memory and val such that only bits in mask are updated on register hwiosym
 *    and shadow memory. Replaces MSM_OUTM, MSM_OUTHM, and MSM_OUTWM.
 *
 * #define HWIO_ADDR(hwiosym)
 *    Get the register address of hwiosym. Replaces the unencapulsated use of
 *    of numeric literal HEX constants for register address.
 *
 * #define HWIO_RMSK(hwiosym)
 *    Get the mask describing valid bits in register hwiosym. Replaces direct,
 *    unencapsulated use of mask symbol from register header file.
 *
 * #define HWIO_RSHFT(hwiosym)
 *    Get the shift value of the least significant bit in register hwiosym.a
 *    Replaces SHIFT_FROM_MASK.
 *
 * #define HWIO_FMSK(hwio_regsym, hwio_fldsym)
 *    Get the bit field mask for bit field hwio_fldsym in register hwio_regsym.
 *    Replaces the direct, unencapsulated use of bit field masks from register
 *    header file.
 *
 * #define HWIO_SHFT(hwio_regsym, hwio_fldsym)
 *    Get the shift value of the least significant bit of bit field hwio_fldsym
 *    in register hwio_regsym. Replaces SHIFT_FROM_MASK.
 * 
 * Copyright (c) 1998, 1999 by QUALCOMM, Incorporated.  All Rights Reserved.
 * Copyright (c) 2000, 2001 by QUALCOMM, Incorporated.  All Rights Reserved.
 * Copyright (c) 2002 by QUALCOMM, Incorporated.  All Rights Reserved.
 *===========================================================================*/

/*===========================================================================
 *
 * EDIT HISTORY FOR FILE
 *
 * This section contains comments describing changes made to this file.
 * Notice that changes are listed in reverse chronological order.
 *
 * $Header: //depot/asic/qsc1100/drivers/hw/msmhwio.h#3 $
 *
 * when       who     what, where, why
 * --------   ---     ----------------------------------------------------------
 * 05/01/06   cr      Added support for VALUE keyword in HWIO auto-gen file
 *                    set. Now the bit field values have names from CAF and
 *                    are encapsulated in HWIO.
 * 05/19/05   wd      Support for L4 linex.
 * 4/29/02    cr      initial revision 
 *===========================================================================*/

#include "customer.h"
#include "msmreg.h"

#include "msmahb.h"


/*===========================================================================
 *
 *                         MACRO DECLARATIONS
 *
 *===========================================================================*/

#define __msm_inx(io)        ( ((io) - MSM_BASE         )/4)
#define __ahb_inx(io)        ( ((io) - AHB_BASE         )/4)
#define __msm_finx(io) (byte)( ((io) - MSM_F_BASE_START )/4)

#define HWIO_IN(hwiosym)              __msmhwio_in(hwiosym)
#define HWIO_INI(hwiosym, index)              __msmhwio_ini(hwiosym, index)
#define HWIO_INI2(hwiosym, index1, index2)              __msmhwio_ini2(hwiosym, index1, index2)
#define HWIO_INM(hwiosym, mask)          __msmhwio_inm(hwiosym, mask)
#define HWIO_INMI(hwiosym, index, mask)              __msmhwio_inmi(hwiosym, index, mask)
#define HWIO_INMI2(hwiosym, index1, index2, mask)              __msmhwio_inmi2(hwiosym, index1, index2, mask)
#define HWIO_OUT(hwiosym, val)        __msmhwio_out(hwiosym, val)
#define HWIO_OUTI(hwiosym, index, val)        __msmhwio_outi(hwiosym, index, val)
#define HWIO_OUTI2(hwiosym, index1, index2, val)        __msmhwio_outi2(hwiosym, index1, index2, val)
#define HWIO_OUTM(hwiosym, mask, val) __msmhwio_outm(hwiosym, mask, val)
#define HWIO_OUTMI(hwiosym, index, mask, val)        __msmhwio_outmi(hwiosym, index, mask, val)
#define HWIO_OUTMI2(hwiosym, index1, index2, mask, val)        __msmhwio_outmi2(hwiosym, index1, index2, mask, val)
#define HWIO_ADDR(hwiosym)            __msmhwio_addr(hwiosym)
#define HWIO_ADDRI(hwiosym, index)            __msmhwio_addri(hwiosym, index)
#define HWIO_ADDRI2(hwiosym, index1, index2)            __msmhwio_addri2(hwiosym, index1, index2)
#define HWIO_RMSK(hwiosym)            __msmhwio_rmsk(hwiosym)
#define HWIO_RSHFT(hwiosym)            __msmhwio_rshft(hwiosym)
#define HWIO_FMSK(hwio_regsym, hwio_fldsym)  __msmhwio_fmsk(hwio_regsym, hwio_fldsym)
#define HWIO_SHFT(hwio_regsym, hwio_fldsym)  __msmhwio_shft(hwio_regsym, hwio_fldsym)
#define HWIO_FVAL(hwio_regsym, hwio_fldsym, hwio_valsym) __msmhwio_fval(hwio_regsym, hwio_fldsym, hwio_valsym)


/* Added for support of macros appearing in HSU code for ULC */
/* Implemention of some short-cut macros for accessing register fields*/

#define HWIO_INF(io, field)               (HWIO_INM(io, HWIO_FMSK(io, field)) >> HWIO_SHFT(io, field))
#define HWIO_INFI(io, index, field)       (HWIO_INMI(io, index, HWIO_FMSK(io, field)) >> HWIO_SHFT(io, field))
#define HWIO_OUTF(io, field, val)          HWIO_OUTM(io, HWIO_FMSK(io, field), (val) << HWIO_SHFT(io, field))
#define HWIO_OUTFI(io, index, field, val)  HWIO_OUTMI(io, index, HWIO_FMSK(io, field), (val) << HWIO_SHFT(io, field))


#ifdef FEATURE_L4
#error code not present
#endif /* FEATURE_L4 */
#ifdef T_MSM6500
  #define HWIO_IS_MSM(addr) (addr>=CHIP_BASE && addr<=0x80002a14)
#else
#error code not present
#endif


 /* Implement the 6200 register interface in terms of HWIO so that 
  * unmodified 6200 drivers can be dropped into 6300 builds.
  *
  * Note that this change prevents backward compatibility to old MSMIO 
  * interface as it exists in 6050, 6000, and older targets when 
  * FEATURE_6200_COMPATIBILITY is defined.
  *
  * Below one will see MSM_OUTM() from 6200 being replace with HWIO_OUTM()
  * as well as MSM_OUTSH() from 6200 being replaced with HWIO_OUTM().
  * In 6100/6300 as in 6200, register I/O only shadows write-only registers.
  * HWIO_OUTM() on read/write register does what MSM_OUTM() does in 6200;
  * reads the register applies the mask, and then writes the register. 
  * HWIO_OUTM() on a write-only register does what MSM_OUTSH() does in 6200;
  * apply mask to shadow memory, and then write register.
  */
#ifdef FEATURE_6200_COMPATIBILITY
#define MSM_OUT( io, val )         HWIO_OUT(io, val) 
#define MSM_OUTM( io, mask, val)   HWIO_OUTM(io, mask, val)
#define MSM_IN( io )               HWIO_IN(io)
#define MSM_INM(io, mask)          HWIO_INM(io, mask)
#define MSM_INF(io, field)         (HWIO_INM(io,field) >> HWIO_SHFT(io,field))
#define MSM_FIELD(field, val)      (((val) << field##_SHFT) & (field##_BMSK))
#define MSM_OUTSH(io, mask, val)   HWIO_OUTM(io, mask, val)
#define MSM_FOUTSH(io, field, val) HWIO_OUTM(io, mask, val)
#define OUTP32(io, val)  	   HWIO_OUT(io, val)
#endif /* FEATURE_6200_COMPATIBILITY */

//DA Added macros for indexed register I/O
#define __msmhwio_in(hwiosym)  HWIO_##hwiosym##_IN
#define __msmhwio_ini(hwiosym, index)  HWIO_##hwiosym##_INI(index)
#define __msmhwio_ini2(hwiosym, index1, index2)  HWIO_##hwiosym##_INI2(index1, index2)
#define __msmhwio_inm(hwiosym, mask)  HWIO_##hwiosym##_INM(mask)
#define __msmhwio_inmi(hwiosym, index, mask)  HWIO_##hwiosym##_INMI(index, mask)
#define __msmhwio_inmi2(hwiosym, index1, index2, mask)  HWIO_##hwiosym##_INMI2(index1, index2, mask)
#define __msmhwio_out(hwiosym, val) HWIO_##hwiosym##_OUT(val)
#define __msmhwio_outi(hwiosym, index, val) HWIO_##hwiosym##_OUTI(index, val)
#define __msmhwio_outi2(hwiosym, index1, index2, val) HWIO_##hwiosym##_OUTI2(index1, index2, val)
#define __msmhwio_outm(hwiosym, mask, val) HWIO_##hwiosym##_OUTM(mask, val)
#define __msmhwio_outmi(hwiosym, index, mask, val) HWIO_##hwiosym##_OUTMI(index, mask, val)
#define __msmhwio_outmi2(hwiosym, index1, index2, mask, val) HWIO_##hwiosym##_OUTMI2(index1, index2, mask, val)

#define __msmhwio_shdw(hwiosym) HWIO_##hwiosym##_shadow
#define __msmhwio_addr(hwiosym) HWIO_##hwiosym##_ADDR
#ifdef FEATURE_SC2X_SW_PORT
#define __msmhwio_addri(hwiosym, index) HWIO_##hwiosym##_ADDR(index)
#define __msmhwio_addri2(hwiosym, index1, index2) HWIO_##hwiosym##_ADDR(index1, index2)
#define __msmhwio_shdwi(hwiosym, index) HWIO_##hwiosym##_SHDW(index)
#define HWIO_RMSKI(hwiosym,i)            __msmhwio_rmski(hwiosym,i)
#define __msmhwio_rmski(hwiosym,i) HWIO_##hwiosym##_RMSK(i)
#else
#define __msmhwio_addri(hwiosym, index) HWIO_##hwiosym##_ADDRI(index)
#define __msmhwio_addri2(hwiosym, index1, index2) HWIO_##hwiosym##_ADDRI2(index1, index2)
#define __msmhwio_shdwi(hwiosym, index) HWIO_##hwiosym##_SHDWI(index)
#endif /* FEATURE_SC2X_SW_PORT */
#define __msmhwio_rmsk(hwiosym) HWIO_##hwiosym##_RMSK
#define __msmhwio_fmsk(hwio_regsym, hwio_fldsym) HWIO_##hwio_regsym##_##hwio_fldsym##_BMSK
#define __msmhwio_rshft(hwio_regsym) HWIO_##hwio_regsym##_SHFT
#define __msmhwio_shft(hwio_regsym, hwio_fldsym) HWIO_##hwio_regsym##_##hwio_fldsym##_SHFT
#define __msmhwio_fval(hwio_regsym, hwio_fldsym, hwio_valsym) HWIO_##hwio_regsym##_##hwio_fldsym##_##hwio_valsym##_FVAL
#define __msmhwio_msminx(io)  ( ((HWIO_##io##_ADDR) - MSM_BASE         )/4)
#define __msmhwio_ahbinx(io)  ( ((HWIO_##io##_ADDR) - AHB_BASE         )/4)
#define __msmhwio_msmfinx(io) (byte)( ((HWIO_##io##_ADDR) - MSM_F_BASE_START )/4)
#ifdef FEATURE_L4
#error code not present
#endif /* FEATURE_L4 */

#ifndef _ARM_ASM_
#include "comdef.h"

#ifndef FEATURE_L4
extern dword rex_int_lock(void);
extern dword rex_int_free(void);
/*extern const int hwio_interrupts_locked_by_user;*/
#endif /* FEATURE_L4 */
#endif /* _ARM_ASM_ */

#define __inp(port)         (*((volatile byte *) (port)))
#define __inpw(port)        (*((volatile word *) (port)))
#define __inpdw(port)       (*((volatile dword *)(port)))

#define __outp(port, val)   (*((volatile byte *) (port)) = ((byte) (val)))
#define __outpw(port, val)  (*((volatile word *) (port)) = ((word) (val)))
#define __outpdw(port, val) (*((volatile dword *) (port)) = ((dword) (val)))



#define in_byte(addr) 					 (__inp(addr))
#define in_byte_masked(addr, mask)  (__inp(addr) & (byte)mask) 
#define out_byte(addr, val) __outp(addr,val)
#define in_word(addr) (__inpw(addr))
#define in_word_masked(addr, mask) ( __inpw(addr) & (word)mask)
#define out_word(addr, val) __outpw(addr,val)
#define in_dword(addr) (__inpdw(addr))
#define in_dword_masked(addr, mask) ( __inpdw(addr) & mask )
#define out_dword(addr, val)  __outpdw(addr,val)

#ifndef FEATURE_L4
/*hwio_interrupts_locked_by_user = value */
#define HWIO_LOCK( )    \
    do { \
      boolean HWIO_LOCK_required = TRUE; \
      word hwio_sav; \
      INTLOCK_SAV( hwio_sav )
#else
#error code not present
#endif /* FEATURE_L4 */

#define HWIO_UNLOCK( )    \
    HWIO_LOCK_required = HWIO_LOCK_required; \
    INTFREE_SAV( hwio_sav );  \
    } while (0);

#ifndef FEATURE_L4
/*if (!hwio_interrupts_locked_by_user) */
#define HWIO_INTLOCK() \
 do { \
   word intlock_sav=1; \
   INTLOCK_SAV(intlock_sav)
/*if (!hwio_interrupts_locked_by_user) */
#define HWIO_INTFREE() \
   INTFREE_SAV(intlock_sav); \
 } while (0);
#else
#error code not present
#endif /* FEATURE_L4 */

/* shadowed, masked output for write-only registers */
#define out_byte_masked(io, mask, val, shadow)  \
  HWIO_INTLOCK();	\
  shadow = (shadow & (word)(~(mask))) | ((word)((val) & (mask))); \
  (void) out_byte( io, shadow); \
  HWIO_INTFREE()

#define out_word_masked(io, mask, val, shadow)  \
  HWIO_INTLOCK( ); \
  shadow = (shadow & (word)(~(mask))) |  ((word)((val) & (mask))); \
  (void) out_word( io, shadow); \
  HWIO_INTFREE( )

#define out_dword_masked(io, mask, val, shadow)  \
   HWIO_INTLOCK( ); \
   shadow = (shadow & (dword)(~(mask))) | ((dword)((val) & (mask))); \
   (void) out_dword( io, shadow); \
   HWIO_INTFREE( )

/* non-shadowed, masked output for read/write registers */
/* intlock and intfree taken by caller */
#define out_byte_masked_ns(io, mask, val, current_reg_content)  \
  (void) out_byte( io, ((current_reg_content & (word)(~(mask))) | \
		       ((word)((val) & (mask)))) )

/* intlock and intfree taken by caller */
#define out_word_masked_ns(io, mask, val, current_reg_content)  \
  (void) out_word( io, ((current_reg_content & (word)(~(mask))) | \
		       ((word)((val) & (mask)))) )

/* intlock and intfree taken by caller */
#define out_dword_masked_ns(io, mask, val, current_reg_content)  (void) out_dword( io, ((current_reg_content & (dword)(~(mask))) | ((dword)((val) & (mask)))) )

#define HWIO_SHDW(hwiosym)            __msmhwio_shdw(hwiosym)
#define HWIO_SHDWI(hwiosym, index)            __msmhwio_shdwi(hwiosym, index)

#endif /* HWIO_H */

