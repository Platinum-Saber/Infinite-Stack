
### 1. Set Up Your Bot with `discord.js`:

#### 1.1 Create a Discord Application:
1. Go to the [Discord Developer Portal](https://discord.com/developers/applications) and create a new application.
2. In the application settings, go to the "Bot" section and create a bot.
3. Copy the bot token, as you'll need it for authentication later.

#### 1.2 Install Node.js and `discord.js`:
- First, install Node.js if you haven't already from [here](https://nodejs.org/en/).
- Then, in your project directory, run the following commands to set up your project and install `discord.js`:
  ```bash
  mkdir discord-git-bot
  cd discord-git-bot
  npm init -y
  npm install discord.js @octokit/rest
  ```

#### 1.3 Create `index.js` File:
Create a file named `index.js` to house your bot's logic.

### 2. Install GitHub/GitLab API Client Libraries:
   - For GitHub, use the `@octokit/rest` package, which is the official GitHub API client for Node.js.
   - If you want to integrate with GitLab, you can use `gitlab`.

   Install `octokit` for GitHub integration:
   ```bash
   npm install @octokit/rest
   ```

### 3. Write Bot Logic:

#### 3.1 Bot Setup (using `discord.js`):

- How to get git access token : [[GitHub Personal Access Token (PAT)]]


```javascript
// Require the necessary discord.js classes
const { Client, GatewayIntentBits } = require('discord.js');
const { Octokit } = require("@octokit/rest");

// Create a new client instance
const client = new Client({ intents: [GatewayIntentBits.Guilds, GatewayIntentBits.GuildMessages] });

// Your bot token (from the Discord Developer Portal)
const token = 'YOUR_DISCORD_BOT_TOKEN';

// GitHub Personal Access Token (from GitHub Developer Settings)
const githubToken = 'YOUR_GITHUB_PERSONAL_ACCESS_TOKEN';

// Initialize the Octokit (GitHub API client)
const octokit = new Octokit({ auth: githubToken });

// When the bot is ready, run this code
client.once('ready', () => {
    console.log('Ready!');
});

// Command to fetch open pull requests
client.on('messageCreate', async message => {
    if (message.content.startsWith('!prs')) {
        const repoOwner = 'OWNER_NAME';
        const repoName = 'REPO_NAME';

        try {
            const { data: pulls } = await octokit.pulls.list({
                owner: repoOwner,
                repo: repoName,
                state: 'open'
            });

            if (pulls.length === 0) {
                message.channel.send('No open pull requests.');
            } else {
                pulls.forEach(pr => {
                    message.channel.send(`PR: ${pr.title} - ${pr.html_url}`);
                });
            }
        } catch (error) {
            console.error(error);
            message.channel.send('Error fetching pull requests.');
        }
    }

    // Command to create a new issue
    if (message.content.startsWith('!issue')) {
        const [_, title, body] = message.content.split('"').filter(Boolean);

        if (!title || !body) {
            message.channel.send('Please provide a title and body for the issue.');
            return;
        }

        try {
            const issue = await octokit.issues.create({
                owner: 'OWNER_NAME',
                repo: 'REPO_NAME',
                title: title,
                body: body
            });
            message.channel.send(`Issue created: ${issue.data.html_url}`);
        } catch (error) {
            console.error(error);
            message.channel.send('Error creating issue.');
        }
    }
});

// Login to Discord with your app's token
client.login(token);
```

### 4. Bot Commands Breakdown:

#### Command: `!prs` (List Pull Requests)
- When a user types `!prs`, the bot calls the GitHub API to list all open pull requests for the specified repository and posts the title and URL of each pull request in the Discord channel.
- The `octokit.pulls.list()` function is used to fetch the list of open PRs.

#### Command: `!issue` (Create a New Issue)
- When a user types `!issue "Issue title" "Issue body"`, the bot creates a new issue in the repository with the provided title and body.
- The `octokit.issues.create()` function is used to create a new issue.

### 5. Run Your Bot:
Run your bot locally by using:
```bash
node index.js
```
You should see `Ready!` in your terminal, meaning your bot is active.

### 6. Host the Bot:
To keep your bot online, you can host it on cloud platforms like Heroku, AWS, or DigitalOcean. You can use services like [UptimeRobot](https://uptimerobot.com/) to keep it running, or use `pm2` if you're hosting it on a VPS.

### Optional Features:
- **GitLab Integration:** If you're using GitLab, you can use the `node-gitlab` package instead of `@octokit/rest` and modify the commands accordingly.
- **OAuth Integration:** You can implement OAuth to allow users to authenticate and access their personal repositories.
