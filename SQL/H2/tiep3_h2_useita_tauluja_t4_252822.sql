-- Tietokantojen perusteet 2020
-- H2 T4
-- emil.rekola@tuni.fi

-- Select wanted information from different tables
SELECT year, exhibition_name, first_name, last_name, artwork_name

-- Link displayed_at table to exhibition and artwork tables
FROM displayed_at d
LEFT OUTER JOIN artwork aw
    ON d.artwork_id = aw.artwork_id
        
        -- Link artwork and artist tables by artist_id
        LEFT OUTER JOIN artist a
            ON aw.artist_id = a.artist_id

LEFT OUTER JOIN exhibition e
    ON d.exhibition_id = e.exhibition_id
    
-- Order the entries with the given priorities
ORDER BY year, last_name, aw.artwork_id;