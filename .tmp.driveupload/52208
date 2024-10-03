1. Run the `movie_store_schema.sql` :- This creates the database and relevant tables.
2. Run the `movie_store-data.sql` :- This populates the tables with relevant data.
3. Run The Queries in `Quize 07.sql` one by one and see if it works.


---

### 1. **Display the first and last names of all actors from the table `actor`.**

```sql
SELECT first_name, last_name
FROM actor;
```

**Explanation:**
- **SELECT first_name, last_name:** Retrieves the `first_name` and `last_name` columns.
- **FROM actor:** Specifies the `actor` table as the source of data.

---

### 2. **Display the first and last name of each actor in a single column in upper case letters. Name the column `Actor Name`.**

```sql
SELECT UPPER(CONCAT(first_name, ' ', last_name)) AS `Actor Name`
FROM actor;
```

**Explanation:**
- **CONCAT(first_name, ' ', last_name):** Combines `first_name` and `last_name` with a space in between.
- **UPPER(...):** Converts the concatenated name to uppercase letters.
- **AS `Actor Name`:** Aliases the resulting column as "Actor Name".
- **FROM actor:** Specifies the `actor` table as the data source.

---

### 3. **Find the ID number, first name, and last name of an actor, of whom you know only the first name, "Joe." Write a query to retrieve the corresponding information.**

```sql
SELECT actor_id, first_name, last_name
FROM actor
WHERE first_name = 'Joe';
```

**Explanation:**
- **SELECT actor_id, first_name, last_name:** Retrieves the `actor_id`, `first_name`, and `last_name` columns.
- **FROM actor:** Specifies the `actor` table.
- **WHERE first_name = 'Joe':** Filters the results to include only actors with the first name "Joe".

*Note:* If multiple actors share the first name "Joe," this query will return all matching records.

---

### 4. **Find all actors whose last name contains the letters "GEN".**

```sql
SELECT first_name, last_name
FROM actor
WHERE last_name LIKE '%GEN%';
```

**Explanation:**
- **WHERE last_name LIKE '%GEN%':** Uses the `LIKE` operator with wildcards `%` to find any `last_name` that includes the substring "GEN" anywhere within it.
- **SELECT first_name, last_name:** Retrieves the relevant name columns.

*Note:* The `LIKE` operator in MySQL is case-insensitive by default, depending on the table's collation.

---

### 5. **Find all actors whose last names contain the letters "LI". Order the rows by last name and first name.**

```sql
SELECT first_name, last_name
FROM actor
WHERE last_name LIKE '%LI%'
ORDER BY last_name ASC, first_name ASC;
```

**Explanation:**
- **WHERE last_name LIKE '%LI%':** Filters actors whose `last_name` includes the substring "LI".
- **ORDER BY last_name ASC, first_name ASC:** Sorts the results first by `last_name` in ascending order, then by `first_name` in ascending order.

---

### 6. **Using `IN`, display the `country_id` and `country` columns of the following countries: Afghanistan, Bangladesh, and China.**

```sql
SELECT country_id, country
FROM country
WHERE country IN ('Afghanistan', 'Bangladesh', 'China');
```

**Explanation:**
- **WHERE country IN ('Afghanistan', 'Bangladesh', 'China'):** Utilizes the `IN` operator to filter records where the `country` column matches any of the specified values.
- **SELECT country_id, country:** Retrieves the `country_id` and `country` columns from the `country` table.

---

### 7. **Add a `middle_name` column to the table `actor`. Position it between `first_name` and `last_name`.**

```sql
ALTER TABLE actor
ADD COLUMN middle_name VARCHAR(45) AFTER first_name;
```

**Explanation:**
- **ALTER TABLE actor:** Specifies that we're modifying the `actor` table.
- **ADD COLUMN middle_name VARCHAR(45):** Adds a new column named `middle_name` with a data type of `VARCHAR(45)`.
- **AFTER first_name:** Positions the new `middle_name` column immediately after the `first_name` column.

