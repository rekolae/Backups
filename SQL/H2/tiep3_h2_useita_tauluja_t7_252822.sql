-- Tietokantojen perusteet 2020
-- H2 T7
-- emil.rekola@tuni.fi

-- Select wanted information from different tables
SELECT first_name, last_name, a.artist_id, aw.artwork_id, artwork_name

-- Set artist table as the left table and link it to artwork
FROM artist a
LEFT OUTER JOIN artwork aw
    ON a.artist_id = aw.artist_id

-- Order the entries by artwork_id
ORDER BY a.artist_id, aw.artwork_id;