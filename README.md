# Simple HTTP Server in C (CS50 Final Project)

This is a lightweight HTTP web server built from scratch in C. 
</br>
This project was developed as my final assignment for [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/).

### Architecture: Hybrid Priority Routing
The core of this server is a **two-tier routing system**:

1.  **Tier 1: Static Hash Table** - Handles explicit route mappings (e.g., `/` → `public/index.html`) using a custom Hash Table powered by the **djb2 algorithm**.
    * Allows for "Pretty URLs" and virtual aliases, enabling clean navigation without file extensions.
2.  **Tier 2: Dynamic File Discovery (Fallback)**
    * Automatically serves any file located in the `public/` directory if no explicit route is found in the Hash Table.
    * Enables serving of assets like CSS, JS, and images without manual configuration.

### Technical Features:
* **Path Sanitization**: Built-in protection against "Directory Traversal" attacks by validating and blocking any request containing `..` before any file system access.
* **MIME Type Detection**: Automatic identification of file extensions to ensure correct browser rendering for `text/html`, `text/css`, `image/webp`, `application/javascript`, and more.
* **Modular Design**: Clean separation of concerns across multiple modules (`main`, `http_handler`, `custom_routing`), ensuring maintainability and encapsulation.
* **Binary Data Integrity**: All files are read and transmitted in binary mode (`rb`), preventing corruption of non-text assets like images or compressed files.
* **Automated Build System**: Includes a Makefile to manage compilation, dependencies, and linking.

### Project structure:
* `main.c`: Server lifecycle management (Socket, Bind, Listen, Accept) and the main event loop.
* `custom_routing.c/h`: The routing logic.
* `http_handler.c/h`: HTTP protocol parsing, security filters, MIME detection, and file transmission logic.
* `public/`: The root directory for all static web assets (HTML, CSS, JS, Images).

## Installation & Usage

1. **Compile the project**
    ```bash
    make
    ```
2. **Run the server**
    ```bash
    ./server
    ```
3. **Clean build files**
    ```bash
    make clean
    ```

---
*Note: This is an educational project and is not intended for production use. 
<br>It was built to demonstrate low-level systems programming, networking, and data structure implementation in C.*
