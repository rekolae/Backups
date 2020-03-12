-- Tietokantojen perusteet 2020
-- H2 T2
-- emil.rekola@tuni.fi

-- Select wanted columns from the tables where the wanted information exists
-- using left outer join and matching the artist_id
SELECT artwork_id, artwork_name, first_name, last_name, year_created
FROM artwork LEFT OUTER JOIN artist
ON artwork.artist_id = artist.artist_id
ORDER BY artwork_id;