*Note:* Adjust the `VARCHAR` length as needed based on your data requirements.

---

### 8. **You realize that some of these actors have tremendously long last names. Change the data type of the `middle_name` column to `BLOB`.**

```sql
ALTER TABLE actor
MODIFY COLUMN middle_name BLOB;
```

**Explanation:**
- **ALTER TABLE actor:** Indicates that we're modifying the `actor` table.
- **MODIFY COLUMN middle_name BLOB:** Changes the data type of the existing `middle_name` column to `BLOB`.

*Important Consideration:* 
- **Data Type Suitability:** Typically, `BLOB` (Binary Large Object) is used for storing binary data. If you intend to store long text data, consider using `TEXT` or `LONGTEXT` instead.
  
  ```sql
  ALTER TABLE actor
  MODIFY COLUMN middle_name TEXT;
  ```

  This modification ensures that textual data is stored appropriately without issues related to binary data handling.

---

### 9. **List the last names of actors, as well as how many actors have that last name.**

```sql
SELECT last_name, COUNT(*) AS actor_count
FROM actor
GROUP BY last_name;
```

**Explanation:**
- **SELECT last_name, COUNT(*) AS actor_count:** Retrieves each unique `last_name` and counts the number of actors sharing that name, aliasing the count as "actor_count".
- **FROM actor:** Specifies the `actor` table as the data source.
- **GROUP BY last_name:** Groups the results by `last_name` to aggregate the counts accordingly.

---

### 10. **List last names of actors and the number of actors who have that last name, but only for names that are shared by at least two actors.**

```sql
SELECT last_name, COUNT(*) AS actor_count
FROM actor
GROUP BY last_name
HAVING COUNT(*) >= 2;
```

**Explanation:**
- **SELECT last_name, COUNT(*) AS actor_count:** Retrieves each unique `last_name` and counts the number of actors sharing that name.
- **FROM actor:** Specifies the `actor` table.
- **GROUP BY last_name:** Groups the results by `last_name`.
- **HAVING COUNT(*) >= 2:** Filters the grouped results to include only those `last_name` entries where the count is two or more, effectively listing only last names shared by at least two actors.

Certainly! Below are the SQL queries addressing each of your questions (11 through 22) based on the provided `movie_store_2` database schema. Each query includes an explanation to help you understand its purpose and functionality.

---

### 11. **Use JOIN to display the first and last names, as well as the address, of each staff member. Use the tables `staff` and `address`.**

```sql
SELECT 
    s.first_name, 
    s.last_name, 
    a.address
FROM 
    staff AS s
JOIN 
    address AS a 
    ON s.address_id = a.address_id;
```

**Explanation:**
- **SELECT s.first_name, s.last_name, a.address:** Retrieves the `first_name` and `last_name` from the `staff` table and the `address` from the `address` table.
- **FROM staff AS s:** Specifies the `staff` table with an alias `s`.
- **JOIN address AS a ON s.address_id = a.address_id:** Performs an inner join between `staff` and `address` tables where the `address_id` matches in both tables. The `address` table is aliased as `a`.

---

### 12. **Use JOIN to display the total amount rung up by each staff member in August of 2005. Use tables `staff` and `payment`.**

```sql
SELECT 
    s.staff_id, 
    CONCAT(s.first_name, ' ', s.last_name) AS staff_name, 
    SUM(p.amount) AS total_amount
FROM 
    staff AS s
JOIN 
    payment AS p 
    ON s.staff_id = p.staff_id
WHERE 
    p.payment_date BETWEEN '2005-08-01' AND '2005-08-31'
GROUP BY 
    s.staff_id, s.first_name, s.last_name;
```

