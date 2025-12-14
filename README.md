# Daily Productivity Tracker (C++)

A **CLI-based daily productivity tracker** built using **modern C++ (C++17)**.  
It helps track work, coding practice, personality development, and organisation tasks using a **points-based productivity system**.

The goal is to bring **structure, discipline, and measurable progress** to daily routines.

---

## ✨ Features

- **Task-based scoring system**
  - Time-based scoring (proportional to effort)
  - Direct score input for qualitative tasks
- **Logical task grouping**
  - Coding, Company Work, Personality Development, etc.
- **Automatic weekend handling**
  - Work-related tasks are skipped on weekends
- **Daily productivity percentage**
- **Clean & extensible design**
  - Object-Oriented Programming
  - Factory pattern for task group creation

---

## 🧠 Core Concepts

### 1. Task
Represents a single activity.

**Characteristics**
- Maximum time (in minutes)
- Maximum score
- Scoring type:
  - **Time-based** → score scales with time spent
  - **Direct input** → manual score entry

---

### 2. TaskGroup (formerly SubSheet)
Represents a category of related tasks.

**Examples**
- CODING + DEV
- COMPANY WORK
- PERSONALITY DEVELOPMENT

**Responsibilities**
- Holds multiple tasks
- Computes total and maximum score
- Can be configured to skip on weekends

---

### 3. ProductivityTracker
Acts as the system orchestrator.

**Responsibilities**
- Initializes all task groups
- Collects daily input
- Generates:
  - Detailed per-task report
  - Group-wise summary
  - Overall productivity percentage

---

## 📂 Task Groups Included

| Task Group | Description |
|-----------|------------|
| Daily Start | Small, high-impact startup task |
| Company Work | Office-related work (skipped on weekends) |
| Coding + Dev | DSA, LeetCode, GFG, Codeforces |
| Personality Development | Health, fitness, and communication |
| Organisation | Digital cleanup and system maintenance |

---

## 🛠 Build & Run

```bash
g++ -std=c++17 -O2 ProductivityTracker.cpp -o tracker
./tracker
