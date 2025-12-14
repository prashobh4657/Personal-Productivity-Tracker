# Daily Productivity Tracker (C++)

A **CLI-based daily productivity tracker** written in modern C++ (C++17).  
It helps you track work, coding, personality development, and organisation tasks
using a **points-based scoring system**.

---

## ✨ Features

- Task-based scoring (time-based or direct score input)
- Logical grouping of tasks (Coding, Company Work, Personality, etc.)
- Automatic **weekend skipping** for work-related tasks
- Daily productivity percentage
- Clean, extensible architecture (OOP + Factory pattern)

---

## 🧠 Core Concepts

### 1. Task
Represents a single activity.
- Has max time
- Has max score
- Can be:
  - **Time-based** (points proportional to time spent)
  - **Direct input** (manual score entry)

### 2. TaskGroup (formerly SubSheet)
Represents a category of tasks.
Examples:
- CODING + DEV
- COMPANY WORK
- PERSONALITY DEVELOPMENT

Each group:
- Holds multiple tasks
- Calculates total & max score
- Can be skipped on weekends

### 3. ProductivityTracker
- Orchestrates all task groups
- Collects user input
- Prints:
  - Detailed report
  - Daily summary
  - Overall productivity %

---

## 📂 Task Groups Included

| Group | Description |
|------|------------|
| Daily Start | Small high-impact startup task |
| Company Work | Office work (skipped on weekends) |
| Coding + Dev | DSA, LeetCode, GFG, CF |
| Personality Development | Health & communication |
| Organisation | Digital & personal cleanup |

---

## 🛠 Build & Run

```bash
g++ -std=c++17 -O2 ProductivityTracker.cpp -o tracker
./tracker