**Explanation:**
- **SELECT s.staff_id, CONCAT(s.first_name, ' ', s.last_name) AS staff_name, SUM(p.amount) AS total_amount:**
  - Retrieves the `staff_id`.
  - Concatenates `first_name` and `last_name` into a single column named `staff_name`.
  - Calculates the total payment amount per staff member using `SUM(p.amount)`.
- **FROM staff AS s JOIN payment AS p ON s.staff_id = p.staff_id:**
  - Joins the `staff` and `payment` tables on the `staff_id` field.
- **WHERE p.payment_date BETWEEN '2005-08-01' AND '2005-08-31':**
  - Filters payments made in August 2005.
- **GROUP BY s.staff_id, s.first_name, s.last_name:**
  - Groups the results by each staff member to aggregate the total amounts.

*Note:* Adjust the date format if your SQL server expects a different format.

---

### 13. **List each film and the number of actors who are listed for that film. Use tables `film_actor` and `film`. Use INNER JOIN.**

```sql
SELECT 
    f.title, 
    COUNT(fa.actor_id) AS actor_count
FROM 
    film AS f
INNER JOIN 
    film_actor AS fa 
    ON f.film_id = fa.film_id
GROUP BY 
    f.film_id, f.title;
```

**Explanation:**
- **SELECT f.title, COUNT(fa.actor_id) AS actor_count:**
  - Retrieves the `title` of each film.
  - Counts the number of `actor_id` entries associated with each film, aliasing it as `actor_count`.
- **FROM film AS f INNER JOIN film_actor AS fa ON f.film_id = fa.film_id:**
  - Performs an inner join between `film` and `film_actor` tables on the `film_id`.
- **GROUP BY f.film_id, f.title:**
  - Groups the results by each film to aggregate the number of actors per film.

---

### 14. **How many copies of the film "Hunchback Impossible" exist in the inventory system?**

```sql
SELECT 
    COUNT(*) AS copy_count
FROM 
    inventory AS i
JOIN 
    film AS f 
    ON i.film_id = f.film_id
WHERE 
    f.title = 'Hunchback Impossible';
```

**Explanation:**
- **SELECT COUNT(*) AS copy_count:**
  - Counts the total number of inventory records for the specified film, aliasing it as `copy_count`.
- **FROM inventory AS i JOIN film AS f ON i.film_id = f.film_id:**
  - Joins the `inventory` and `film` tables on the `film_id`.
- **WHERE f.title = 'Hunchback Impossible':**
  - Filters the records to include only those where the film title is "Hunchback Impossible".

*Note:* Ensure that the film title matches exactly as stored in the database, including case sensitivity based on collation settings.

---

### 15. **The music of Queen and Kris Kristofferson have seen an unlikely resurgence. As an unintended consequence, films starting with the letters K and Q have also soared in popularity. Use subqueries to display the titles of movies starting with the letters K and Q whose language is English.**

```sql
SELECT 
    f.title
FROM 
    film AS f
WHERE 
    (f.title LIKE 'K%' OR f.title LIKE 'Q%')
    AND f.language_id = (
        SELECT 
            l.language_id 
        FROM 
            language AS l 
        WHERE 
            l.name = 'English'
        LIMIT 1
    );
```

**Explanation:**
- **SELECT f.title:**
  - Retrieves the `title` of films.
- **FROM film AS f:**
  - Specifies the `film` table with alias `f`.
- **WHERE (f.title LIKE 'K%' OR f.title LIKE 'Q%'):**
  - Filters films where the title starts with 'K' or 'Q'.
- **AND f.language_id = (SELECT l.language_id FROM language AS l WHERE l.name = 'English' LIMIT 1):**
  - Uses a subquery to find the `language_id` corresponding to 'English' from the `language` table.
  - Ensures that only films with the language set to English are selected.

*Alternative Approach:* If you want to handle cases where multiple languages might have the name 'English' (though unlikely), you can use `IN` instead of `=`.

