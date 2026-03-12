# 🗓️ 6-Month Day-by-Day Embedded/Firmware/IoT Master Plan

**Pace:** 1–2 hrs/day | **Goal:** Job-ready in 6 months | **Style:** Learn → Practice → Build

---

## 📌 GROUND RULES
- **Mon/Wed/Fri** = Learn (theory + code reading)
- **Tue/Thu** = Hands-on coding practice
- **Sat** = Project build / GitHub push
- **Sun** = Review + document + plan next week
- Every **Saturday** contributes to the weekly mini project
- Every **month-end** = Major resume-worthy project

---

# 🟥 MONTH 1 — C Programming Mastery + Toolchain Setup

> **Monthly Major Project:** *Bare-metal Register Emulator in C* — A software simulation of a microcontroller's GPIO/UART register map using structs, bitfields, and function pointers. Full CLI interface. Hosted on GitHub with full documentation.

---

### WEEK 1 — Environment Setup + C Foundations

| Day | Focus | Task |
|---|---|---|
| Mon | Setup | Install VS Code, GCC (MinGW/Linux), Git. Write first "Hello World" in C. Understand compilation pipeline: `.c → preprocessor → compiler → linker → binary` |
| Tue | Data Types & Operators | Practice: write programs using all integer types. Understand `sizeof()`. Explore signed/unsigned behavior |
| Wed | Control Flow | Study if/else, switch, loops. Read: K.N. King Ch. 1–5 |
| Thu | Functions | Write 10 small functions (factorial, Fibonacci, palindrome check). Understand stack frames conceptually |
| Fri | Arrays & Strings | Study arrays, `char[]` strings, `strlen`, `strcpy`. No `std::string` — pure C |
| Sat | **Mini Project** | Build a **Number Systems Converter CLI** — input decimal, output binary/hex/octal using bit operations. Push to GitHub |
| Sun | Review | Re-read your code, add comments, document the GitHub README |

---

### WEEK 2 — Pointers (The Heart of C)

| Day | Focus | Task |
|---|---|---|
| Mon | Pointer Basics | Understand `*`, `&`, pointer declaration, dereferencing. Draw memory diagrams on paper |
| Tue | Pointer Arithmetic | Practice: traverse arrays using pointers only (no index). Write `my_strlen`, `my_strcpy` |
| Wed | Pointers to Pointers | Study `**ptr`. Understand argv/argc. Read K.N. King Ch. 11–12 |
| Thu | Pointers & Functions | Pass by reference using pointers. Write a `swap()` function. Write `array_reverse()` |
| Fri | Function Pointers | Study function pointer syntax. Build a simple dispatch table (array of function pointers) |
| Sat | **Mini Project** | Build a **Custom String Library** — implement `my_strlen`, `my_strcmp`, `my_strcat`, `my_memcpy` using only pointers. Zero standard library. GitHub push |
| Sun | Review | Test edge cases (NULL, empty string). Document every function with Doxygen-style comments |

---

### WEEK 3 — Memory, Structs & Bit Manipulation

| Day | Focus | Task |
|---|---|---|
| Mon | Memory Layout | Study stack vs heap vs BSS vs data segment. Draw a C program's memory map |
| Tue | Dynamic Memory | Practice `malloc`, `calloc`, `realloc`, `free`. Write a dynamic array implementation |
| Wed | Structs & Unions | Study structs, nested structs, unions. Understand memory alignment and padding |
| Thu | Bitfields | Use bitfields to model a hardware register. Practice `volatile` keyword use |
| Fri | Bit Manipulation | Master: set bit, clear bit, toggle bit, check bit using `|=`, `&=`, `^=`, `~`, `<<`, `>>`. Do 20 exercises |
| Sat | **Mini Project** | Build a **GPIO Register Simulator** — use structs + bitfields + bit manipulation to simulate an 8-pin GPIO port with direction, output, and input registers. CLI to set/clear/read pins |
| Sun | Review | Add error handling. Document thoroughly |

---

### WEEK 4 — Advanced C + Makefile + Major Project

