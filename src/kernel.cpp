#include <stddef.h>
#include <stdint.h>
 
#include "compile_checks.hpp"
#include "kernel.hpp"
#include "VGA.hpp"

namespace{
    const char* const STATUS_OK = "Static init OK";
    const char* const STATUS_BAD = "Static init not OK";
    const char* status = STATUS_BAD;
    //check for correct static_init of classes.
    struct StaticInitVerifier
    {
        // this constructor should be run before kernel_main enters.
        StaticInitVerifier()
        {
            status = STATUS_OK;
        }
    };
    StaticInitVerifier bar;
}

static void call_global_constructors()
{
    extern void(*__ctors_start)();
    __ctors_start();
}

extern "C" void kernel_main(void)
{
    using namespace PaulOS;
    call_global_constructors();
	/* Initialize terminal interface */
    Vga::initialize();
    char buf[] = "What is this\n";
    static_assert(sizeof(buf) == 14, "buf should be 13");
    Vga::put(buf, sizeof(buf));
    Vga::putline("Hello from the kernel!!!! ");
    Vga::putline(status);
    using Vga::putline;
    putline("one");
    putline("two");
    putline("three");
    putline("four");
    putline("five");
    putline("six");
    putline("seven");
    putline("eight");
    putline("nine");
    putline("ten");
    putline("eleven");
    putline("twelve");
    putline("thirteen");
    putline("fourteen");
    putline("fifteen");
    putline("sixteen");
    putline("seventeen");
    putline("eighteen");
    putline("nineteen");
    putline("twenty");
    putline("twenty-one");
    putline("twenty-two");
    putline("twenty-three");
    putline("twenty-five");
    putline("twenty-six");
    putline("twenty-seven");


    for(size_t i = 0; i < 80; i++)
    {
        Vga::put_at('@', Vga::make_color(Vga::Color::Cyan, Vga::Color::Black), i, 10);
    }


    //terminal_writestring(foo.str);
}