```sql
SELECT 
    f.title
FROM 
    film AS f
WHERE 
    (f.title LIKE 'K%' OR f.title LIKE 'Q%')
    AND f.language_id IN (
        SELECT 
            l.language_id 
        FROM 
            language AS l 
        WHERE 
            l.name = 'English'
    );
```

---

### 16. **Use subqueries to display all actors who appear in the film "Alone Trip."**

```sql
SELECT 
    a.first_name, 
    a.last_name
FROM 
    actor AS a
WHERE 
    a.actor_id IN (
        SELECT 
            fa.actor_id
        FROM 
            film_actor AS fa
        JOIN 
            film AS f 
            ON fa.film_id = f.film_id
        WHERE 
            f.title = 'Alone Trip'
    );
```

**Explanation:**
- **SELECT a.first_name, a.last_name:**
  - Retrieves the first and last names of actors.
- **FROM actor AS a:**
  - Specifies the `actor` table with alias `a`.
- **WHERE a.actor_id IN (...):**
  - Filters actors whose `actor_id` is in the list returned by the subquery.
- **Subquery:**
  - **SELECT fa.actor_id FROM film_actor AS fa JOIN film AS f ON fa.film_id = f.film_id WHERE f.title = 'Alone Trip':**
    - Joins `film_actor` and `film` tables to find `actor_id`s associated with the film titled "Alone Trip".

*Alternative Approach:* Using EXISTS.

```sql
SELECT 
    a.first_name, 
    a.last_name
FROM 
    actor AS a
WHERE 
    EXISTS (
        SELECT 
            1
        FROM 
            film_actor AS fa
        JOIN 
            film AS f 
            ON fa.film_id = f.film_id
        WHERE 
            fa.actor_id = a.actor_id
            AND f.title = 'Alone Trip'
    );
```

---

### 17. **You want to run an email marketing campaign in Canada, for which you will need the names and email addresses of all Canadian customers. Use JOINs to retrieve this information.**

```sql
SELECT 
    c.first_name, 
    c.last_name, 
    c.email
FROM 
    customer AS c
JOIN 
    address AS a 
    ON c.address_id = a.address_id
JOIN 
    city AS ci 
    ON a.city_id = ci.city_id
JOIN 
    country AS co 
    ON ci.country_id = co.country_id
WHERE 
    co.country = 'Canada'
    AND c.email IS NOT NULL;
```

**Explanation:**
- **SELECT c.first_name, c.last_name, c.email:**
  - Retrieves the first name, last name, and email of customers.
- **FROM customer AS c:**
  - Specifies the `customer` table with alias `c`.
- **JOIN address AS a ON c.address_id = a.address_id:**
  - Joins the `address` table to get address details.
- **JOIN city AS ci ON a.city_id = ci.city_id:**
  - Joins the `city` table to get city details.
- **JOIN country AS co ON ci.country_id = co.country_id:**
  - Joins the `country` table to get country details.
- **WHERE co.country = 'Canada' AND c.email IS NOT NULL:**
  - Filters customers residing in Canada and ensures that the email field is not null.

*Note:* Including `c.email IS NOT NULL` ensures that only customers with an email address are retrieved, which is essential for an email marketing campaign.

---

### 18. **Sales have been lagging among young families, and you wish to target all family movies for a promotion. Identify all movies categorized as family films.**

```sql
SELECT 
    f.title
FROM 
    film AS f
JOIN 
    film_category AS fc 
    ON f.film_id = fc.film_id
JOIN 
    category AS c 
    ON fc.category_id = c.category_id
WHERE 
    c.name = 'Family';
```

**Explanation:**
- **SELECT f.title:**
  - Retrieves the title of films.
- **FROM film AS f JOIN film_category AS fc ON f.film_id = fc.film_id JOIN category AS c ON fc.category_id = c.category_id:**
  - Joins the `film`, `film_category`, and `category` tables to link films to their categories.
