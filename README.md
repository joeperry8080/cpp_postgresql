This `README.md` is for my CSCI 210 course at Ivy Tech Community College. It covers the environment setup, architectural decisions, and the essential "Smoke Test" instructions to ensure their local environment is ready for database development.
---

# C++ & PostgreSQL Integration Template (CSCI 210)

This repository serves as a foundational template for connecting a C++ application to a PostgreSQL database using the `libpqxx` library. It is designed to demonstrate professional software architecture, including security best practices and the "Single Source of Truth" principle.

## 🚀 Prerequisites

Before cloning this repository, you must install the necessary C++ development tools and the PostgreSQL client libraries for your operating system.

### Fedora/RHEL Linux
```bash
sudo dnf group install development-tools
sudo dnf install libpqxx-devel
```

### Debian-based Linux
```bash
sudo apt install build-essential
sudo apt-get install libpqxx-dev
```

### macOS (Using Homebrew)
```bash
brew install libpqxx
```

### Windows using MSYS2

* Install MSYS2 from https://www.msys2.org/ using defaults.
* When running pacman use defaults (all) as well.

```bash
pacman -S --needed base-devel mingw-w64-x86_64-toolchain	
pacman -S mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-toolchain
pacman -S mingw-w64-ucrt-x86_64-postgresql
pacman -S mingw-w64-ucrt-x86_64-libpqxx
```

### CLion Windows toolchain settings

<img width="1242" height="736" alt="clion_win_settings" src="https://github.com/user-attachments/assets/b5b2c71f-a154-4431-8447-ad09521e0f12" />


## In Windows you can't compile directly in CLion
```bash
g++ main.cpp database.cpp country_count.cpp -o main.exe -lpqxx -lpq
```

## 📂 Project Structure

* **`main.cpp`**: The user interface (Menu System). It handles input/output but contains no SQL.
* **`database.h`**: The header file defining the "contract" for database operations.
* **`database.cpp`**: Centralized configuration and environment variable loading.
* **`country_count.cpp`**: A specialized repository file for handling queries related to the `countries` table.
* **`.env`**: (Hidden) Contains your local database credentials. **Never commit this file.**
* **`.env.example`**: A template for students to copy and fill with their own credentials.

---

## 🛠️ Setup Instructions

### 1. Environment Variables
To keep your credentials secure, this project uses a `.env` file. 
1. Copy the template: `cp .env.example .env`
2. Open `.env` and enter your specific database details (Host, Database Name, Username, and Password).

### 2. Configure Your IDE
Both CLion and VS Code need to know where the `.env` file is located during execution.
* **CLion**: Go to `Run > Edit Configurations` and set the **Working Directory** to the project root folder.
* **VS Code**: In `launch.json`, ensure `"cwd": "${workspaceFolder}"` is set.

---

## 🏗️ Architecture Highlights

### Security: No Hardcoded Passwords
We use a `.gitignore` file to ensure that your `.env` file is never uploaded to GitHub. This prevents your database from being compromised by public exposure of your password.

### Single Source of Truth
The connection string is managed via a centralized function: `getConnectionString()`. 
* **Efficiency**: It uses a `static` variable to load the `.env` file only once per program execution.
* **Maintainability**: If the database server moves or the credentials change, you only update the `.env` file or the logic in `database.cpp`.

### Error Handling
The project uses C++ exceptions (`try-catch` blocks). If a connection fails, the program will catch the error and return a safe value (like `-1`) rather than crashing the entire application.

---

## 🖥️ Building the Project

This project uses **CMake**. To build from the terminal:

```bash
mkdir build
cd build
cmake ..
make
./PostgresConnection
```

---

## 📝 Lab Task
1. Clone this repository.
2. Successfully connect to the `amp.jtperry.net` database.
3. Run Option 1 in the menu to confirm you can return a record count from the `public.countries` table.
4. If you see the count, your environment is correctly configured for the semester!

---
