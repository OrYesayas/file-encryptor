# 🔐 File Encryptor – Written in C

A lightweight and fast file encryption/decryption tool written in pure C.  
Encrypts any file type (text, image, binary) using XOR logic with a password-based key.

---

## 📁 Project Structure

| File                        | Description                                                  |
|-----------------------------|--------------------------------------------------------------|
| `encryptor.c`               | Basic version: simple XOR encryption using raw password      |
| `encryptor_v2_no_openssl.c` | Enhanced version with key stretching, file signature, multi-file support |

---

## 🚀 Version 2.0 – What’s New?

✔️ Internal 32-byte key stretching based on the password  
✔️ Magic header to verify that the file was encrypted with this tool  
✔️ Support for multiple files in a single command  
✔️ Improved error handling with meaningful messages  
✔️ Clean and modular code – no external dependencies

---

## 🔧 Compile

No external libraries needed:
```bash
gcc encryptor_v2_no_openssl.c -o encryptor
.
