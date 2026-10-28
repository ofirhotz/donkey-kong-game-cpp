# Donkey Kong Game (C++)

🎮 A simple version of the classic **Donkey Kong** game implemented in C++, using object-oriented programming principles.

## 📌 About the Project

This project is a console-based implementation of the Donkey Kong arcade game, developed as part of Academic Object-Oriented Programming (OOP) — Exercise #3.  
The game logic, structure, and design are built using C++ (OOP), focusing on clarity, modularity, and maintainability.

## 🛠 Features

* Modular design using C++ classes (e.g., `Game`, `Board`, `Ghost`, `Barrel`, `Mario`, etc.)
* Two gameplay modes: Manual and Automatic (Save/Load steps recording)
* Ghost AI and multiple types of enemies
* Screen file parsing and configuration files (`.screen`)
* Game result tracking and scoring
* Clean architecture with headers and implementation files separated

## 🧠 Concepts & Technologies

* Object-Oriented Programming (classes, inheritance, encapsulation)
* File I/O (reading level data, game screens, steps recording)
* Basic game loop and rendering logic in console
* Memory management in C++

## 🕹️ Controls & Navigation

> **Important:** The Windows console input must be set to **English (lowercase)** for commands to register properly.

* **`a`** — Move Left
* **`d`** — Move Right
* **`w`** — Jump / Climb Ladder Up (`H`)
* **`x`** — Climb Ladder Down
* **`s`** — Stay / Stop
* **`p`** — Hammer Attack (when hammer `p` is collected)

## 📝 Project & Gameplay Notes

1. **Mario Spawn:** Mario is initialized in the `level1.screen` file; in subsequent lives, he respawns in that same position.
2. **Barrels Scoring:** Some barrels are empty and do not grant score points upon avoidance/destruction.
3. **Execution & Naming:** The project was originally designated as `DONKYKONG` for academic automated command-line evaluation scripts.
4. **Recording & Replay Mode:** Gameplay always begins from the first level. In save/record mode, only the first level onwards is recorded, generating a single `gameSteps.txt` file and a corresponding `gameSteps.result.txt` file.

## ⚠️ Known Issues & Technical Limitations

* **Console Rendering Artifacts:** Due to direct console cursor manipulation (`gotoxy`), minor text residual artifacts or flickering may occasionally appear during fast movements.
* **Keyboard Layout Sensitivity:** Controls rely strictly on lowercase ASCII inputs (`a`, `d`, `w`, `x`, `s`); alternate keyboard languages (e.g., Hebrew) or Caps-Lock will prevent character movement.