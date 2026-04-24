# 🔐 WiFi Password Viewer (C)

A simple and professional Windows tool written in C that allows you to view saved WiFi networks and their passwords directly from your system.

---

## 📌 Features

* 📶 List all saved WiFi networks
* 🔑 Show password for a selected network
* ⚡ Display all WiFi passwords at once
* 🎨 Clean console UI with colors
* 🪶 Lightweight and fast (no external dependencies)

---

## ⚙️ Requirements

* Windows OS
* GCC compiler (MinGW recommended)

---

## 🚀 Installation & Usage

### 1. Clone the repository

```bash
git clone https://github.com/Haroun677/WifiViewPasswordSaved.git
cd WifiViewPasswordSaved
```

### 2. Compile the program

```bash
gcc wifiView.c -o wifiView
```

### 3. Run the program

```bash
./wifiView
```

---

## 🧠 How It Works

This program uses Windows command-line tools:

* `netsh wlan show profiles` → to list saved WiFi networks
* `netsh wlan show profile name="..." key=clear` → to extract passwords

---

## ⚠️ Important Notes

* This tool only works on **Windows**
* It shows passwords **already saved on your system**
* Administrator privileges may be required

---

## 📷 Preview

```
[01] WiFi Name        [PASSWORD] : ********
[02] Home Network     [PASSWORD] : ********
```
<img width="300" height="200" alt="image" src="https://github.com/user-attachments/assets/9742cca8-8fb6-4ac8-b209-7aef19c034f1" />
<img width="300" height="200" alt="image" src="https://github.com/user-attachments/assets/6956e93e-f9b7-41a5-bdd5-87db384956c5" />



---

## 👨‍💻 Author

Created by **Haroun**

---

## 📄 License

This project is for educational purposes only.
