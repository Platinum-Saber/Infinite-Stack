

## Adding User Signup Functionality

We'll add a new route for user registration, use `bcrypt` for password hashing, and store the user information in the database.

### Step 1: Install additional dependencies

```
npm install bcrypt
```

### Step 2: Update the database schema

Modify your users table to include a password field:

```sql
USE your_database_name;

ALTER TABLE users ADD COLUMN password VARCHAR(255) NOT NULL;
```

### Step 3: Create a signup route

Add the following code to your `app.js` file:

```javascript
const bcrypt = require('bcrypt');

// ... (previous code remains the same)

// Signup route
app.post('/signup', async (req, res) => {
  try {
    const { username, email, password } = req.body;

    // Check if user already exists
    const [existingUsers] = await db.promise().query('SELECT * FROM users WHERE email = ?', [email]);
    if (existingUsers.length > 0) {
      return res.status(400).json({ error: 'User already exists' });
    }

    // Hash the password
    const saltRounds = 10;
    const hashedPassword = await bcrypt.hash(password, saltRounds);

    // Insert the new user into the database
    const [result] = await db.promise().query(
      'INSERT INTO users (name, email, password) VALUES (?, ?, ?)',
      [username, email, hashedPassword]
    );

    res.status(201).json({ message: 'User created successfully', userId: result.insertId });
  } catch (error) {
    console.error('Error in signup:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});
```

### Step 4: Add input validation

For better security, add input validation. You can use a library like `joi` for this purpose. First, install it:

```
npm install joi
```

Then, add the following code to your `app.js`:

```javascript
const Joi = require('joi');

// ... (previous code remains the same)

const signupSchema = Joi.object({
  username: Joi.string().alphanum().min(3).max(30).required(),
  email: Joi.string().email().required(),
  password: Joi.string().pattern(new RegExp('^[a-zA-Z0-9]{3,30}$')).required()
});

app.post('/signup', async (req, res) => {
  try {
    // Validate input
    const { error } = signupSchema.validate(req.body);
    if (error) {
      return res.status(400).json({ error: error.details[0].message });
    }

    // ... (rest of the signup code remains the same)
  } catch (error) {
    console.error('Error in signup:', error);
    res.status(500).json({ error: 'Internal server error' });
  }
});
```

### Step 5: Test the signup functionality

You can test the signup functionality using a tool like Postman or by creating a simple HTML form. Here's an example of how to test it with cURL:

```bash
curl -X POST http://localhost:3000/signup \
  -H "Content-Type: application/json" \
  -d '{"username":"johndoe", "email":"john@example.com", "password":"password123"}'
```

### Security Considerations

1. Always use HTTPS in production to encrypt data in transit.
2. Consider implementing rate limiting to prevent brute-force attacks.
3. Use prepared statements (as shown in the example) to prevent SQL injection attacks.
4. Never store plain-text passwords. Always hash passwords before storing them.
5. Implement proper error handling to avoid leaking sensitive information.

### Next Steps

1. Implement a login route that verifies the email and password.
2. Add authentication middleware to protect routes that require a user to be logged in.
3. Implement password reset functionality.
4. Consider adding email verification for new signups.

Remember to always follow security best practices and keep your dependencies up to date.