| Day | Focus | Task |
|---|---|---|
| Mon | `const`, `static`, `volatile`, `extern` | Study each keyword with embedded context. Understand `volatile` for ISR variables |
| Tue | Preprocessor & Macros | Study `#define`, `#ifdef`, `#pragma`, header guards, inline functions vs macros |
| Wed | Makefile Basics | Write a Makefile from scratch. Understand targets, dependencies, variables, `$(CC)`, `$(CFLAGS)` |
| Thu | Multi-file C Projects | Split code into `.h` and `.c` files. Understand extern declarations. Build with Makefile |
| Fri | Linking & Compilation Deep Dive | Study `.o` files, static vs dynamic libraries, `ar`, `nm` commands |
| Sat | **Major Project START** | Begin *Bare-metal Register Emulator* — design the architecture, write structs for GPIO + UART registers |
| Sun | **Major Project FINISH** | Complete CLI, test all functions, write full README with architecture diagram. Push to GitHub with tags `v1.0` |

---

# 🟧 MONTH 2 — STM32 Bare-Metal Microcontroller Programming

> **Monthly Major Project:** *STM32 Bare-Metal Multi-Peripheral Driver Library* — Custom drivers for GPIO, UART, I2C, SPI written at register level (no HAL). Documented API, Makefile build system, tested with real hardware.

**Hardware needed:** STM32 Nucleo-F446RE (~€15) + USB cable + jumper wires + breadboard

---

### WEEK 5 — STM32 Setup + GPIO Bare-Metal

| Day | Focus | Task |
|---|---|---|
| Mon | STM32 Ecosystem | Install STM32CubeIDE. Understand Nucleo board layout. Study STM32F4 block diagram |
| Tue | Reference Manual | Learn to READ the datasheet. Find GPIO registers: MODER, ODR, IDR, BSRR |
| Wed | Clock System | Understand RCC (Reset & Clock Control). Enable GPIO clock via RCC registers manually |
| Thu | GPIO Register Programming | Write bare-metal LED blink — no HAL, only register addresses with `#define` |
| Fri | GPIO Input + Interrupt | Read button state via IDR register. Configure EXTI interrupt at register level |
| Sat | **Mini Project** | **Bare-Metal GPIO Controller** — Button-controlled LED patterns (blink, fade via software PWM). 100% register-level. No HAL/LL. Schematic + code on GitHub |
| Sun | Review | Study your code. Try to reduce it. Understand every register write |

---

### WEEK 6 — UART + SPI + I2C

| Day | Focus | Task |
|---|---|---|
| Mon | UART Theory | Study UART frame format, baud rate calculation, parity, stop bits |
| Tue | UART Register Programming | Configure USART2 at register level. Implement `UART_SendChar()`, `UART_SendString()`, `UART_Receive()` |
| Wed | SPI Theory | Study SPI modes (CPOL, CPHA), master/slave, NSS. Read reference manual SPI section |
| Thu | SPI Register Programming | Implement SPI driver. Connect SPI flash or SPI LCD (or loopback test) |
| Fri | I2C Theory + Practice | Study I2C: START, STOP, ACK, 7-bit addressing. Write I2C driver at register level |
| Sat | **Mini Project** | **I2C Sensor Reader** — Read BME280 (temp/humidity/pressure) via bare-metal I2C driver. Print values over UART to PC terminal |
| Sun | Review | Check I2C timing with logic analyzer or oscilloscope if available |

---

### WEEK 7 — Timers, PWM, ADC, DMA

| Day | Focus | Task |
|---|---|---|
| Mon | Timer Architecture | Study STM32 timer types (basic, general, advanced). Understand PSC and ARR registers |
| Tue | PWM Generation | Configure TIM2 for PWM output at register level. Control LED brightness |
| Wed | ADC | Configure ADC1 in single-conversion mode. Read potentiometer or internal temp sensor |
| Thu | DMA | Understand DMA channels, streams. Use DMA for UART TX — no CPU blocking |
| Fri | Timer Interrupts | Use TIM6 interrupt to trigger periodic tasks. Understand NVIC priority |
| Sat | **Mini Project** | **PWM Servo Controller** — Read ADC (potentiometer), map value to PWM duty cycle, control servo position. All bare-metal |
| Sun | Review | Profile CPU usage (estimate cycles per task). Document timing calculations |

