# 🔐 File Encryptor – Written in C

A lightweight and fast file encryption/decryption tool written in pure C.  
Encrypts any file type (text, image, binary) using XOR logic with password-based keying.

---

## 📁 Project Structure

| File               | Description                                |
|--------------------|--------------------------------------------|
| `encryptor.c`      | Basic version: simple XOR encryption using raw password |
| `encryptor_v2.c`   | Enhanced version with hashing, file signature, multi-file support |

---

## 🚀 Version 2.0 – What’s New?

✔️ **SHA-256 hashing** of the password for stronger encryption  
✔️ **Magic header** to verify that the file was encrypted with this tool  
✔️ **Support for multiple files** in a single command  
✔️ **Improved error handling** with meaningful messages  
✔️ Clean and modular code

---

## 🔧 Compile

Make sure to link with OpenSSL for SHA-256:
```bash
gcc encryptor_v2.c -o encryptor -lssl -lcrypto
```

---

## 🧪 Usage

### Encrypt:
```bash
./encryptor encrypt file1.txt file2.jpg mypassword
```

### Decrypt:
```bash
./encryptor decrypt file1.txt.enc file2.jpg.enc mypassword
```

Each file will be saved with `.enc` or `.dec` accordingly.

---

## 🧠 Author

Or Yesayas  
Computer Science Student @ HIT  
LinkedIn: [or yesayas](https://www.linkedin.com/in/or-yesayas)

---

## 📸 Project Mascot

![fox programmer](A_vibrant_digital_illustration_features_an_anthrop.png)

---

## ⭐️ Want to Help?

Feel free to open issues, suggest improvements, or just give a ⭐ if you liked it.
