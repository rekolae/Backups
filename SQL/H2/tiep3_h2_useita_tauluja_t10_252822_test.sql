-- Tietokantojen perusteet 2020
-- H2 T10
-- emil.rekola@tuni.fi

SELECT m.title, first_name, last_name, character_name, release_date

FROM acts_in acts
LEFT OUTER JOIN actor a
    ON acts.actor_id = a.actor_id

LEFT OUTER JOIN movie m
    ON acts.title = m.title
    
WHERE first_name = 'Brad';
