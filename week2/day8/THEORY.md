# 📅 Day 8 — Week 2, Day 1: Pointer Basics + Memory Diagrams

Today is a **learning day** (Mon = theory + code). Pointers are the single most important concept in C. Everything in embedded — driver APIs, register access, buffers, callbacks — runs on pointers. Let's build the mental model from absolute zero.

---

## 🧠 PART 1 — What is a Pointer? (20 mins)

### The core idea

Every variable in your program lives somewhere in RAM. That location has an **address** — like a house number on a street.

```c
uint8_t temperature = 25;
```

In memory this looks like:

```
RAM:
Address   Value
──────────────────
0x20000000  [ 25 ]   ← temperature lives here
0x20000001  [ ?? ]
0x20000002  [ ?? ]
0x20000003  [ ?? ]
```

A **pointer** is a variable that stores one of those addresses:

```c
uint8_t  temperature = 25;      // regular variable — stores a VALUE
uint8_t *ptr = &temperature;    // pointer variable — stores an ADDRESS
                                // & means "give me the address of"
```

Now memory looks like:

```
RAM:
Address      Value
────────────────────────────────────
0x20000000  [  25  ]  ← temperature
0x20000004  [0x20000000] ← ptr (stores the address of temperature)
```

Three operators — memorize these:

```c
uint8_t  x   = 42;
uint8_t *ptr = &x;      // & = "address of"   → ptr = 0x20000000
uint8_t  val = *ptr;    // * = "dereference"   → val = 42 (go to address, read value)
*ptr = 99;              // * on left = "write through pointer" → x is now 99
```

---

### Why pointers exist — the real reason

```c
// WITHOUT pointers — this doesn't work
void set_value(uint8_t x) {
    x = 99;    // only changes LOCAL copy — original unchanged
}

// WITH pointers — this works
void set_value(uint8_t *x) {
    *x = 99;   // changes the ORIGINAL variable
}

int main(void) {
    uint8_t sensor = 0;

    set_value(sensor);    // sensor still 0 — doesn't work
    set_value(&sensor);   // sensor is now 99 — works ✅
}
```

In embedded firmware, pointers are used for:
- **Driver APIs** — `sensor_read(&data)` fills your struct
- **Buffers** — pass arrays between functions efficiently
- **Hardware registers** — `GPIOA->ODR` is a pointer dereference
- **Callbacks** — function pointers for interrupt handlers
- **Linked lists** — for task queues in RTOS

---

## 🧠 PART 2 — Pointer Types & Sizes (15 mins)

### The type of a pointer tells you what's AT that address

```c
uint8_t  *p8;    // points to a uint8_t  — reading gives 1 byte
uint16_t *p16;   // points to a uint16_t — reading gives 2 bytes
uint32_t *p32;   // points to a uint32_t — reading gives 4 bytes
char     *pch;   // points to a char     — reading gives 1 byte
```

### The pointer itself is always the same size

On a 32-bit system (STM32), every pointer is **4 bytes** regardless of what it points to:

```c
printf("%zu\n", sizeof(uint8_t  *));   // 4 bytes (32-bit address)
printf("%zu\n", sizeof(uint32_t *));   // 4 bytes (same!)
printf("%zu\n", sizeof(void     *));   // 4 bytes (same!)
```

On your PC (64-bit) pointers are 8 bytes. On STM32 (32-bit) they're 4 bytes. This is why embedded code uses fixed-width types everywhere.

---

## 🧠 PART 3 — Pointer Arithmetic (20 mins)

This is where pointers get powerful — and dangerous if misunderstood.

```c
uint8_t arr[4] = {10, 20, 30, 40};
uint8_t *ptr   = arr;    // ptr points to arr[0]
```

Memory layout:
```
Address      Value
────────────────────────────────
0x20000000  [ 10 ]  ← arr[0]  ← ptr
0x20000001  [ 20 ]  ← arr[1]
0x20000002  [ 30 ]  ← arr[2]
0x20000003  [ 40 ]  ← arr[3]
```

