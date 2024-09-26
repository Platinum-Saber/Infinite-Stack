## Set Up a Discord Bot:

- **Create a Discord bot:**
    1. Go to the Discord Developer Portal.
    2. Create a new application and add a bot to it.
        1. Copy the bot token (you'll need this later for authentication).
    3. Invite the bot to the Discord server.

### 1. Go to the Discord Developer Portal
- Link : [Discord Developer Portal](https://discord.com/developers/docs/intro)

>[!image]- Screen Shot
>![[Pasted image 20240926163158.png]]

### 2. Create a new application and add a bot to it.
- Navigate to the applications tab located at the top of the side panel.
- Create new application
> [!image]- Screen Shot
> ![[Pasted image 20240926163611.png]]


### 3. Invited to the Server:

- You can invite the bot to your server through the **OAuth2 URL Generator** in the Discord Developer Portal.

> [!summary] Here's how:
> 
> 1. Go to the Discord Developer Portal.
> 2. Select your bot (Sebastian) from the list of applications.
> 3. On the left, click **OAuth2** > **URL Generator**.
> 4. In the **OAuth2 URL Generator**:
>     - Under **OAuth2 Scopes**, select **bot**.
>     - Under **OAuth2 Bot Permissions**, ensure you check the necessary permissions (such as `Send Messages`, `Read Messages`, `View Channels`, etc.).
> 5. Copy the generated URL.
> 6. Open the copied URL in your browser, select the server you want to add the bot to, and authorize it.

#### 1. Check Bot Permissions in the Server:

If the bot is already invited to the server, but still isn't visible:

- Go to **Server Settings** > **Roles** and ensure that the bot's role is assigned and it has sufficient permissions (especially "View Channels" and "Send Messages").

##### Bot Permissions:

- The bot should have the required permissions in the channel where you're typing the commands. These include:
    - **Read Messages**
    - **Send Messages**
    - **Read Message History** (to ensure the bot can see the past messages)
    - **Message Content** (as you've enabled this intent)

To verify or adjust permissions:

- Right-click the channel where you want to interact with the bot, select **Edit Channel** > **Permissions**, and ensure the bot role has these permissions.
> [!image]- Screen Shot
> ![[Pasted image 20240926165218.png]]


#### 2. Check the Bot's Online Status:

- The bot should be online and visible in the member list if it's connected to Discord. You can verify if the bot is running and connected by checking the logs in your terminal or console.
- If the bot is online but still not appearing, you may need to enable the "Display role members separately from online members" option for the bot's role.

#### 3. Reinvite the Bot to the Server (if necessary):

If the bot is still not showing up in the server even after you've verified that it's online, try reinviting it using the OAuth2 URL as described in **Step 1**. You might also try removing and re-adding the bot if you encounter any issues.

#### 4. Verify the Bot Token:

Double-check that you're using the correct `DISCORD_BOT_TOKEN` in your `.env` file to ensure you're not accidentally running a different bot.

#### 5. Bot Presence Settings:

If the bot is online but not actively responding to commands, it might be appearing as "invisible" or "offline." You can set its status manually in your bot's `ready` event, like this:
```javascript
client.once('ready', () => {
    console.log(`Successfully connected to Discord as ${client.user.tag}.`);
    client.user.setPresence({
        activities: [{ name: 'with GitHub', type: 'PLAYING' }],
        status: 'online'
    });
});
```
