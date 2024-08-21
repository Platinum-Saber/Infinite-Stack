Related : #OS #Daemons 

---
# Content

# System Daemons
> [!faq]- What are system daemons
>- *Background processes* that run on an operating system (OS) to *perform specific tasks* **without user interaction**. 
> - Often essential for the proper functioning of the system and are usually **started at boot time**, *running continuously in the background*.

<br>

## Characteristics of System daemons

> [!info]- ** Background Processes**:
> 
> Daemons run in the background, meaning they *don’t have a* **direct interface** (like a window) for user interaction. They *perform tasks* **autonomously** without requiring user input.

> [!info]- **Start at Boot**:
>  Many daemons *start when the system boots* up and *continue to run until the system is* **shut down or restarted**. For example, a web server daemon might start at boot and listen for incoming HTTP requests.

> [!info]- **Provide Services**:
>  Daemons provide various services, such as *handling network requests*, *managing hardware devices*, or *maintaining system logs*.

> [!info]- **Run Independently**:
>    Daemons **operate independently** *of user applications*, ensuring that essential system functions are maintained even if no user is logged in.

> [!info]- **Low Visibility**:
>    Since they don’t interact with users directly, daemons usually have **low visibility**. They *quietly manage tasks in the background* to keep the system running smoothly.

<br>

## Examples of System Daemons

> [!NOTE] Daemons
> - **cron**:
>     
>     - Manages scheduled tasks in Unix-like operating systems. It allows users and system administrators to run scripts or programs at specified times.
> - **sshd**:
>     
>     - The SSH daemon handles Secure Shell (SSH) connections, allowing secure remote access to the system.
> - **httpd**:
>     
>     - The Apache HTTP Server daemon handles web server requests, serving web pages to users.
> - **systemd**:
>     
>     - A modern system and service manager for Linux, responsible for initializing and managing system daemons during boot and shutdown.
> - **init**:
>     
>     - The traditional system and service manager on Unix-like systems, responsible for starting system processes during boot.
> - **mysqld**:
>     
>     - The MySQL daemon, responsible for managing MySQL database services.
> - **cupsd**:
>     
>     - Manages print jobs in Unix-like systems, part of the Common UNIX Printing System (CUPS).
> - **rsyslogd**:
>     
>     - Handles system logging, recording system events and messages to log files.

## How Daemons Work
When a daemon starts, it usually **detaches itself from the terminal** and *runs in the background*. This involves several steps:

1. **Forking**:
    
    - The daemon process typically "forks" itself, meaning it creates a copy of itself. The parent process may then terminate, leaving the child process to run as the daemon.
2. **Detaching from Terminal**:
    
    - The daemon disconnects from the terminal (or controlling terminal) to ensure it continues running independently, even if the user logs out.
3. **Running in the Background**:
    
    - The daemon continues to run in the background, performing its designated tasks. It waits for specific events or conditions to occur, such as a scheduled time or an incoming network request.

<br>

## Managing Daemons

On Unix-like systems, you can manage daemons using service management tools like `systemd`, `init`, or `service` commands. These tools allow you to start, stop, restart, or check the status of daemons.

- **systemctl** (for systemd-based systems):
    
    - `systemctl start <daemon_name>`
    - `systemctl stop <daemon_name>`
    - `systemctl status <daemon_name>`
- **service** (older systems):
    
    - `service <daemon_name> start`
    - `service <daemon_name> stop`
    - `service <daemon_name> status`