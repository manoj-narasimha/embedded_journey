# Embedded Number Systems & Bit Toolkit

A professional CLI tool for embedded developers — converts number systems,
inspects hardware registers, builds bitmasks, and decodes STM32 peripherals.

## Features
- Decimal / Hex / Binary / Octal conversion (8, 16, 32-bit)
- Hardware register inspector with bit-by-bit breakdown
- Register diff tool — shows exactly which bits changed and why
- STM32 GPIO MODER decoder
- STM32 UART status register decoder
- ADC raw value → voltage converter
- Sensor data pack/unpack into single uint32_t
- Bit range overflow validator

## Build
\`\`\`bash
make
./bit_toolkit.exe
\`\`\`

## Skills Demonstrated
C99 | Bit Manipulation | Multi-file Architecture |
Makefile | Structs | Enums | Modular Design
```

---

## 🎯 Day 6 Checklist
```
☐ All files created and project builds with zero warnings
☐ All 10 demo sections run correctly
☐ Register inspector shows correct bit breakdown
☐ GPIO MODER decoder shows correct pin modes
☐ Sensor pack/unpack verifies correctly (all three ✅)
☐ Project pushed to GitHub with proper commit message
☐ README written on GitHub