// this needs to be here for virtual functions to work.
extern "C" void __cxa_pure_virtual()
{
    // Do nothing or print an error message.
}

//for support of global construction
// void *__dso_handle;
namespace __cxxabiv1
{

	//static local variables.
    //don't do anything het.
    //when we exit, we just halt, so don't bother running destructors.
    extern "C" int __cxa_atexit(void (*destructor) (void *), void *arg, void *dso)
    {
        (void) destructor;
        (void) arg;
        (void) dso;
        return 0;
    }

    extern "C" void __cxa_finalize(void *f)
    {
        (void) f;
    }

	/* guard variables */

	/* The ABI requires a 64-bit type.  */
	__extension__ typedef int __guard __attribute__((mode(__DI__)));

	extern "C" int __cxa_guard_acquire (__guard *);
	extern "C" void __cxa_guard_release (__guard *);
	extern "C" void __cxa_guard_abort (__guard *);

	extern "C" int __cxa_guard_acquire (__guard *g)
	{
		return !*(char *)(g);
	}

	extern "C" void __cxa_guard_release (__guard *g)
	{
		*(char *)g = 1;
	}

	extern "C" void __cxa_guard_abort (__guard *)
	{

	}
}