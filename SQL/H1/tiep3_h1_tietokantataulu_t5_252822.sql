-- Tietokantojen perusteet 2020
-- H1 T5
-- emil.rekola@tuni.fi

-- Select title and release_date columns from movies that 
-- were released after 1980-01-01 and set ascending order
SELECT title, release_date FROM movie
WHERE release_date > "1980-01-01"
ORDER BY release_date;