When you do `ptr + 1` the compiler doesn't add 1 to the address. It adds **1 × sizeof(type)**:

```c
uint8_t *p8 = arr;
// p8     = 0x20000000
// p8 + 1 = 0x20000001  (+1 byte  — sizeof uint8_t = 1)
// p8 + 2 = 0x20000002  (+2 bytes)

uint32_t arr32[4] = {1, 2, 3, 4};
uint32_t *p32 = arr32;
// p32     = 0x20000000
// p32 + 1 = 0x20000004  (+4 bytes — sizeof uint32_t = 4)
// p32 + 2 = 0x20000008  (+8 bytes)
```

This is **critical** for understanding how STM32 register structs work:

```c
typedef struct {
    volatile uint32_t MODER;    // offset 0x00 → base + 0
    volatile uint32_t OTYPER;   // offset 0x04 → base + 4
    volatile uint32_t OSPEEDR;  // offset 0x08 → base + 8
} GPIO_TypeDef;

// When you write GPIOA->MODER:
// compiler calculates: base_address + offsetof(MODER) = 0x40020000 + 0
// When you write GPIOA->OTYPER:
// compiler calculates: base_address + offsetof(OTYPER) = 0x40020000 + 4
```

---

## 🧠 PART 4 — Pointers and const (10 mins)

Four combinations — all mean different things. You'll see all of these in firmware:

```c
uint8_t x = 10;
uint8_t y = 20;

// 1. Pointer to non-const — can change both pointer and value
uint8_t *ptr = &x;
*ptr = 99;       // ✅ change value
ptr  = &y;       // ✅ change pointer

// 2. Pointer to const — can't change value through pointer
const uint8_t *ptr2 = &x;
*ptr2 = 99;      // ❌ compiler error — value is read-only
ptr2  = &y;      // ✅ can still point elsewhere
// Use for: function params that shouldn't modify data
// e.g. void send(const uint8_t *buf, uint8_t len)

// 3. Const pointer — pointer itself can't change, value can
uint8_t * const ptr3 = &x;
*ptr3 = 99;      // ✅ can change value
ptr3  = &y;      // ❌ compiler error — pointer is fixed
// Use for: fixed hardware register pointer

// 4. Const pointer to const — neither can change
const uint8_t * const ptr4 = &x;
*ptr4 = 99;      // ❌ error
ptr4  = &y;      // ❌ error
// Use for: read-only lookup tables in flash
```

The rule to read these declarations:
> **Read right to left:** `const uint8_t *ptr` = "ptr is a pointer to uint8_t that is const"

---

## 🧠 PART 5 — NULL Pointer (5 mins)

```c
uint8_t *ptr = NULL;   // pointer pointing to address 0 — "nothing"
```

**Always initialize pointers to NULL if not immediately assigned.** And always check before dereferencing:

```c
// ❌ Never do this — undefined behavior, crash on MCU
uint8_t *ptr;      // uninitialized — contains garbage address
*ptr = 42;         // writing to random memory location — system crash

// ✅ Always do this
uint8_t *ptr = NULL;
if (ptr != NULL) {
    *ptr = 42;
}

// ✅ In driver functions — always validate
SensorStatus_t sensor_read(SensorData_t *out) {
    if (out == NULL) return SENSOR_ERROR;   // defensive check
    // ... proceed safely
}
```

On a real STM32, dereferencing a NULL or invalid pointer triggers a **HardFault** — the MCU crashes. This is one of the top causes of firmware bugs.

---

## 💻 Programs to Write Today (6 programs)

