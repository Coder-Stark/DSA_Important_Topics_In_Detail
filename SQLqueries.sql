-- Querying Bollywood movies
SELECT title, industry FROM movies WHERE industry = 'Bollywood';
-- Output:
-- | title | industry |
-- |-------|----------|
-- | 3 Idiots | Bollywood |
-- | Dangal | Bollywood |
-- | RRR | Bollywood |

-- Count Bollywood movies
SELECT COUNT(*) FROM movies WHERE industry = 'Bollywood';
-- Output: 3

-- Select distinct industries
SELECT DISTINCT industry FROM movies;
-- Output:
-- | industry |
-- |----------|
-- | Hollywood |
-- | Bollywood |

-- Find movies with 'Thor' in the title
SELECT * FROM movies WHERE title LIKE '%Thor%';
-- Output:
-- | movie_id | title | industry | studio | imdb_rating | release_year |
-- |----------|-------------|------------|---------------|--------------|--------------|
-- | 1 | Thor: Ragnarok | Hollywood | Marvel Studios | 7.9 | 2017 |


SELECT * FROM movies;

SELECT * FROM movies WHERE studio = "";

SELECT * FROM movies WHERE imdb_rating >= 9;

SELECT * FROM movies WHERE imdb_rating >= 7 AND imdb_rating <= 9;

SELECT * FROM movies WHERE imdb_rating BETWEEN 7 AND 9;       -- include both 7 and 9

SELECT * FROM movies WHERE release_year = 2022 OR release_year = 2019;

SELECT * FROM movies WHERE release_year IN(2022, 2019, 2018);

SELECT * FROM movies WHERE studio IN("Marvel Studios", "Zee Studios");

SELECT * FROM movies WHERE imdb_rating IS NULL;

SELECT * FROM movies WHERE imdb_rating IS NOT NULL;

SELECT * FROM movies WHERE industry = "bollywood" ORDER BY imdb_rating;  -- by defalut ascending

SELECT * FROM movies WHERE industry = "bollywood" ORDER BY imdb_rating DESC;

SELECT * FROM movies WHERE industry = "bollywood" ORDER BY imdb_rating DESC LIMIT 5;             -- not = only 5

SELECT * FROM movies WHERE industry = "bollywood" ORDER BY imdb_rating DESC LIMIT 5 OFFSET 1;     -- ignore top(offset val) element or push ans by offset val

SELECT MAX(imdb_rating) FROM movies WHERE industry = "hollywood";        -- same MIN()

SELECT AVG(imdb_rating) FROM movies WHERE industry = "bollywood";         -- 7.68235

SELECT ROUND(AVG(imdb_rating), 2) FROM movies WHERE industry = "bollywood";   -- 7.68

SELECT MIN(imdb_rating) as minRating, MAX(imdb_rating) as maxRating, ROUND(AVG(imdb_rating),2) as avgRating FROM movies;

SELECT studio, COUNT(*) FROM movies GROUP BY studio;

SELECT studio, COUNT(*) as cnt FROM movies GROUP BY studio ORDER BY cnt DESC;

SELECT studio, COUNT(*) as cnt, ROUND(AVG(imdb_rating), 2) as avgRating FROM movies GROUP BY studio ORDER BY avgRating DESC;

SELECT release_year, COUNT(*) AS moviesCount FROM movies GROUP BY release_year ORDER BY moviesCount DESC;

 X  SELECT release_year, COUNT(*) AS moviesCount FROM movies WHERE moviesCount > 2 GROUP BY release_year ORDER BY moviesCount DESC;
-- FROM --> WHERE --> GROUP BY --> HAVING --> ORDER BY                 -- where cant use to filter out due to its execution place

SELECT release_year, COUNT(*) AS moviesCount FROM movies GROUP BY release_year HAVING moviesCount > 2 ORDER BY moviesCount DESC;

/* same as just above query
SELECT release_year, COUNT(*) AS moviesCount    -- in having's statement cmd should present in select statement
FROM movies 
GROUP BY release_year                        -- having is mainly used with group by
HAVING moviesCount > 2                       -- having COLUMN should present in select clause
ORDER BY moviesCount DESC;
*/

SELECT CURDATE();

SELECT YEAR(CURDATE());


ACTOR 
SELECT *, YEAR(CURDATE())-birth_year as age FROM actors;

FINANCE TABLE
SELECT * FROM financials;

SELECT *, (revenue-budget) as profit FROM financials;

-- INR TO USD 
SELECT *, IF(currency = 'USD', revenue * 80, revenue) as revenueINR FROM financials;

SELECT DISTINCT unit FROM financials;

-- BILLIONS -> 1000 MILLION, 1 THOUNSANDS -> 1000 / MILLIONS

/*
SELECT *,
CASE
	WHEN unit = 'Billions' THEN revenue * 1000
    WHEN unit = 'Thousands'THEN revenue / 1000
    WHEN unit = 'Millions' THEN revenue
    ELSE revenue
END as revenueMill 
FROM financials;
*/

-- JOINS
SELECT * FROM movies;

SELECT movies.movie_id, title, budget, revenue, currency, unit
FROM movies JOIN financials
ON movies.movie_id = financials.movie_id;


--   same as above just movies ==> m
-- JOIN(BY DEFAULT INNER JOIN) (INERSECTION)
SELECT m.movie_id, title, budget, revenue, currency, unit
FROM movies m JOIN financials f                      --by default INNER JOIN (ONLY TAKES WHOSE INTERSECTION(COMMON IN BOTH) ELSE IGNORE)
ON m.movie_id = f.movie_id;

-- LEFT JOIN (INTERSECTION + LEFT PART)
SELECT m.movie_id, title, budget, revenue, currency, unit
FROM movies m LEFT JOIN financials f
ON m.movie_id = f.movie_id;

-- RIGHT JOIN (INTERSECTION + RIGHT PART)
SELECT f.movie_id, title, budget, revenue, currency, unit    --f. (otherwise null cause title empty in movie)
FROM movies m RIGHT JOIN financials f
ON m.movie_id = f.movie_id;


-- FULL JOIN USING UNION (LEFT + INTERSECTION + RIGHT)
SELECT m.movie_id, title, budget, revenue, currency, unit
FROM movies m LEFT JOIN financials f
ON m.movie_id = f.movie_id
UNION                                                          --all left + intersection + right (col name should same)  
SELECT f.movie_id, title, budget, revenue, currency, unit      --f. (otherwise null cause title empty in movie)
FROM movies m RIGHT JOIN financials f
ON m.movie_id = f.movie_id;

-- OUTER JOIN => LEFT, RIGHT, FULL (ALL CALLED OUTER JOIN EXCEPT INNER JOIN)

-- USING
SELECT m.movie_id, title, budget, revenue, currency, unit
FROM movies m LEFT JOIN financials f
ON m.movie_id = f.movie_id
UNION                                                           --all left + intersection + right (col name should same)  
SELECT f.movie_id, title, budget, revenue, currency, unit       --f. (otherwise null cause title empty in movie)
FROM movies m RIGHT JOIN financials f
USING (movie_id);               -- movie id is same in both movie and financial table

-- WE CAN ADD MULTIPLE ATTRIBUTE OR JOIN USING 2 COL USING MULTIPLE ATTRIBUTE IN A BRACKET ();


-- QUESTIONS

