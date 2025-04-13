<h1 align="center"> 
	PHILOSOPHERS
</h1>

<p align="center">
	<img src="https://img.shields.io/badge/Language-C-blue?style=flat-square"/>
	<img src="https://img.shields.io/badge/Concurrency-Threads%20%7C%20Processes-orange?style=flat-square"/>
	<img src="https://img.shields.io/badge/Project-Philosophers-green?style=flat-square"/>
</p>

**Philosophers** is a classic concurrency problem implementation, created in C. This project simulates the behavior of philosophers sitting at a table, thinking, eating, and competing for limited resources (forks). It's an essential project to understand race conditions, deadlocks, and synchronization techniques using **threads** and **processes**.

## › Features
- 🍝 Simulates the **Dining Philosophers Problem** in real-time
- 🧵 Implements thread-based concurrency with **mutexes**
- 🧪 Bonus version using **processes** and **semaphores**
- 🛑 Avoids **deadlocks** and **starvation**
- 🔧 Parameterized execution: number of philosophers, time to eat/sleep/die
- 📚 Solid practice in synchronization and systems-level programming

## › Project Overview
<p align="center">
	<img src="https://upload.wikimedia.org/wikipedia/commons/7/7b/An_illustration_of_the_dining_philosophers_problem.png" alt="Dining Philosophers Problem" width="200"/>
</p>

In this simulation:
- Each philosopher is represented by a **thread** or **process**
- Forks are shared resources requiring proper **locking mechanisms**
- The program ensures that no philosopher **dies from starvation**
- Includes a **monitoring system** to check for philosopher death and manage simulation flow

# How to Use
 ## › Run with threads (mandatory)
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

› Example
./philo 5 800 200 200

## › Run with processes (bonus)
./philo_bonus <same_arguments_as_above>

## › Arguments

| Argument                                | Description                                            |
|----------------------------------------|--------------------------------------------------------|
| `number_of_philosophers`               | Number of philosophers and forks                      |
| `time_to_die`                          | Time (ms) a philosopher can go without eating         |
| `time_to_eat`                          | Time (ms) spent eating                                |
| `time_to_sleep`                        | Time (ms) spent sleeping                              |
| `number_of_times_each_philosopher_must_eat` | (Optional) Stops the simulation once all have eaten this many times |

## › Bonus Version

The bonus challenge is to implement the same logic using **processes** instead of threads. Each philosopher runs in its **own process**, communicating via **semaphores** to manage forks and logging.

## 📫 Contact

Feel free to reach out or explore more of my work:

[<img src="https://img.shields.io/badge/LinkedIn-0077B5?style=flat-square&logo=linkedin&logoColor=white"/>](https://www.linkedin.com/in/aitor-guinea-961635348/)  
[<img src="https://img.shields.io/badge/GitHub-aguinea1-black?style=flat-square&logo=github"/>](https://github.com/aguinea1)  
[<img src="https://img.shields.io/badge/Email-guineaitor36@gmail.com-red?style=flat-square&logo=gmail&logoColor=white"/>](mailto:guineaitor36@gmail.com)

⭐
