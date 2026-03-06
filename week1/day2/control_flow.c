#include <stdio.h>
#include <stdint.h>

typedef enum
{
    STATE_IDLE,
    STATE_INIT,
    STATE_RUNNING,
    STATE_ERROR,
    STATE_SHUTDOWN
} SystemState;

const char* state_name(SystemState s) {
    switch (s) {
        case STATE_IDLE:     return "IDLE";
        case STATE_INIT:     return "INIT";
        case STATE_RUNNING:  return "RUNNING";
        case STATE_ERROR:    return "ERROR";
        case STATE_SHUTDOWN: return "SHUTDOWN";
        default:             return "UNKNOWN";
    }
}

int main(void) {
    SystemState current = STATE_IDLE;
    uint8_t     error   = 0;

    printf("=== Firmware State Machine ===\n");
    for (uint8_t cycle = 0; cycle < 8; cycle++) {
        printf("Cycle %u -> State: %s\n", cycle, state_name(current));

        switch (current) {
            case STATE_IDLE:
                current = STATE_INIT;
                break;
            case STATE_INIT:
                    current = STATE_RUNNING;
                    break;
            case STATE_RUNNING:
                if (cycle == 5) error = 1;
                current = error ? STATE_ERROR : STATE_RUNNING;
                break;
            case STATE_ERROR:
                current = STATE_SHUTDOWN;
                break;
            case STATE_SHUTDOWN:
                printf("System halted.\n");
                return 0;
            default:
                break;
        }
    }
    return 0;
}