---

### WEEK 8 — Linker Scripts + Startup + Major Project

| Day | Focus | Task |
|---|---|---|
| Mon | Memory Map | Study STM32 flash/RAM layout. Understand `.text`, `.data`, `.bss` sections |
| Tue | Linker Script | Read and modify the default `.ld` file. Understand `MEMORY` and `SECTIONS` blocks |
| Wed | Startup Code | Study `startup_stm32f4xx.s`. Understand reset handler, vector table, `SystemInit` |
| Thu | Custom Bootloader Concept | Study how bootloader jumps to application. Modify linker script to offset app |
| Fri | Code Review Day | Review all Month 2 code. Refactor. Add Doxygen comments to every function |
| Sat | **Major Project START** | Begin *Multi-Peripheral Driver Library* — folder structure, header files, driver skeletons |
| Sun | **Major Project FINISH** | Complete GPIO + UART + I2C + SPI drivers. Example app using all 4. Full README + wiring diagram. GitHub `v1.0` |

---

# 🟨 MONTH 3 — FreeRTOS + Interrupts + Debugging

> **Monthly Major Project:** *RTOS-Based Sensor Hub* — Multi-task FreeRTOS application: Task 1 reads multiple sensors via I2C, Task 2 processes/filters data, Task 3 transmits over UART. Uses queues, semaphores, and software timers. Includes fault handling.

---

### WEEK 9 — FreeRTOS Fundamentals

| Day | Focus | Task |
|---|---|---|
| Mon | RTOS Concepts | Study: why RTOS? Preemption, scheduling, context switch, tick. Read FreeRTOS intro docs |
| Tue | Task Creation | Create 2 tasks on STM32: LED blink task + UART print task. Use `xTaskCreate()` |
| Wed | Task States & Priority | Study: Ready, Running, Blocked, Suspended. Experiment with priorities |
| Thu | Delay & Timing | Use `vTaskDelay()` vs `vTaskDelayUntil()`. Understand why `DelayUntil` is better for periodic tasks |
| Fri | Stack & Heap in FreeRTOS | Study `configMINIMAL_STACK_SIZE`, `heap_4.c`. Debug stack overflow with `uxTaskGetStackHighWaterMark()` |
| Sat | **Mini Project** | **RTOS Traffic Light System** — 3 tasks (Red/Yellow/Green LED), each with different periods, coordinated with FreeRTOS timing. No blocking between tasks |
| Sun | Review | Check stack usage. Verify timing accuracy |

---

### WEEK 10 — Queues, Semaphores, Mutexes

| Day | Focus | Task |
|---|---|---|
| Mon | Queues | Study queue internals. Create a queue to pass sensor data between tasks |
| Tue | Queue Practice | Producer-Consumer: ADC task produces values, UART task consumes and prints |
| Wed | Semaphores | Study binary semaphore vs counting semaphore. Use semaphore to signal from ISR to task |
| Thu | Mutex | Study mutex vs semaphore. Solve a shared UART resource problem using mutex |
| Fri | Priority Inversion | Study the problem. Understand priority inheritance (FreeRTOS mutexes handle this) |
| Sat | **Mini Project** | **ISR-to-Task Communication System** — Button press triggers ISR → posts to queue → task receives and logs event over UART with timestamp |
| Sun | Review | Stress test with multiple rapid button presses. Check for race conditions |

---

### WEEK 11 — Software Timers, Event Groups, Watchdog

