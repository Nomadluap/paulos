#include <stddef.h>
#include <stdint.h>
 
#include "compile_checks.hpp"
#include "kernel.hpp"
#include "VGA.hpp"
#include "stack.hpp"

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

extern "C" void a_func(int a, int b)
{
    using namespace PaulOS;
    (void)a;
    (void)b;
    /*
    Vga::put("address of a is: ");
    Vga::puthex(reinterpret_cast<uintptr_t>(&a));
    Vga::put("\n");
    */

    Stack::dump_stack();
    //Stack::stacktrace(100);
}


extern "C" void kernel_main(void)
{
    using namespace PaulOS;
    call_global_constructors();
	/* Initialize terminal interface */
    Vga::initialize();
    /*
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

    using namespace Vga;

    auto stack_top = reinterpret_cast<uintptr_t>(Stack::stack_top());
    auto stack_bottom = reinterpret_cast<uintptr_t>(Stack::stack_bottom());
    auto esp = reinterpret_cast<uintptr_t>(Stack::esp());
    put("stack_top=");
    puthex(stack_top);
    put("\nstack_bottom=");
    puthex(stack_bottom);
    put("\nesp=");
    puthex(esp);

    put("\nstack max_size=");
    putdec(stack_top - stack_bottom);
    put(" = ");
    puthex(stack_top-stack_bottom);
    put("\nstack current size=");
    putdec(stack_top-esp);
    put('\n');

    for(size_t i = 0; i < 80; i++)
    {
        Vga::put_at('@', Vga::make_color(Vga::Color::Cyan, Vga::Color::Black), i, 10);
    }

    put("address of kernel_main: ");
    puthex(reinterpret_cast<uintptr_t>(&kernel_main));
    put('\n');
    */

    a_func(0xDEADBEEF, 0xABCD1234);

    //terminal_writestring(foo.str);
}




