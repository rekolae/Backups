-- Tietokantojen perusteet 2020
-- H2 T9
-- emil.rekola@tuni.fi

-- Select wanted information from different tables
SELECT aw.artwork_id, aw.artwork_name

-- Set artwork table as the left table and link it to displayed_at...
FROM artwork aw
LEFT OUTER JOIN displayed_at d
    ON aw.artwork_id = d.artwork_id
        
        -- which in turn is linked to exhibition
        LEFT OUTER JOIN exhibition e
            ON d.exhibition_id = e.exhibition_id

-- Filter entries which have not been in any exhibition (so exhibition_id is NULL)
WHERE e.exhibition_id IS NULL

-- Order the entries by artwork_id
ORDER BY aw.artwork_id;