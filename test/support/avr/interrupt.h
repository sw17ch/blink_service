#ifndef _AVR_INTERRUPT_H_
#define _AVR_INTERRUPT_H_

#include <avr/io.h>

static void sei(void) {}; // Redefine the macro as a function so that it can be mocked by CMock
static void cli(void) {}; // Redefine the macro as a function so that it can be mocked by CMock

#define ISR void ISR

#define SIGNAL(vector) \
  void vector (void)

#if defined(__DOXYGEN__)
/** \def EMPTY_INTERRUPT(vector)
    \ingroup avr_interrupts

    \code #include <avr/interrupt.h> \endcode

    Defines an empty interrupt handler function. This will not generate
    any prolog or epilog code and will only return from the ISR. Do not
    define a function body as this will define it for you.
    Example:
    \code EMPTY_INTERRUPT(ADC_vect);\endcode */
#  define EMPTY_INTERRUPT(vector)
#else  /* real code */

#ifdef __cplusplus
#  define EMPTY_INTERRUPT(vector)                \
    extern "C" void vector(void) __attribute__ ((signal,naked,__INTR_ATTRS));    \
    void vector (void) {  __asm__ __volatile__ ("reti" ::); }
#else
#  define EMPTY_INTERRUPT(vector)                \
    void vector (void) __attribute__ ((signal,naked,__INTR_ATTRS));    \
    void vector (void) { __asm__ __volatile__ ("reti" ::); }
#endif

#endif /* DOXYGEN */

#if defined(__DOXYGEN__)
/** \def ISR_ALIAS(vector, target_vector)
    \ingroup avr_interrupts

    \code #include <avr/interrupt.h> \endcode

    Aliases a given vector to another one in the same manner as the
    ISR_ALIASOF attribute for the ISR() macro. Unlike the ISR_ALIASOF
    attribute macro however, this is compatible for all versions of
    GCC rather than just GCC version 4.2 onwards.

    \note This macro creates a trampoline function for the aliased
    macro.  This will result in a two cycle penalty for the aliased
    vector compared to the ISR the vector is aliased to, due to the
    JMP/RJMP opcode used.

    \deprecated
    For new code, the use of ISR(..., ISR_ALIASOF(...))  is
    recommended.

    Example:
    \code
    ISR(INT0_vect)
    {
        PORTB = 42;
    }

    ISR_ALIAS(INT1_vect, INT0_vect);
    \endcode 
*/
#  define ISR_ALIAS(vector, target_vector)
#else /* real code */

#ifdef __cplusplus
#  if defined(__AVR_MEGA__) && __AVR_MEGA__
#    define ISR_ALIAS(vector, tgt) extern "C" void vector (void) \
	__attribute__((signal, naked, __INTR_ATTRS)); \
	void vector (void) { asm volatile ("jmp " __STRINGIFY(tgt) ::); }
#  else /* !__AVR_MEGA */
#    define ISR_ALIAS(vector, tgt) extern "C" void vector (void) \
	__attribute__((signal, naked, __INTR_ATTRS)); \
	void vector (void) { asm volatile ("rjmp " __STRINGIFY(tgt) ::); }
#  endif  /* __AVR_MEGA__ */
#else	  /* !__cplusplus */
#  if defined(__AVR_MEGA__) && __AVR_MEGA__
#  define ISR_ALIAS(vector, tgt) void vector (void) \
	__attribute__((signal, naked, __INTR_ATTRS)); \
	void vector (void) { asm volatile ("jmp " __STRINGIFY(tgt) ::); }
#  else /* !__AVR_MEGA */
#  define ISR_ALIAS(vector, tgt) void vector (void) \
	__attribute__((signal, naked, __INTR_ATTRS)); \
	void vector (void) { asm volatile ("rjmp " __STRINGIFY(tgt) ::); }
#  endif  /* __AVR_MEGA__ */
#endif	/* __cplusplus */

#endif /* DOXYGEN */

#if defined(__DOXYGEN__)
/** \def reti()
    \ingroup avr_interrupts

    \code #include <avr/interrupt.h> \endcode

    Returns from an interrupt routine, enabling global interrupts. This should
    be the last command executed before leaving an ISR defined with the ISR_NAKED
    attribute.

    This macro actually compiles into a single line of assembly, so there is
    no function call overhead.
*/
#  define reti()
#else  /* !DOXYGEN */
#  define reti()  __asm__ __volatile__ ("reti" ::)
#endif /* DOXYGEN */

#if defined(__DOXYGEN__)
/** \def BADISR_vect
    \ingroup avr_interrupts

    \code #include <avr/interrupt.h> \endcode

    This is a vector which is aliased to __vector_default, the vector
    executed when an ISR fires with no accompanying ISR handler. This
    may be used along with the ISR() macro to create a catch-all for
    undefined but used ISRs for debugging purposes.
*/
#  define BADISR_vect
#else  /* !DOXYGEN */
#  define BADISR_vect __vector_default
#endif /* DOXYGEN */

/** \name ISR attributes */

#if defined(__DOXYGEN__)
/** \def ISR_BLOCK
    \ingroup avr_interrupts

    \code# include <avr/interrupt.h> \endcode

    Identical to an ISR with no attributes specified. Global
    interrupts are initially disabled by the AVR hardware when
    entering the ISR, without the compiler modifying this state.

    Use this attribute in the attributes parameter of the ISR macro.
*/
#  define ISR_BLOCK

/** \def ISR_NOBLOCK
    \ingroup avr_interrupts

    \code# include <avr/interrupt.h> \endcode

    ISR runs with global interrupts initially enabled.  The interrupt
    enable flag is activated by the compiler as early as possible
    within the ISR to ensure minimal processing delay for nested
    interrupts.

    This may be used to create nested ISRs, however care should be
    taken to avoid stack overflows, or to avoid infinitely entering
    the ISR for those cases where the AVR hardware does not clear the
    respective interrupt flag before entering the ISR.

    Use this attribute in the attributes parameter of the ISR macro.
*/
#  define ISR_NOBLOCK

/** \def ISR_NAKED
    \ingroup avr_interrupts

    \code# include <avr/interrupt.h> \endcode

    ISR is created with no prologue or epilogue code. The user code is
    responsible for preservation of the machine state including the
    SREG register, as well as placing a reti() at the end of the
    interrupt routine.

    Use this attribute in the attributes parameter of the ISR macro.
*/
#  define ISR_NAKED

/** \def ISR_ALIASOF(target_vector)
    \ingroup avr_interrupts

    \code#include <avr/interrupt.h>\endcode

    The ISR is linked to another ISR, specified by the vect parameter.
    This is compatible with GCC 4.2 and greater only.

    Use this attribute in the attributes parameter of the ISR macro.
*/
#  define ISR_ALIASOF(target_vector)
#else  /* !DOXYGEN */
#  define ISR_BLOCK
#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))
#  define ISR_ALIASOF(v) __attribute__((alias(__STRINGIFY(v))))
#endif /* DOXYGEN */

/* \@} */

#endif
