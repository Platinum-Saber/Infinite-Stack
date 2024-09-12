# Setting up a Node.js Backend with SQL Database

## Prerequisites
- Node.js installed on your system
- MySQL installed and running
- Basic knowledge of JavaScript and SQL

## Step 1: Set up the project

#### 1. Create a new directory for your project and navigate to it:
   ```
   mkdir my-nodejs-backend
   cd my-nodejs-backend
   ```

#### 2. Initialize a new Node.js project:
   ```
   npm init -y
   ```

#### 3. Install necessary dependencies:
   ```
   npm install express mysql2 dotenv
   ```

   - `express`: Web application framework
   - `mysql2`: MySQL client for Node.js
   - `dotenv`: For managing environment variables

<br>

## Step 2: Create the main application file

Create a new file named `app.js` in your project root:

```javascript
const express = require('express');
const mysql = require('mysql2');
require('dotenv').config();

const app = express();
const port = process.env.PORT || 3000;

// Middleware
app.use(express.json());

// Database connection
const db = mysql.createConnection({
  host: process.env.DB_HOST,
  user: process.env.DB_USER,
  password: process.env.DB_PASSWORD,
  database: process.env.DB_NAME,
});

db.connect((err) => {
  if (err) {
    console.error('Error connecting to the database:', err);
    return;
  }
  console.log('Connected to the database');
});

// Routes
app.get('/', (req, res) => {
  res.json({ message: 'Welcome to the Node.js backend!' });
});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});
```

## Step 3: Set up environment variables

Create a `.env` file in your project root:

```
PORT=3000
DB_HOST=localhost
DB_USER=your_mysql_username
DB_PASSWORD=your_mysql_password
DB_NAME=your_database_name
```

Make sure to replace the placeholder values with your actual MySQL credentials.

## Step 4: Create a sample database and table

Log in to your MySQL client and run the following commands:

```sql
CREATE DATABASE IF NOT EXISTS your_database_name;
USE your_database_name;

CREATE TABLE IF NOT EXISTS users (
  id INT AUTO_INCREMENT PRIMARY KEY,
  name VARCHAR(100) NOT NULL,
  email VARCHAR(100) UNIQUE NOT NULL
);

INSERT INTO users (name, email) VALUES 
  ('John Doe', 'john@example.com'),
  ('Jane Smith', 'jane@example.com');
```

## Step 5: Add a route to fetch users

Add the following route to your `app.js` file:

```javascript
app.get('/users', (req, res) => {
  db.query('SELECT * FROM users', (err, results) => {
    if (err) {
      console.error('Error fetching users:', err);
      res.status(500).json({ error: 'Error fetching users' });
      return;
    }
    res.json(results);
  });
});
```

## Step 6: Run the application

Start your Node.js application:

```
node app.js
```

You should see messages indicating that the server is running and connected to the database.

## Testing the API

You can test your API using tools like cURL, Postman, or your web browser:

1. Open a web browser or Postman and navigate to `http://localhost:3000/`
   You should see the welcome message.

2. Navigate to `http://localhost:3000/users`
   You should see the list of users from the database.

## Next Steps

1. Implement error handling and input validation
2. Add more routes for creating, updating, and deleting users
3. Implement authentication and authorization
4. Consider using an ORM like Sequelize for more complex database operations
5. Set up a testing framework for your API

Remember to always follow security best practices, such as using prepared statements to prevent SQL injection, validating and sanitizing user inputs, and never exposing sensitive information like database credentials.


