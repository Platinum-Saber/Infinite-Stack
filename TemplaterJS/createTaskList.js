async function createTaskList(tp) {
    // Prompt user for tasks
    const tasksInput = await tp.system.prompt("Enter tasks (comma-separated):");
    if (!tasksInput) {
        new Notice("No tasks provided!", 3000);
        return;
    }

    // Split input into individual tasks
    const tasks = tasksInput.split(",").map(task => task.trim());

    // Generate the task list
    const taskList = tasks.map(task => `- [ ] ${task}`).join("\n");

    // Show the task list as a notice (or insert into a file)
    new Notice(taskList, 5000);

    // Return the task list for further use
    return taskList;
}

module.exports = createTaskList;
