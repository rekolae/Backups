-- Tietokantojen perusteet 2020
-- H1 T7
-- emil.rekola@tuni.fi

-- Create given movie table
CREATE TABLE movie (
    title VARCHAR (30),
    director VARCHAR(30),
    release_date date,
    PRIMARY KEY (title)
);

-- And insert data to the table
INSERT INTO movie
VALUES ('Jaws', 'Spielberg', '1975-12-19');  

INSERT INTO movie
VALUES ('Jurassic Park', 'Spielberg', '1993-09-03');  

INSERT INTO movie
VALUES ('2001: A Space Odyssey', 'Kubrick', '1968-09-20');

INSERT INTO movie
VALUES ('The Shining', 'Kubrick', '1980-09-26');


-- Update director entries where the director is "Kubric" with "Stanley"
UPDATE movie
SET director = 'Stanley'
WHERE director = 'Kubrick';