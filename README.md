# Campus Lost & Found Management System

A beginner-friendly console application written in C. It helps a college campus keep track of items that have been lost or found.

## Features
- Report a lost item or a found item
- View all reported items
- Search reports by item name
- View item category and campus location
- Mark an item as returned/resolved
- Automatically assign an ID to each report
- Save reports in a local text file

## Concepts used
- Structures
- Functions
- Strings
- Loops and switch statements
- File handling
- Basic searching and updating records

## How to run

Compile using GCC:

```bash
gcc main.c -o lost_found
```

On Windows:

```bash
lost_found.exe
```

On Linux/macOS:

```bash
./lost_found
```

The program creates `items.txt` to store reports. Keep it in the same folder as the program. Use underscores instead of spaces when entering names, categories, and locations (for example, `blue_bottle` or `library_block`).

## Project note
This is an educational prototype for a small campus. It does not send notifications or verify ownership; it demonstrates basic record management using C.