Create folder: `C:\embedded_journey\week2\day8\`

---

### Program 1 — `pointer_basics.c`

```c
#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("=== Pointer Basics ===\n\n");

    uint8_t  temperature = 25U;
    uint16_t adc_value   = 4095U;
    uint32_t frequency   = 168000000UL;

    // Declare pointers
    uint8_t  *p_temp = &temperature;
    uint16_t *p_adc  = &adc_value;
    uint32_t *p_freq = &frequency;

    // Print values and addresses
    printf("--- Values ---\n");
    printf("temperature = %u\n",   temperature);
    printf("adc_value   = %u\n",   adc_value);
    printf("frequency   = %lu\n",  (unsigned long)frequency);

    printf("\n--- Addresses (via & operator) ---\n");
    printf("&temperature = %p\n",  (void*)&temperature);
    printf("&adc_value   = %p\n",  (void*)&adc_value);
    printf("&frequency   = %p\n",  (void*)&frequency);

    printf("\n--- Pointer values (addresses they store) ---\n");
    printf("p_temp = %p\n",  (void*)p_temp);
    printf("p_adc  = %p\n",  (void*)p_adc);
    printf("p_freq = %p\n",  (void*)p_freq);

    printf("\n--- Dereferenced values (values AT those addresses) ---\n");
    printf("*p_temp = %u\n",  *p_temp);
    printf("*p_adc  = %u\n",  *p_adc);
    printf("*p_freq = %lu\n", (unsigned long)*p_freq);

    // Modify through pointer
    printf("\n--- Modify through pointer ---\n");
    printf("Before: temperature = %u\n", temperature);
    *p_temp = 99U;
    printf("After *p_temp = 99: temperature = %u\n", temperature);

    // Pointer sizes
    printf("\n--- Pointer sizes ---\n");
    printf("sizeof(uint8_t  *) = %zu bytes\n", sizeof(uint8_t  *));
    printf("sizeof(uint16_t *) = %zu bytes\n", sizeof(uint16_t *));
    printf("sizeof(uint32_t *) = %zu bytes\n", sizeof(uint32_t *));
    printf("sizeof(void     *) = %zu bytes\n", sizeof(void     *));
    printf("(All the same — just an address)\n");

    return 0;
}
```

---

### Program 2 — `pointer_vs_value.c`

*The classic pass-by-value vs pass-by-pointer demo*

```c
#include <stdio.h>
#include <stdint.h>

// ❌ Pass by value — original unchanged
void double_value_wrong(uint32_t x) {
    x = x * 2U;
    printf("  Inside wrong: x = %lu\n", (unsigned long)x);
}

// ✅ Pass by pointer — modifies original
void double_value_correct(uint32_t *x) {
    *x = *x * 2U;
    printf("  Inside correct: *x = %lu\n", (unsigned long)*x);
}

// ✅ Real embedded pattern — read multiple outputs from one function
typedef struct {
    uint16_t voltage_mv;
    uint16_t current_ma;
    uint8_t  fault_flag;
} PowerReading_t;

void read_power_sensor(PowerReading_t *out) {
    if (out == NULL) return;
    // Simulate hardware read
    out->voltage_mv = 3300U;
    out->current_ma = 150U;
    out->fault_flag = 0U;
}

int main(void) {
    printf("=== Pass by Value vs Pointer ===\n\n");

    uint32_t counter = 100UL;

    printf("Before: counter = %lu\n", (unsigned long)counter);
    double_value_wrong(counter);
    printf("After wrong: counter = %lu  (unchanged!)\n\n",
           (unsigned long)counter);

    printf("Before: counter = %lu\n", (unsigned long)counter);
    double_value_correct(&counter);
    printf("After correct: counter = %lu  (changed!)\n\n",
           (unsigned long)counter);

    // Multiple return values via pointer
    printf("--- Multiple return values ---\n");
    PowerReading_t pwr = {0};
    read_power_sensor(&pwr);
    printf("Voltage : %u mV\n", pwr.voltage_mv);
    printf("Current : %u mA\n", pwr.current_ma);
    printf("Fault   : %u\n",    pwr.fault_flag);

    return 0;
}
```

---

### Program 3 — `pointer_arithmetic.c`

```c
#include <stdio.h>
#include <stdint.h>

