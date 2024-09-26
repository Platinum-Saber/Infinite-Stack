
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

### **3. Write Bot Logic:**

#### 3.1 Basic Bot Setup (using `discord.js`):

```javascript
require('dotenv').config();
const { Client, GatewayIntentBits } = require('discord.js');
const cron = require('node-cron');
const { initializeOctokit, fetchAndPostAuditLog, fetchAndPostCommits, fetchRepoContent, getOctokit } = require('./services');

// Initialize the bot and set up Octokit
(async () => {
    await initializeOctokit();
    const octokit = getOctokit();
    console.log('Octokit status after initialization:', octokit ? 'Initialized' : 'Not initialized');

    const client = new Client({
        intents: [
            GatewayIntentBits.Guilds,
            GatewayIntentBits.GuildMessages,
            GatewayIntentBits.MessageContent
        ]
    });

  
    const token = process.env.DISCORD_BOT_TOKEN;
    const auditLogChannelId = process.env.DISCORD_AUDIT_LOG_CHANNEL_ID;
    const commitsChannelId = process.env.DISCORD_COMMITS_CHANNEL_ID;

    // Log in to Discord
    client.login(token);
    client.once('ready', () => {

        console.log(`Successfully connected to Discord as ${client.user.tag}.`);

    });

  

    // Schedule tasks

    cron.schedule('0 */2 * * *', () => fetchAndPostAuditLog(client, auditLogChannelId));

    cron.schedule('0 */2 * * *', () => fetchAndPostCommits(client, commitsChannelId));

  

    // Define commands

    const commands = {

        async prs(message, repoOwner, repoName) {

            try {

                const { data: pulls } = await getOctokit().pulls.list({

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

                console.error('Error fetching pull requests:', error);

                message.channel.send('Error fetching pull requests.');

            }

        },

        async postissue(message, repoOwner, repoName) {

            const issuePattern = /!postissue\s+"(.+?)"\s+"(.+?)"/;

            const match = message.content.match(issuePattern);

  

            if (!match || match.length < 3) {

                message.channel.send('Please provide a title and description like this: `!postissue "Title" "Description"`');

                return;

            }

  

            const [ , title, body ] = match;

  

            try {

                const issue = await getOctokit().issues.create({

                    owner: repoOwner,

                    repo: repoName,

                    title: title,

                    body: body

                });

                message.channel.send(`Issue created: ${issue.data.html_url}`);

            } catch (error) {

                console.error('Error creating issue:', error);

                message.channel.send('Error creating issue.');

            }

        },

        async issues(message, repoOwner, repoName) {

            try {

                const { data: issues } = await getOctokit().issues.listForRepo({

                    owner: repoOwner,

                    repo: repoName,

                    state: 'open'

                });

  

                if (issues.length === 0) {

                    message.channel.send('No open issues.');

                } else {

                    issues.forEach(issue => {

                        message.channel.send(`Issue: ${issue.title} - ${issue.html_url}`);

                    });

                }

            } catch (error) {

                console.error('Error fetching issues:', error);

                message.channel.send('Error fetching issues.');

            }

        },

        async repoContent(message, repoOwner, repoName) {

            await fetchRepoContent(client, repoOwner, repoName, message.channel);

        },

        async commits(message, repoOwner, repoName) {

            try {

                const { data: commits } = await getOctokit().repos.listCommits({

                    owner: repoOwner,

                    repo: repoName

                });

                commits.forEach(commit => {
                    message.channel.send(`Commit: ${commit.commit.message} - ${commit.html_url}`);
                });
            } catch (error) {
                console.error('Error fetching commits:', error);
                message.channel.send('Error fetching commits.');
            }
        }
    };

    // Handle message commands
    client.on('messageCreate', async message => {
        if (message.author.bot) return;
        const repoOwner = 'Ballerina-Sentinals';
        const repoName = 'MediSense';
        const command = message.content.split(' ')[0].substring(1); // Extract command after !
        if (commands[command]) {
            await commands[command](message, repoOwner, repoName);
        }
    });
})();
```

### 4. **Bot Commands Breakdown:**

#### **Command: `!prs` (List Pull Requests)**
- When a user types `!prs`, the bot calls the GitHub API to list all open pull requests for the specified repository and posts the title and URL of each pull request in the Discord channel.
- The `octokit.pulls.list()` function is used to fetch the list of open PRs.

#### **Command: `!issue` (Create a New Issue)**
- When a user types `!issue "Issue title" "Issue body"`, the bot creates a new issue in the repository with the provided title and body.
- The `octokit.issues.create()` function is used to create a new issue.

### 5. **Run Your Bot:**
Run your bot locally by using:
```bash
node index.js
```
You should see `Ready!` in your terminal, meaning your bot is active.

### 6. **Host the Bot:**
To keep your bot online, you can host it on cloud platforms like Heroku, AWS, or DigitalOcean. You can use services like [UptimeRobot](https://uptimerobot.com/) to keep it running, or use `pm2` if you're hosting it on a VPS.

### Optional Features:
- **GitLab Integration:** If you're using GitLab, you can use the `node-gitlab` package instead of `@octokit/rest` and modify the commands accordingly.
- **OAuth Integration:** You can implement OAuth to allow users to authenticate and access their personal repositories.

Let me know if you'd like more information on any specific part or need further assistance!