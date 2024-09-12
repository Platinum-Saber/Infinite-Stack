

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