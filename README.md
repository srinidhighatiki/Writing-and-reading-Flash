Auditing Firmware

This repository provides a simple and reliable auditing mechanism for
configuration data stored in the STM32 flash memory. The auditing module
reads raw binary data from flash, computes its SHA256 hash, and returns
the digest, which can be used for blockchain-based integrity
verification.

Note: X-CUBE-CRYPTOLIB version 4.2.0 is included in the STM32 Project folder which can be found at
https://www.st.com/en/embedded-software/x-cube-cryptolib.html


Overview

When the auditing API is provided with: - A flash memory start address -
The size of the data to read - A buffer to store the extracted bytes

It reads the raw binary data from flash and hashes it using the SHA256
algorithm. The resulting 32‑byte (256‑bit) hash digest can be shared
with a blockchain or verification server. Any mismatch between stored
and computed digests indicates tampering or corruption.

------------------------------------------------------------------------

audit.c — Auditing APIs

### audit_compute_hash(uint32_t address, uint32_t size, uint8_t *digest_out)

Purpose:
Reads raw data from flash and computes its SHA256 hash.

Arguments:
- address: Starting flash address to read.
- size: Number of bytes to read from flash.
- digest_out: Pointer to a 32‑byte buffer where the computed SHA256
digest will be written.

Functionality:
- Calls flash read APIs from flash.c
- Feeds read data into SHA256 algorithm
- Produces a 32‑byte digest representing the flash content

What it accomplishes:
Provides an integrity‑proof hash of the flash data for comparison or
external verification.

------------------------------------------------------------------------

flash.c — Flash Access APIs

flash_read_bytes(uint32_t address, uint8_t *buffer, uint32_t size)

Purpose:
Reads a block of bytes from flash memory.

Arguments:
- address: Start address in flash.
- buffer: Buffer to store the read data.
- size: Number of bytes to read.

Functionality:
- Performs safe raw-byte extraction from STM32 flash memory
- Used internally by audit_compute_hash()

How audit.c uses it:
The auditing module relies on flash_read_bytes() to obtain exact
byte‑level data from flash before hashing.

------------------------------------------------------------------------

Summary

This firmware provides: - A clean API for flash data extraction
- SHA256 hashing for data integrity verification
- A modular structure where audit.c uses low‑level flash utilities in
flash.c

The final digest can be shared with a blockchain or remote validator to
ensure the configuration data stored in flash has not been modified.
