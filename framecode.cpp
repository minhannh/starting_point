#include "framecode.h"

void Process() {
    while (!__isExiting) {
        DisplayMenu();
        ProcessUserChoice();
    }
}