void print_array_info(const char *label,
                      const uint8_t *arr,
                      uint8_t len) {
    printf("%s:\n", label);
    for (uint8_t i = 0U; i < len; i++) {
        printf("  [%u] addr=%p  val=%u\n",
               i, (void*)(arr + i), arr[i]);
    }
}

int main(void) {
    printf("=== Pointer Arithmetic ===\n\n");

    uint8_t arr8[5]  = {10U, 20U, 30U, 40U, 50U};
    uint32_t arr32[4] = {100UL, 200UL, 300UL, 400UL};

    // uint8_t pointer — steps 1 byte at a time
    printf("--- uint8_t array (1-byte steps) ---\n");
    uint8_t *p8 = arr8;
    for (uint8_t i = 0U; i < 5U; i++) {
        printf("  p8+%u = %p  value = %u\n",
               i, (void*)(p8 + i), *(p8 + i));
    }

    // uint32_t pointer — steps 4 bytes at a time
    printf("\n--- uint32_t array (4-byte steps) ---\n");
    uint32_t *p32 = arr32;
    for (uint8_t i = 0U; i < 4U; i++) {
        printf("  p32+%u = %p  value = %lu\n",
               i, (void*)(p32 + i),
               (unsigned long)*(p32 + i));
    }

    // Array name IS a pointer
    printf("\n--- Array name = pointer to first element ---\n");
    printf("arr8      = %p\n", (void*)arr8);
    printf("&arr8[0]  = %p\n", (void*)&arr8[0]);
    printf("Same? %s\n",
           arr8 == &arr8[0] ? "YES ✅" : "NO");

    // Two ways to access elements — identical
    printf("\n--- arr[i] vs *(arr+i) — identical ---\n");
    for (uint8_t i = 0U; i < 5U; i++) {
        printf("  arr8[%u]=%u  *(arr8+%u)=%u  %s\n",
               i, arr8[i],
               i, *(arr8 + i),
               arr8[i] == *(arr8+i) ? "✅" : "❌");
    }

    // Pointer difference
    printf("\n--- Pointer difference ---\n");
    uint8_t *start = &arr8[0];
    uint8_t *end   = &arr8[4];
    printf("end - start = %td elements\n", end - start);

    // Traversal with pointer increment
    printf("\n--- Traversal with ptr++ ---\n");
    uint8_t *ptr = arr8;
    uint8_t *arr_end = arr8 + 5U;
    while (ptr < arr_end) {
        printf("  *ptr = %u  (addr %p)\n",
               *ptr, (void*)ptr);
        ptr++;
    }

    return 0;
}
```

---

### Program 4 — `const_pointer_demo.c`

```c
#include <stdio.h>
#include <stdint.h>

// ── Firmware-realistic examples of all 4 const pointer types ──

// Type 2: pointer to const — safe read-only buffer parameter
void uart_transmit(const uint8_t *buf, uint8_t len) {
    printf("[UART TX] %u bytes: ", len);
    for (uint8_t i = 0U; i < len; i++) {
        printf("0x%02X ", buf[i]);
    }
    printf("\n");
    // *buf = 0;  // ← compiler would catch this ✅
}

// Type 2: read-only string parameter
void log_message(const char *msg) {
    printf("[LOG] %s\n", msg);
}

// Type 3: const pointer to hardware register (fixed address)
// (simulated — on STM32 this would be: uint32_t * const ODR = (uint32_t*)0x40020014)
static uint32_t sim_ODR_reg = 0U;
uint32_t * const ODR = &sim_ODR_reg;