| Day | Focus | Task |
|---|---|---|
| Mon | Software Timers | Study one-shot vs auto-reload timers. Use timer to timeout a UART receive operation |
| Tue | Event Groups | Study event bits. Use event group to synchronize 3 tasks at a common checkpoint |
| Wed | Task Notifications | Study as lightweight alternative to semaphore. Refactor week 10 project to use notifications |
| Thu | Watchdog Timer | Configure IWDG (Independent Watchdog) on STM32. Understand how it detects system hang |
| Fri | HardFault Handler | Write a custom HardFault handler that prints stack info over UART before reset |
| Sat | **Mini Project** | **Watchdog-Protected Multi-Task System** — 3 tasks each "check in" via event group. Watchdog resets system if any task hangs. UART logs all events |
| Sun | Review | Intentionally cause a hang. Verify watchdog resets system correctly |

---

### WEEK 12 — Debugging + Profiling + Major Project

| Day | Focus | Task |
|---|---|---|
| Mon | GDB Debugging | Learn GDB with OpenOCD + ST-Link. Set breakpoints, watch variables, inspect stack |
| Tue | SWV / ITM Tracing | Use STM32CubeIDE's SWV trace to profile task CPU usage in real-time |
| Wed | Memory Analysis | Use `valgrind` concepts. Check for heap fragmentation. Analyze `.map` file |
| Thu | Logic Analyzer | Capture I2C/SPI/UART waveforms with logic analyzer. Verify timing |
| Fri | Code Review | Review all Month 3 code. Refactor for clarity and safety |
| Sat | **Major Project START** | Begin *RTOS Sensor Hub* — set up task structure, queues, I2C sensor integration |
| Sun | **Major Project FINISH** | Complete all tasks + error handling + UART dashboard output. Full README + architecture diagram. GitHub `v1.0` |

---

# 🟩 MONTH 4 — Communication Protocols + IoT Stack

> **Monthly Major Project:** *Industrial IoT Gateway* — ESP32-based device collects sensor data over I2C/SPI, sends to AWS IoT Core via MQTT over TLS, supports OTA firmware update, has a Node-RED dashboard. This is a portfolio centrepiece.

---

### WEEK 13 — CAN Bus + UART Advanced + Modbus

| Day | Focus | Task |
|---|---|---|
| Mon | CAN Bus Theory | Study CAN frame structure, arbitration, bit stuffing, error frames. Essential for Germany automotive |
| Tue | STM32 CAN Setup | Configure bxCAN peripheral. Set up loopback mode. Transmit and receive CAN frames |
| Wed | CAN Filter Configuration | Study mask/list filters. Filter specific CAN IDs |
| Thu | Modbus RTU | Study Modbus RTU protocol (used heavily in German industrial automation) |
| Fri | RS-485 + Modbus | Implement a basic Modbus RTU master that reads holding registers |
| Sat | **Mini Project** | **CAN Bus Data Logger** — Two STM32 boards communicate via CAN. One sends sensor data, other logs it over UART. GitHub with timing diagram |
| Sun | Review | Capture CAN frames with logic analyzer. Document frame structure |

---

### WEEK 14 — ESP32 + Wi-Fi + MQTT

| Day | Focus | Task |
|---|---|---|
| Mon | ESP32 & ESP-IDF | Install ESP-IDF toolchain. Build first project. Understand partition table |
| Tue | Wi-Fi Connection | Connect ESP32 to Wi-Fi using ESP-IDF (not Arduino). Handle reconnection events |
| Wed | MQTT Basics | Study MQTT protocol: broker, publish, subscribe, QoS levels, retain, LWT |
| Thu | MQTT on ESP32 | Use `esp-mqtt` component. Connect to HiveMQ public broker. Pub/sub test |
| Fri | AWS IoT Core Setup | Create AWS IoT thing, download certificates, configure policy |
| Sat | **Mini Project** | **MQTT Sensor Publisher** — ESP32 reads DHT22 sensor, publishes JSON payload to AWS IoT Core every 5 seconds. Certificates stored in flash |
| Sun | Review | Monitor messages in AWS IoT console. Check QoS delivery |

---

### WEEK 15 — BLE + LoRa + OTA

