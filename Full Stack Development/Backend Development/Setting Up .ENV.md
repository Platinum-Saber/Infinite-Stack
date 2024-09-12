

## 1. Setting up `dotenv`

1. First, install the `dotenv` package:
```
npm install dotenv
```

2. Create a `.env` file in the root of your project (same level as `package.json`):
```
DB_HOST=localhost
DB_USER=root
DB_PASSWORD=2003
DB_NAME=bank_database
```

3. Update your `index.js` file:

```javascript:core banking system/backend/index.js
import express from 'express';
import mysql from 'mysql';
import cors from 'cors';
import dotenv from 'dotenv';

dotenv.config();

const app = express();
app.use(cors());

const db = mysql.createConnection({
    host: process.env.DB_HOST,
    user: process.env.DB_USER,
    password: process.env.DB_PASSWORD,
    database: process.env.DB_NAME
})

// ... rest of the file remains unchanged ...
```

4. Update your `package.json` to include `dotenv`:

```json:core banking system/backend/package.json
{
  "dependencies": {
    "backend": "file:",
    "cors": "^2.8.5",
    "dotenv": "^16.0.3",
    "express": "^4.19.2",
    "mysql": "^2.18.1",
    "nodemon": "^3.1.4"
  }
  // ... rest of the file remains unchanged ...
}
```

These changes will use environment variables to store sensitive information, making your database connection more secure. Remember to add `.env` to your `.gitignore` file to prevent it from being committed to version control.

<br>
<br>

## 2. Stop committing Environmental variables

#### To add `.env` to your `.gitignore` file, follow these steps:

1. Open your project's root directory.
2. Look for a file named `.gitignore`. If it doesn't exist, create one.
3. Open the `.gitignore` file in a text editor.
4. Add the following line to the file:

```
.env
```

5. Save and close the file.

Here's a more detailed explanation:

```gitignore
# Ignore .env file
.env

# You can also ignore all files with .env extension
*.env

# If you have multiple .env files, you can ignore them all like this:
.env*

# Except for .env.example if you want to keep it in version control
!.env.example
```

After making these changes:

1. If you've previously committed the `.env` file, you'll need to remove it from Git's tracking:

```bash
git rm --cached .env
```

2. Then commit the changes to your `.gitignore` file:

```bash
git add .gitignore
git commit -m "Add .env to .gitignore"
```

Now, Git will ignore the `.env` file, and it won't be tracked or committed to your repository. This is important for keeping sensitive information like API keys and passwords out of version control.

Remember, if you're working in a team, make sure to communicate this change to your teammates so they can update their local `.gitignore` files as well.