int main(void) {
    printf("=== const Pointer Variants ===\n\n");

    uint8_t  val_a = 10U;
    uint8_t  val_b = 20U;

    // ── Type 1: uint8_t *ptr — fully mutable
    printf("--- Type 1: fully mutable pointer ---\n");
    uint8_t *ptr1 = &val_a;
    printf("*ptr1 = %u (val_a)\n", *ptr1);
    *ptr1 = 55U;
    printf("After *ptr1=55: val_a = %u\n", val_a);
    ptr1 = &val_b;
    printf("After ptr1=&val_b: *ptr1 = %u\n", *ptr1);

    // ── Type 2: const uint8_t *ptr — can't change value
    printf("\n--- Type 2: pointer to const (read-only data) ---\n");
    const uint8_t *ptr2 = &val_a;
    printf("*ptr2 = %u\n", *ptr2);
    ptr2 = &val_b;
    printf("After ptr2=&val_b: *ptr2 = %u\n", *ptr2);
    // *ptr2 = 99;  // ← uncommenting this causes compile error

    // ── Type 2 in use — UART transmit
    printf("\n--- Type 2 in use: uart_transmit ---\n");
    uint8_t packet[] = {0xAAU, 0xBBU, 0xCCU, 0xDDU};
    uart_transmit(packet, sizeof(packet));
    log_message("System initialized");

    // ── Type 3: uint8_t * const ptr — fixed pointer
    printf("\n--- Type 3: const pointer (fixed address) ---\n");
    uint8_t * const ptr3 = &val_a;
    printf("*ptr3 = %u\n", *ptr3);
    *ptr3 = 77U;
    printf("After *ptr3=77: val_a = %u\n", val_a);
    // ptr3 = &val_b;  // ← uncommenting causes compile error

    // ── Type 3 in use — hardware register simulation
    printf("\n--- Type 3 in use: fixed ODR register pointer ---\n");
    printf("ODR before: 0x%08lX\n", (unsigned long)*ODR);
    *ODR |= (1UL << 5U);    // set pin 5
    printf("ODR after set pin5: 0x%08lX\n", (unsigned long)*ODR);
    *ODR &= ~(1UL << 5U);   // clear pin 5
    printf("ODR after clear pin5: 0x%08lX\n", (unsigned long)*ODR);
    // ODR = NULL;  // ← uncommenting causes compile error

    // ── Type 4: const uint8_t * const — fully immutable
    printf("\n--- Type 4: fully immutable (flash lookup table) ---\n");
    static const uint8_t lut[8] = {0U,36U,71U,100U,128U,150U,178U,200U};
    const uint8_t * const lut_ptr = lut;
    printf("Sine LUT: ");
    for (uint8_t i = 0U; i < 8U; i++) {
        printf("%u ", lut_ptr[i]);
    }
    printf("\n");

    return 0;
}
```

---

### Program 5 — `null_pointer_safety.c`

```c
#include <stdio.h>
#include <stdint.h>

// ── Simulated driver with proper NULL checking ─────────────────
typedef struct {
    uint16_t raw;
    uint16_t voltage_mv;
    uint8_t  valid;
} AdcResult_t;

typedef enum {
    ADC_OK      = 0,
    ADC_ERROR   = 1,
    ADC_NULL    = 2
} AdcStatus_t;

// Simulate ADC hardware read
static AdcStatus_t adc_read(AdcResult_t *out) {
    // Always check NULL first
    if (out == NULL) {
        printf("[ADC] ERROR: NULL pointer passed!\n");
        return ADC_NULL;
    }

    // Simulate hardware read
    out->raw        = 2048U;
    out->voltage_mv = (uint16_t)((uint32_t)out->raw * 3300U / 4095U);
    out->valid      = 1U;

    return ADC_OK;
}

// Return pointer from function — common pattern
static uint8_t s_tx_buffer[64] = {0};

uint8_t *get_tx_buffer(void) {
    return s_tx_buffer;    // return pointer to static buffer
}

uint8_t *get_null_buffer(void) {
    return NULL;           // simulate failure
}