| Day | Focus | Task |
|---|---|---|
| Mon | BLE Fundamentals | Study BLE architecture: GAP, GATT, profiles, services, characteristics |
| Tue | ESP32 BLE GATT Server | Create a custom BLE GATT service exposing sensor data. Read from phone using nRF Connect |
| Wed | LoRaWAN Concepts | Study LoRa modulation, LoRaWAN network architecture, OTAA vs ABP join |
| Thu | OTA Firmware Update | Study ESP-IDF OTA: partition table, `esp_https_ota`, rollback mechanism |
| Fri | OTA Implementation | Implement OTA update that pulls new firmware from HTTPS server. Test rollback on failure |
| Sat | **Mini Project** | **BLE + OTA Device** — ESP32 exposes sensor data over BLE. Supports OTA update trigger via BLE command. New firmware downloaded from server |
| Sun | Review | Test OTA failure scenario. Verify rollback works |

---

### WEEK 16 — Security + Dashboard + Major Project

| Day | Focus | Task |
|---|---|---|
| Mon | Embedded Security | Study TLS handshake, certificate pinning, secure boot concept, flash encryption on ESP32 |
| Tue | Secure Boot + Flash Encryption | Enable on ESP32 in development mode. Understand implications |
| Wed | Node-RED Dashboard | Install Node-RED. Connect to AWS IoT via MQTT. Build live sensor dashboard |
| Thu | Grafana + InfluxDB | Set up InfluxDB + Grafana (Docker). Route MQTT data to InfluxDB. Beautiful time-series charts |
| Fri | System Integration | Connect all components: STM32 → UART → ESP32 → AWS → Grafana |
| Sat | **Major Project START** | Begin *Industrial IoT Gateway* — full system design, ESP32 + STM32 integration |
| Sun | **Major Project FINISH** | Complete system. Record a demo video. Write detailed README with architecture, setup instructions, dashboard screenshots. GitHub `v1.0` |

---

# 🟦 MONTH 5 — Embedded Linux + Yocto + Professional Tools

> **Monthly Major Project:** *Custom Embedded Linux Image with Application Daemon* — Yocto-built Linux image for Raspberry Pi running a custom C daemon that reads sensors, logs to SQLite, exposes REST API, and auto-starts via systemd.

---

### WEEK 17 — Embedded Linux Basics

| Day | Focus | Task |
|---|---|---|
| Mon | Linux for Embedded | Study: kernel, bootloader (U-Boot), device tree, rootfs. Understand boot sequence |
| Tue | Raspberry Pi Setup | Install Raspberry Pi OS. Practice Linux CLI: file system, permissions, processes, services |
| Wed | Cross Compilation | Set up cross-compile toolchain on PC. Compile a C program for ARM on x86 host |
| Thu | Device Tree | Study `.dts` file syntax. Enable I2C/SPI/UART via device tree overlay |
| Fri | Kernel Modules | Write a simple "Hello World" loadable kernel module (`.ko`). Insert/remove it |
| Sat | **Mini Project** | **Cross-Compiled Sensor Reader** — C program cross-compiled on PC, runs on Raspberry Pi, reads I2C sensor (BME280), prints to console. Systemd service auto-starts it on boot |
| Sun | Review | Write a proper `systemd` unit file. Test auto-start on reboot |

---

### WEEK 18 — Yocto Project

| Day | Focus | Task |
|---|---|---|
| Mon | Yocto Concepts | Study layers, recipes (`.bb`), bitbake, machine configs, distro configs |
| Tue | First Yocto Build | Build `core-image-minimal` for QEMU (use PC, not RPi — saves time). Takes a few hours |
| Wed | Custom Layer | Create your own Yocto layer `meta-myproject`. Add a simple recipe |
| Thu | Custom Recipe | Write a `.bb` recipe that cross-compiles your C sensor daemon and installs it |
| Fri | SDK Generation | Generate Yocto SDK. Use it to cross-compile applications without full Yocto setup |
| Sat | **Mini Project** | **Custom Yocto Image** — Minimal Yocto image for QEMU/RPi with your sensor app baked in. Boots directly into your application. GitHub with `.bb` recipe |
| Sun | Review | Document every Yocto command. This is rare knowledge — document it well |