- **WHERE c.name = 'Family':**
  - Filters films that are categorized under 'Family'.

*Alternative Approach:* If you prefer to use `DISTINCT` to avoid duplicate titles in case a film belongs to multiple categories including 'Family'.

```sql
SELECT DISTINCT 
    f.title
FROM 
    film AS f
JOIN 
    film_category AS fc 
    ON f.film_id = fc.film_id
JOIN 
    category AS c 
    ON fc.category_id = c.category_id
WHERE 
    c.name = 'Family';
```

---

### 19. **In your new role as an executive, you would like to have an easy way of viewing -- the Top five genres by gross revenue. Use the solution from the problem above to create a view.**

```sql
CREATE VIEW top_five_genres_by_revenue AS
SELECT 
    c.name AS genre, 
    SUM(p.amount) AS total_revenue
FROM 
    payment AS p
JOIN 
    rental AS r 
    ON p.rental_id = r.rental_id
JOIN 
    inventory AS i 
    ON r.inventory_id = i.inventory_id
JOIN 
    film AS f 
    ON i.film_id = f.film_id
JOIN 
    film_category AS fc 
    ON f.film_id = fc.film_id
JOIN 
    category AS c 
    ON fc.category_id = c.category_id
GROUP BY 
    c.category_id, c.name
ORDER BY 
    total_revenue DESC
LIMIT 5;
```

**Explanation:**
- **CREATE VIEW top_five_genres_by_revenue AS:**
  - Creates a new view named `top_five_genres_by_revenue`.
- **SELECT c.name AS genre, SUM(p.amount) AS total_revenue:**
  - Retrieves the category name (`genre`) and calculates the total revenue (`total_revenue`) by summing the payment amounts.
- **FROM payment AS p JOIN rental AS r ON p.rental_id = r.rental_id JOIN inventory AS i ON r.inventory_id = i.inventory_id JOIN film AS f ON i.film_id = f.film_id JOIN film_category AS fc ON f.film_id = fc.film_id JOIN category AS c ON fc.category_id = c.category_id:**
  - Joins the necessary tables to link payments to film categories.
- **GROUP BY c.category_id, c.name:**
  - Groups the results by category to aggregate revenue per genre.
- **ORDER BY total_revenue DESC LIMIT 5:**
  - Orders the genres by total revenue in descending order and limits the results to the top five.

*Note:* MySQL allows the use of `LIMIT` in views, but some SQL standards do not. If you encounter issues, consider creating the view without `LIMIT` and applying `LIMIT` in queries against the view.

---

### 20. **List the top five genres in gross revenue in descending order.**

Assuming you have created the view `top_five_genres_by_revenue` in the previous step, you can retrieve the top five genres as follows:

```sql
SELECT 
    genre, 
    total_revenue
FROM 
    top_five_genres_by_revenue;
```

**Explanation:**
- **SELECT genre, total_revenue FROM top_five_genres_by_revenue:**
  - Retrieves the `genre` and `total_revenue` columns from the view.
- **Ordering:** Since the view `top_five_genres_by_revenue` already orders the genres by `total_revenue` in descending order and limits to five records, this query will display the top five genres as intended.

*Alternative Approach:* If you prefer not to create a view, you can directly query as follows:

```sql
SELECT 
    c.name AS genre, 
    SUM(p.amount) AS total_revenue
FROM 
    payment AS p
JOIN 
    rental AS r 
    ON p.rental_id = r.rental_id
JOIN 
    inventory AS i 
    ON r.inventory_id = i.inventory_id
JOIN 
    film AS f 
    ON i.film_id = f.film_id
JOIN 
    film_category AS fc 
    ON f.film_id = fc.film_id
JOIN 
    category AS c 
    ON fc.category_id = c.category_id
GROUP BY 
    c.category_id, c.name
ORDER BY 
    total_revenue DESC
LIMIT 5;
```

---

### 21. **Write a query to display for each store its store ID, city, and country.**

