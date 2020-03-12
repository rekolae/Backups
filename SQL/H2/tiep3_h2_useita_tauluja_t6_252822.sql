-- Tietokantojen perusteet 2020
-- H2 T6
-- emil.rekola@tuni.fi

-- Select wanted information from different tables
SELECT DISTINCT aw.artwork_id, artwork_name

-- Link displayed_at table to artwork...
FROM displayed_at d
LEFT OUTER JOIN artwork aw
    ON d.artwork_id = aw.artwork_id
        
-- and exhibition tables
LEFT OUTER JOIN exhibition e
    ON d.exhibition_id = e.exhibition_id

-- Order the entries by artwork_id
ORDER BY aw.artwork_id;