---

### WEEK 19 — systemd, IPC, POSIX, Daemons

| Day | Focus | Task |
|---|---|---|
| Mon | POSIX Threads | Study `pthreads`: `pthread_create`, `mutex`, `condition variables`. Compare to FreeRTOS |
| Tue | IPC Mechanisms | Study pipes, FIFOs, message queues, shared memory, Unix sockets |
| Wed | systemd Deep Dive | Write unit files with dependencies, socket activation, watchdog integration |
| Thu | D-Bus | Study D-Bus for inter-process communication on Linux. Write a simple service |
| Fri | Daemon Design Patterns | Study how proper Linux daemons are structured (signal handling, logging, PID files) |
| Sat | **Mini Project** | **Multi-Process Sensor System** — Process 1 reads sensor → writes to message queue → Process 2 reads queue → logs to SQLite → Process 3 exposes REST API (using libmicrohttpd). All as systemd services |
| Sun | Review | Test inter-process failure and recovery |

---

### WEEK 20 — CI/CD, Testing, Code Quality + Major Project

| Day | Focus | Task |
|---|---|---|
| Mon | Unit Testing | Learn Unity test framework for C. Write tests for your driver functions |
| Tue | CMake | Learn CMake: `CMakeLists.txt`, targets, linking, cross-compile toolchain files |
| Wed | Static Analysis | Use `cppcheck` and `clang-tidy` on your codebase. Fix all warnings |
| Thu | GitHub Actions CI | Write a `.github/workflows/ci.yml` that builds and runs unit tests on every push |
| Fri | Code Coverage | Use `gcov` + `lcov` to measure test coverage. Add coverage badge to README |
| Sat | **Major Project START** | Begin *Custom Linux Daemon System* — architecture, Yocto recipe, daemon code |
| Sun | **Major Project FINISH** | Complete system, CI pipeline green, coverage > 70%, full README with architecture diagram and demo. GitHub `v1.0` |

---

# 🟪 MONTH 6 — Portfolio Polish + Interview Prep + Job Applications

> **Monthly Major Project:** *Capstone — Automotive-Grade CAN Bus Data Acquisition System* — STM32-based system that reads multiple CAN nodes, timestamps frames, stores to SD card, streams over UART to Linux PC, with Python analysis tool. Targets automotive/industrial roles specifically.

---

### WEEK 21 — Advanced Topics + German Industry Focus

| Day | Focus | Task |
|---|---|---|
| Mon | AUTOSAR Awareness | Study AUTOSAR layered architecture (just conceptual). Read 2–3 articles. Know the terminology |
| Tue | ISO 26262 Awareness | Study functional safety levels (ASIL A–D). Know what "safety-critical" means in practice |
| Wed | MISRA C | Study MISRA C:2012 rules. Run `cppcheck --addon=misra` on your code |
| Thu | IEC 61508 Awareness | Study industrial safety standard. Compare to ISO 26262 |
| Fri | Bootloader Deep Dive | Implement a basic STM32 bootloader that receives firmware via UART (YMODEM-like) and flashes it |
| Sat | **Mini Project** | **UART Bootloader** — STM32 bootloader that receives new `.bin` file over UART, writes to flash, jumps to application. Fully functional |
| Sun | Review | Test with corrupted firmware. Verify bootloader rejects bad CRC |

---

### WEEK 22 — Capstone Project Build

| Day | Focus | Task |
|---|---|---|
| Mon | Capstone Design | Design full CAN DAQ system architecture. Define CAN IDs, data format, SD card structure |
| Tue | CAN Receive + Timestamping | Implement multi-ID CAN receiver with hardware timestamp using STM32 timer |
| Wed | SD Card + FatFS | Integrate FatFS library. Write CAN frames to `.csv` on SD card |
| Thu | UART Streaming | Stream live CAN data over UART to PC in structured format |
| Fri | Python Analysis Tool | Write Python script: reads UART stream, parses frames, plots signals using matplotlib |
| Sat | **Integration + Testing** | Connect all parts. Test with real CAN traffic. Fix bugs |
| Sun | **Document** | Write full system README, wiring diagram, protocol spec, demo video script |

