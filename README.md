# Simple HTTP Server in C (CS50 Final Project - In Progress)

This is a lightweight HTTP web server built from scratch in C. 
</br>
I am currently developing this project as my final assignment for [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/).

## Current Status: Phase 1.1 (Refactored Routing)
The core architecture has been refactored to separate the routing logic from the file transmission, ensuring cleaner code and better resource management.

### Features in this version:
* **Socket Programming**: Manually handling `socket`, `bind`, `listen`, and `accept` using the `<sys/socket.h>` library.
* **Request Parsing**: Basic extraction of the requested URL path from the HTTP header using `sscanf`.
* **Centralized Routing**: A dedicated `handle_request` function acts as a router, decoupling the decision-making logic from the low-level I/O operations.
* **Binary File Reading**: Files are read in binary mode (`rb`) to ensure data integrity, allowing for potential future support of images and other non-text assets.
* **Safety Error Handling**: A "Safety Net" mechanism ensures the server sends a valid HTML response even if the physical `404.html` file is missing or corrupted.
</br>
</br>
---
*Note: This is an educational project and is not intended for production use. I am currently working on implementing a dynamic Document Root.*