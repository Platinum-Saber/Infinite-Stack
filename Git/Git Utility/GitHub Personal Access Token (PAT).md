To get a GitHub Personal Access Token (PAT), follow these steps:

### 1. Log In to GitHub
   - Go to [GitHub](https://github.com/) and log in with your account.

### 2. Navigate to Developer Settings
   - Click on your profile picture in the top-right corner.
   - From the dropdown menu, select **Settings**.

### 3. Go to "Developer Settings"
   - In the left-hand menu, scroll down and click on **Developer settings** at the bottom.
> [!image]- Screen Shot
> ![[Pasted image 20240926160230.png]]
> ![[Pasted image 20240926160404.png]]

### 4. Select "Personal Access Tokens"
   - Under **Developer settings**, click on **Personal access tokens**.
   - Then, click on **Tokens (classic)** if prompted (GitHub is rolling out new token types but many bots and scripts still use classic tokens).

> [!image]- Screen Shot
> ![[Pasted image 20240926160610.png]]

### 5. Generate New Token
   - Click on **Generate new token** (or **Generate new token (classic)**).
   - You will be prompted to name the token and configure its permissions.

### 6. Set Token Permissions (Scopes)
   - **Give the token a descriptive name**, so you know what it's for (e.g., "Discord Git Bot").
   - Choose the **scopes** (permissions) the token needs. For basic access to repositories (to list pull requests, issues, etc.), you will typically need:
     - `repo` (Full control of private repositories) – this allows access to your repositories.
     - `admin:repo_hook` (Manage repository hooks) – required if you plan to integrate webhooks.
     - If you're working with organization-level repositories, you might need the `read:org` scope.
   
   You can add more permissions depending on what your bot will do.

### 7. Generate and Save the Token
   - Once you've selected the required scopes, click **Generate token** at the bottom of the page.
   - **Important**: Copy the token immediately. You will not be able to see it again once you leave the page.

### 8. Store the Token Securely
   - Save the token in a secure place, such as in environment variables or a secure password manager.
   - Do **not** hard-code the token in your codebase, especially if you plan to share or host the code somewhere publicly.

### 9. Use the Token in Your Code 
   - When using the GitHub API or libraries like `@octokit/rest`, you’ll need to pass this token for authentication.
   - Example (using `octokit` in Node.js):
     ```javascript
     const { Octokit } = require("@octokit/rest");
     const octokit = new Octokit({
       auth: 'your_personal_access_token_here'
     });
     ```

Now your GitHub Personal Access Token is ready to be used for interacting with repositories, issues, and pull requests through the API! Make sure to keep the token private and secure.