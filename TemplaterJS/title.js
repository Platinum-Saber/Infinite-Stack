async function title(tp) {
    let title = tp.file.title
    if (title.startsWith("Untitled")) {
        title = await tp.system.prompt("Title:")
        await tp.file.rename(`${title}`)
    }
    new Notice(`Title: ${title}`, 5000)
}

module.exports = title