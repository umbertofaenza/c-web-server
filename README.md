# Simple HTTP Server in C (CS50 Final Project - In Progress)

This is a lightweight HTTP web server built from scratch in C. 
</br>
I am currently developing this project as my final assignment for [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/).

## Current Status: Phase 1 (Basic Routing)
The project is currently in its initial development phase. The goal of this version was to understand the fundamentals of socket programming and the HTTP protocol.

### Features in this version:
* **Socket Programming**: Manually handling `socket`, `bind`, `listen`, and `accept` using the `<sys/socket.h>` library.
* **Request Parsing**: Basic extraction of the requested URL path from the HTTP header using `sscanf`.
* **Manual Routing**: A static routing system that maps specific URL paths (like `/` or `/about`) to local HTML files.
* **Binary File Reading**: Files are read in binary mode (`rb`) to ensure data integrity, allowing for potential future support of images and other non-text assets.
* **Custom Error Handling**: A dedicated 404 handler that serves a custom `404.html` page when a requested file is not found, with a hardcoded fallback mechanism.
</br>
</br>
---
*Note: This is an educational project and is not intended for production use. I am currently working on refactoring the routing system to avoid repetition and support a dynamic Document Root.*