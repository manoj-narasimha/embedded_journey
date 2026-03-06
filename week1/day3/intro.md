### A C program's memory is divided into segments:
```
HIGH ADDRESS
┌─────────────────┐
│      STACK      │ ← local variables, function calls, grows DOWNWARD
│        ↓        │
│                 │
│        ↑        │
│      HEAP       │ ← malloc/free, grows UPWARD (avoid in embedded!)
├─────────────────┤
│      BSS        │ ← uninitialized global/static variables (zeroed at startup)
├─────────────────┤
│      DATA       │ ← initialized global/static variables
├─────────────────┤
│      TEXT       │ ← your compiled code (read-only)
└─────────────────┘
LOW ADDRESS
```

### On a real STM32 this maps to:
```
FLASH (read-only, non-volatile):
  └── TEXT  → your compiled firmware code
  └── DATA  → initial values of global variables (copied to RAM at startup)

RAM (read-write, volatile — lost on power off):
  └── DATA  → initialized globals (copied from flash)
  └── BSS   → uninitialized globals (zeroed by startup code)
  └── HEAP  → dynamic memory (avoid on MCUs!)
  └── STACK → local variables + function call frames

```
// These go in DATA segment (initialized globals)
uint32_t system_tick = 0;
uint8_t  device_id   = 0x42;

// These go in BSS segment (zero-initialized)
uint8_t rx_buffer[64];       // automatically zeroed at startup
uint16_t adc_results[128];

// These go on the STACK (local variables)
void some_function(void) {
    uint8_t local_var = 5;   // lives on stack, dies when function returns
    uint8_t local_arr[16];   // 16 bytes eaten from stack!
}
// ⚠️ Stack on STM32 is tiny (few KB). Large local arrays = stack overflow = crash
// Rule: large buffers go as GLOBAL variables (BSS), not local (stack)

// HEAP — dynamic allocation
uint8_t *buf = malloc(64);   // ❌ Avoid in embedded firmware!
                             // fragmentation, non-deterministic, dangerous

```

```
// The compiler adds padding to align members to their natural size
typedef struct {
    uint8_t  a;      // 1 byte
    // 3 bytes padding added here! (to align next member to 4-byte boundary)
    uint32_t b;      // 4 bytes
    uint8_t  c;      // 1 byte
    // 3 bytes padding added here!
} BadLayout_t;       // Total: 12 bytes (not 6!)

// Better layout — largest members first
typedef struct {
    uint32_t b;      // 4 bytes
    uint8_t  a;      // 1 byte
    uint8_t  c;      // 1 byte
    // 2 bytes padding
} GoodLayout_t;      // Total: 8 bytes

// For hardware register maps — force no padding
typedef struct __attribute__((packed)) {
    uint8_t  status;
    uint32_t data;
} PacketHeader_t;    // Exactly 5 bytes, no padding

```

