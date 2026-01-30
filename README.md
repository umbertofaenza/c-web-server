# Simple HTTP Server in C (CS50 Final Project - In Progress)

This is a lightweight HTTP web server built from scratch in C. 
</br>
I am currently developing this project as my final assignment for [CS50: Introduction to Computer Science](https://cs50.harvard.edu/x/).

## Current Status: Phase 1.2 (Optimized Routing & Modular Design)
The project has evolved from simple conditional routing to a Hash Table-based routing system.

### Features in this version:
* **Hash Table Routing**: Replaced linear search ($O(n)$) with a custom Hash Table ($O(1)$) using the djb2 algorithm for route lookups.
* **Modular Architecture**: Organized into distinct modules (custom_routing, http_handler, main) with encapsulation using static variables.
* **Automated Build System**: Includes a Makefile to manage compilation, dependencies, and linking.

### Project structure:
* **main.c**: Server entry point, socket lifecycle, and route configuration.
* **custom_routing.c/h**: The routing logic (Hash Table implementation and encapsulation).
* **http_handler.c/h**: Logic for processing HTTP requests and serving files.
* **public/**: Directory for static assets.



---
*Note: This is an educational project and is not intended for production use. Next steps include implementing MIME type detection for CSS/Image support.*