```sql
SELECT 
    s.store_id, 
    ci.city, 
    co.country
FROM 
    store AS s
JOIN 
    address AS a 
    ON s.address_id = a.address_id
JOIN 
    city AS ci 
    ON a.city_id = ci.city_id
JOIN 
    country AS co 
    ON ci.country_id = co.country_id;
```

**Explanation:**
- **SELECT s.store_id, ci.city, co.country:**
  - Retrieves the `store_id`, `city`, and `country` for each store.
- **FROM store AS s:**
  - Specifies the `store` table with alias `s`.
- **JOIN address AS a ON s.address_id = a.address_id:**
  - Joins the `address` table to get address details of each store.
- **JOIN city AS ci ON a.city_id = ci.city_id:**
  - Joins the `city` table to get city names.
- **JOIN country AS co ON ci.country_id = co.country_id:**
  - Joins the `country` table to get country names.

*Optional Enhancement:* You can alias the columns for clearer output.

```sql
SELECT 
    s.store_id AS `Store ID`, 
    ci.city AS `City`, 
    co.country AS `Country`
FROM 
    store AS s
JOIN 
    address AS a 
    ON s.address_id = a.address_id
JOIN 
    city AS ci 
    ON a.city_id = ci.city_id
JOIN 
    country AS co 
    ON ci.country_id = co.country_id;
```

---

### 22. **Write a query to display how much business, in dollars, each store brought in.**

```sql
SELECT 
    s.store_id, 
    CONCAT(ci.city, ', ', co.country) AS store_location, 
    SUM(p.amount) AS total_business
FROM 
    store AS s
JOIN 
    inventory AS i 
    ON s.store_id = i.store_id
JOIN 
    rental AS r 
    ON i.inventory_id = r.inventory_id
JOIN 
    payment AS p 
    ON r.rental_id = p.rental_id
JOIN 
    address AS a 
    ON s.address_id = a.address_id
JOIN 
    city AS ci 
    ON a.city_id = ci.city_id
JOIN 
    country AS co 
    ON ci.country_id = co.country_id
GROUP BY 
    s.store_id, ci.city, co.country
ORDER BY 
    total_business DESC;
```

**Explanation:**
- **SELECT s.store_id, CONCAT(ci.city, ', ', co.country) AS store_location, SUM(p.amount) AS total_business:**
  - Retrieves the `store_id`.
  - Concatenates `city` and `country` into a single column named `store_location`.
  - Calculates the total business in dollars by summing the `amount` from payments, aliasing it as `total_business`.
- **FROM store AS s:**
  - Specifies the `store` table with alias `s`.
- **JOIN inventory AS i ON s.store_id = i.store_id:**
  - Joins the `inventory` table to link stores with their inventory items.
- **JOIN rental AS r ON i.inventory_id = r.inventory_id:**
  - Joins the `rental` table to associate rentals with inventory items.
- **JOIN payment AS p ON r.rental_id = p.rental_id:**
  - Joins the `payment` table to link payments to rentals.
- **JOIN address AS a ON s.address_id = a.address_id JOIN city AS ci ON a.city_id = ci.city_id JOIN country AS co ON ci.country_id = co.country_id:**
  - Joins `address`, `city`, and `country` tables to retrieve location details for each store.
- **GROUP BY s.store_id, ci.city, co.country:**
  - Groups the results by each store to aggregate the total business per store.
- **ORDER BY total_business DESC:**
  - Orders the stores by total business in descending order, showing the highest-grossing stores first.

*Alternative Approach Using Views:* If you have previously created a view like `sales_by_store`, you can simplify the query.

```sql
SELECT 
    store_id, 
    store, 
    total_sales AS total_business
FROM 
    sales_by_store
ORDER BY 
    total_business DESC;
```

*Note:* Replace `store`, `total_sales` with the actual column names from the `sales_by_store` view if they differ.
