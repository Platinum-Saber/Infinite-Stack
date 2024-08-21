Related : #OS #Daemons 

---
# Content

# System Daemons
> [!faq]- What are system daemons
>- *Background processes* that run on an operating system (OS) to *perform specific tasks* **without user interaction**. 
> - Often essential for the proper functioning of the system and are usually **started at boot time**, *running continuously in the background*.

<br>

## Characteristics of System daemons
- **Background Processes**:
    - Daemons run in the background, meaning they *don’t have a* **direct interface** (like a window) for user interaction. They *perform tasks* **autonomously** without requiring user input.

- **Start at Boot**:
    - Many daemons *start when the system boots* up and *continue to run until the system is* **shut down or restarted**. For example, a web server daemon might start at boot and listen for incoming HTTP requests.

- **Provide Services**:
    - Daemons provide various services, such as *handling network requests*, *managing hardware devices*, or *maintaining system logs*.

- **Run Independently**:
    - Daemons **operate independently** *of user applications*, ensuring that essential system functions are maintained even if no user is logged in.

- **Low Visibility**:
    - Since they don’t interact with users directly, daemons usually have low visibility. They quietly manage tasks in the background to keep the system running smoothly.