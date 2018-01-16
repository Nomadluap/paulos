/* x86 crtn.s */
.section .init_after
    /* gcc will put crtend.o's .init here. */
    popl %ebp
    ret

.section .fini_after
/* gcc will put crtend.o's .fini here */
    popl %ebp
    ret
