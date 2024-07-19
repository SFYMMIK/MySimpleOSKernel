#include "isr.h"
#include "io.h"
#include "screen.h"

void isr_handler(struct registers *r) {
    print("Interrupt received: ");
    print_hex(r->int_no);
    print("\n");
}