int main(void) {
    printf("=== NULL Pointer Safety ===\n\n");

    // ── Case 1: Safe usage
    printf("--- Case 1: Correct usage ---\n");
    AdcResult_t result = {0};
    AdcStatus_t status = adc_read(&result);
    if (status == ADC_OK) {
        printf("ADC: raw=%u  voltage=%u mV\n",
               result.raw, result.voltage_mv);
    }

    // ── Case 2: NULL passed — driver handles it gracefully
    printf("\n--- Case 2: NULL passed to driver ---\n");
    status = adc_read(NULL);
    printf("Status: %s\n",
           status == ADC_NULL ? "ADC_NULL (handled safely)" : "other");

    // ── Case 3: Pointer returned from function
    printf("\n--- Case 3: Pointer from function ---\n");
    uint8_t *buf = get_tx_buffer();
    if (buf != NULL) {
        buf[0] = 0xAAU;
        buf[1] = 0xBBU;
        printf("buf[0]=0x%02X  buf[1]=0x%02X\n", buf[0], buf[1]);
    }

    // ── Case 4: NULL returned from function — safe handling
    printf("\n--- Case 4: NULL returned — safe handling ---\n");
    uint8_t *bad_buf = get_null_buffer();
    if (bad_buf == NULL) {
        printf("Buffer unavailable — skipping operation safely\n");
    } else {
        bad_buf[0] = 0xFF;   // only reached if not NULL
    }

    // ── Case 5: Pointer to struct member
    printf("\n--- Case 5: Pointer to struct member ---\n");
    AdcResult_t readings[3] = {{1000U, 0U, 0U},
                                {2000U, 0U, 0U},
                                {3000U, 0U, 0U}};

    for (uint8_t i = 0U; i < 3U; i++) {
        uint16_t *raw_ptr = &readings[i].raw;
        readings[i].voltage_mv =
            (uint16_t)((uint32_t)(*raw_ptr) * 3300U / 4095U);
        printf("Reading[%u]: raw=%u  voltage=%u mV\n",
               i, readings[i].raw, readings[i].voltage_mv);
    }

    return 0;
}
```

---

### Program 6 — `memory_diagram.c`

*Print actual memory addresses to see how the stack and data are laid out*

```c
#include <stdio.h>
#include <stdint.h>

// Global variables — DATA/BSS segment (low addresses on most systems)
uint32_t g_system_tick = 0UL;
uint8_t  g_device_id   = 0x42U;
uint8_t  g_rx_buffer[16];         // BSS — zeroed

// Simulated hardware register addresses (like STM32)
#define SIM_GPIOA_BASE  (0x40020000U)
#define SIM_GPIOA_ODR   (SIM_GPIOA_BASE + 0x14U)

void print_memory_map(void) {
    printf("=== Memory Address Map ===\n\n");

    printf("--- Global/Static (DATA/BSS) ---\n");
    printf("g_system_tick @ %p  size=%zu\n",
           (void*)&g_system_tick, sizeof(g_system_tick));
    printf("g_device_id   @ %p  size=%zu\n",
           (void*)&g_device_id, sizeof(g_device_id));
    printf("g_rx_buffer   @ %p  size=%zu\n",
           (void*)g_rx_buffer, sizeof(g_rx_buffer));

    // Local variables — STACK (higher addresses, downward growth)
    uint32_t local_a = 1UL;
    uint16_t local_b = 2U;
    uint8_t  local_c = 3U;
    uint8_t  local_arr[8] = {0};

    printf("\n--- Local (STACK) ---\n");
    printf("local_a   @ %p  size=%zu\n",
           (void*)&local_a, sizeof(local_a));
    printf("local_b   @ %p  size=%zu\n",
           (void*)&local_b, sizeof(local_b));
    printf("local_c   @ %p  size=%zu\n",
           (void*)&local_c, sizeof(local_c));
    printf("local_arr @ %p  size=%zu\n",
           (void*)local_arr, sizeof(local_arr));

    // Pointer relationships
    printf("\n--- Pointer Relationships ---\n");
    uint32_t *p_tick = &g_system_tick;
    uint8_t  *p_id   = &g_device_id;
    uint8_t  *p_buf  = g_rx_buffer;

    printf("p_tick = %p  *p_tick = %lu\n",
           (void*)p_tick, (unsigned long)*p_tick);
    printf("p_id   = %p  *p_id   = 0x%02X\n",
           (void*)p_id, *p_id);
    printf("p_buf  = %p  *p_buf  = %u\n",
           (void*)p_buf, *p_buf);

    // Adjacent array elements
    printf("\n--- Array memory is contiguous ---\n");
    uint8_t arr[5] = {1U, 2U, 3U, 4U, 5U};
    for (uint8_t i = 0U; i < 5U; i++) {
        printf("arr[%u] @ %p = %u  (diff from [0]: %td)\n",
               i, (void*)&arr[i], arr[i],
               &arr[i] - &arr[0]);
    }

    // Simulated hardware register pointer (what STM32 does)
    printf("\n--- Hardware Register Pointer (simulated) ---\n");
    printf("GPIOA base address : 0x%08X\n", SIM_GPIOA_BASE);
    printf("GPIOA ODR  address : 0x%08X\n", SIM_GPIOA_ODR);
    printf("Offset of ODR      : 0x%02X (%u bytes)\n",
           SIM_GPIOA_ODR - SIM_GPIOA_BASE,
           SIM_GPIOA_ODR - SIM_GPIOA_BASE);
}

