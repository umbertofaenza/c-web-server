# Simple HTTP Server in C (CS50 Final Project - In Progress)

This is a lightweight HTTP web server built from scratch in C. 
</br>
I am currently developing this project as my final assignment for [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/).

## Current Status: Phase 1.3 (Multimedia & MIME Support)
The project now supports a wide range of file types, allowing for full web page rendering with CSS, JavaScript, and images.

### Technical Features:
**MIME Type Detection**: Automatic identification of file extensions using `strrchr` and `strcasecmp`. This ensures the server sends the correct `Content-Type` header (e.g., `text/css`, `image/png`, `application/javascript`), allowing browsers to render assets correctly.
* **Hash Table Routing**: Replaced linear search ($O(n)$) with a custom Hash Table ($O(1)$) using the djb2 algorithm for route lookups.
* **Modular Architecture**: Organized into distinct modules (custom_routing, http_handler, main) with encapsulation using static variables.
**Binary Data Integrity**: All files are read and transmitted in binary mode (`rb`), preventing corruption of non-text assets like images or compressed files.
* **Automated Build System**: Includes a Makefile to manage compilation, dependencies, and linking.

### Project structure:
* **main.c**: Server entry point, socket lifecycle, and route configuration.
* **custom_routing.c/h**: The routing logic (Hash Table implementation and encapsulation).
* **http_handler.c/h**: Logic for processing HTTP requests and serving files.
* **public/**: Directory for static assets.

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
<br>Next steps include transitioning to a Dynamic Document Root to automatically serve any file within the public/ directory and implementing security filters to prevent directory traversal attacks.*