# 🍝 Philosophers — Dining Philosophers Problem

> A solution to the classical synchronization problem using C and POSIX threads.

---

## 📌 Project Description

This project simulates the classic **Dining Philosophers** problem, a fundamental exercise in concurrent programming and process synchronization. Each philosopher alternates between thinking and eating, but must acquire two forks (mutexes) to eat, which introduces the risk of **deadlocks** and **race conditions**.

The project explores different techniques to safely and efficiently manage these shared resources using **threads** and **mutexes** in **C**.

---

## ✨ Features

- 🧠 Accurate simulation of concurrent philosophers  
- 🔒 Use of POSIX mutexes to control access to forks  
- 🕒 Timing constraints for eating, sleeping, dying  
- 🏃 Thread-safe logging and clean output  
- 🔁 Support for simulation with any number of philosophers  
- 💥 Handles edge cases like 1 philosopher and starvation

---

## ⚙️ Technologies Used

- 💻 **C Language**  
- 🧵 **POSIX Threads (pthreads)**  
- ⏱️ **gettimeofday** for accurate timing  
- 🔐 **Mutexes** for thread synchronization  
- 📝 Custom utilities for timing, printing, and memory handling

---

## 🚧 Challenges Faced

- Avoiding deadlocks and starvation  
- Achieving millisecond-accurate sleep and timing  
- Writing thread-safe console outputs  
- Managing edge cases and abnormal terminations  
- Balancing performance with clarity

---

## 📁 Table of Contents

- [📌 Project Description](#project-description)  
- [✨ Features](#features)  
- [⚙️ Technologies Used](#technologies-used)  
- [🚧 Challenges Faced](#challenges-faced)  
- [🔧 Installation](#installation)  
- [🚀 Usage](#usage)  
- [🎮 Simulation Options](#simulation-options)  
- [📄 License](#license)

---

## 🔧 Installation

### Requirements

- Unix-like system (Linux/macOS)  
- `gcc` compiler  
- `make` utility  
- POSIX thread support

### Setup

```bash
git clone https://github.com/Thanagorn16/Philosopher.git
cd Philosopher
make
```

---

## 🚀 Usage
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
### Arguments
1. number_of_philosophers: total philosophers/forks

2. time_to_die: time (ms) before a philosopher dies without eating

3. time_to_eat: time (ms) a philosopher spends eating

4. time_to_sleep: time (ms) a philosopher spends sleeping

5. (optional) number_of_times_each_philosopher_must_eat: if all philosophers eat this many times, the simulation ends

---

## 🎮 Simulation Options

| Argument    | Name | Description |
| -------- | ------- | ----------- |
| 1  | $250    | `number_of_philosophers` | Total philosophers (and forks)|            
| 2 | `time_to_die` | Max wait time before dying (ms) |
| 3 | `time_to_eat`| Eating duration (ms) |
| 4  | `time_to_sleep` | Sleeping duration (ms) |
| 5 (opt) | `number_of_times_each_must_eat` | Stop simulation after this many meals per philosopher |