int main(void) {
    print_memory_map();
    return 0;
}
```

---

## 🔨 Build and Run

```bash
mkdir C:\embedded_journey\week2\day8
cd C:\embedded_journey\week2\day8
# create all 6 files above, then:
gcc -std=c11 -Wall -Wextra program1.c -o p1.exe && ./p1.exe
gcc -std=c11 -Wall -Wextra program2.c -o p2.exe && ./p2.exe
gcc -std=c11 -Wall -Wextra program3.c -o p3.exe && ./p3.exe
gcc -std=c11 -Wall -Wextra program4.c -o p4.exe && ./p4.exe
gcc -std=c11 -Wall -Wextra program5.c -o p5.exe && ./p5.exe
gcc -std=c11 -Wall -Wextra program6.c -o p6.exe && ./p6.exe
```

---

## 🎯 Day 8 Checklist

```
☐ All 6 programs compiled with zero warnings
☐ Program 1: You see pointer address = variable address (they match)
☐ Program 2: You see pass-by-value leaves original unchanged
☐ Program 3: You see uint8_t* steps 1 byte, uint32_t* steps 4 bytes
☐ Program 4: All 4 const pointer types make sense
☐ Program 5: You understand NULL checking pattern
☐ Program 6: You can see DATA/BSS addresses are lower than STACK
☐ You can draw a memory diagram on paper for any pointer scenario
```

---

## 🔑 Key Rules — Pointers in Embedded

| Rule | Why |
|---|---|
| Always initialize to NULL | Prevents accidental dereference of garbage address |
| Always NULL-check before dereference | HardFault on MCU if you don't |
| Use `const T*` for read-only params | Documents intent + compiler enforces it |
| Never return pointer to local variable | Local dies when function returns — dangling pointer |
| Pass structs by pointer not by value | Avoids copying large data onto the tiny MCU stack |
| Use `(void*)` when printing with `%p` | Correct way to print any pointer type |

---

## 🔥 Mental Model to Carry Forward

```
Variable:   [  42  ]  at address 0x2000
             value        address

Pointer:    [ 0x2000 ]  at address 0x2004
              value          address
              (which is an address of something else)

Dereference:  *ptr  →  go to 0x2000  →  read 42
```

**Every STM32 register access you'll ever write is just this pattern** — a pointer containing a hardware address, dereferenced to read or write a register value. That's all it is.

---

Come back with results or questions. **Day 9 tomorrow — Pointer + Arrays deep dive, traverse everything with pointers only, write your own `my_strlen` and `my_memcpy`!** 💪