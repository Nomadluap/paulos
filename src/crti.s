/* x85 crti.s */
.section .init_before
.global _init
.global _static_init

.type _init, @function
_init:
_static_init:
    push %ebp
    movl %esp, %ebp

    /* gcc will put crtbegin.o's .init here, but we've already returned.  */
.section .init
    nop

.section .fini_before
.global _fini
.type _fini, @function
_fini:
    push %ebp
    movl %esp, %ebp
    /* gcc will put crtbegin.o's .fini here. */

.section .fini
    nop