---

### WEEK 23 — Portfolio Polish + CV + LinkedIn

| Day | Focus | Task |
|---|---|---|
| Mon | GitHub Audit | Review ALL 6 major projects. Consistent READMEs: overview, hardware, setup, demo, architecture diagram |
| Tue | Demo Videos | Record short (2–3 min) demo videos for top 3 projects. Upload to YouTube (unlisted is fine) |
| Wed | CV Writing | Write German-style CV. Tailor for embedded roles. List every tool, protocol, peripheral |
| Thu | LinkedIn Optimization | Update LinkedIn. Add projects, skills, set open-to-work for Germany. Connect with German embedded engineers |
| Fri | Cover Letter Template | Write a template Anschreiben (German cover letter). Customize for Bosch/Siemens/Continental style |
| Sat | **Portfolio Website** (optional but impressive) | One-page GitHub Pages site listing all projects with links and screenshots |
| Sun | Review | Get feedback on CV from LinkedIn connections or communities (r/embedded) |

---

### WEEK 24 — Interview Prep + Apply

| Day | Focus | Task |
|---|---|---|
| Mon | Technical Interview Prep | Study: pointer questions, bit manipulation puzzles, volatile/const, ISR rules, RTOS questions |
| Tue | System Design Questions | Practice: "Design a firmware architecture for a battery management system." Talk through it |
| Wed | Protocol Questions | Be ready to explain: I2C vs SPI vs UART vs CAN. Timing diagrams. Use cases |
| Thu | Behavioral Prep | Prepare answers: project you're proud of, debugging challenge, working with hardware constraints |
| Fri | Mock Interview | Do a mock interview with a friend, ChatGPT, or Pramp.com. Time yourself |
| Sat | **Apply to 10 companies** | StepStone.de, LinkedIn, Indeed.de, Xing.de. Target: Bosch, Continental, Siemens, Infineon, SICK AG, Wago, Beckhoff, Rohde & Schwarz, Endress+Hauser, Dräger |
| Sun | **Reflect + Celebrate** 🎉 | You went from beginner to job-ready in 6 months. Keep applying, keep building |

---

## 🏆 Your Final Portfolio (6 Resume-Worthy Projects)

| # | Project | Skills Demonstrated |
|---|---|---|
| 1 | Bare-metal Register Emulator | C mastery, bitfields, structs, Makefile, Doxygen |
| 2 | STM32 Multi-Peripheral Driver Library | Register-level drivers, GPIO/UART/I2C/SPI, no HAL |
| 3 | RTOS Sensor Hub | FreeRTOS, queues, semaphores, ISR handling, watchdog |
| 4 | Industrial IoT Gateway | ESP32, MQTT/TLS, AWS IoT, OTA, BLE, Grafana dashboard |
| 5 | Custom Embedded Linux Daemon | Yocto, systemd, POSIX, CI/CD, cross-compilation |
| 6 | CAN Bus DAQ System *(Capstone)* | CAN, FatFS, SD card, Python tools, automotive focus |

---

## 🧠 Quick Reference — Tools You'll Master

**Languages:** C (expert), C++ (intermediate), Python (scripting), Bash
**MCUs:** STM32F4, ESP32
**RTOS:** FreeRTOS, Zephyr (awareness)
**Protocols:** UART, SPI, I2C, CAN, MQTT, BLE, LoRaWAN, Modbus RTU, RS-485
**Linux:** Yocto, systemd, pthreads, cross-compilation, kernel modules
**Tools:** GCC, GDB, OpenOCD, CMake, Make, Git, GitHub Actions, cppcheck, Doxygen
**Cloud:** AWS IoT Core, Node-RED, Grafana, InfluxDB

---

Start **tomorrow morning** with Week 1, Day 1. Install GCC and write your first C program. The journey of 6 months begins with a single `gcc hello.c`. 💪