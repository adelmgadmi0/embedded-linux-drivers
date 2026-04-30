# Embedded Linux Drivers

A collection of Linux loadable kernel modules (LKMs) written in C, built and tested on a QEMU virtual machine running Alpine Linux.

## Drivers

| Driver | Description |
|--------|-------------|
| [`led`](./01_led_driver/) | Character device driver that simulates LED control via `/dev/led_driver` |

## Environment

- **OS:** Alpine Linux (QEMU)
- **Kernel:** Linux 6.6.117-0-virt
- **Toolchain:** gcc, make, linux-headers

## Author

[adelmgadmi0](https://github.com/adelmgadmi0)
