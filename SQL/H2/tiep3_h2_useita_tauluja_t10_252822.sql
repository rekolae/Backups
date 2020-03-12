-- Tietokantojen perusteet 2020
-- H2 T10
-- emil.rekola@tuni.fi

-- Create the movie table and insert movie data
CREATE TABLE movie (
    title VARCHAR (30),
    director VARCHAR(30),
    release_date date,
    PRIMARY KEY (title)
);

-- Given movies
INSERT INTO movie
VALUES ('Jaws', 'Spielberg', '1975-12-19');

INSERT INTO movie
VALUES ('Jurassic Park', 'Spielberg', '1993-09-03');

INSERT INTO movie
VALUES ('2001: A Space Odyssey', 'Kubrick', '1968-09-20');

INSERT INTO movie
VALUES ('The Shining', 'Kubrick', '1980-09-26');

-- Self added movies
INSERT INTO movie
VALUES ('Django unchained', 'Tarantino', '2013-01-18');

INSERT INTO movie
VALUES ('Inglourious Basterds', 'Tarantino', '2009-08-20');

INSERT INTO movie
VALUES ('Terminator', 'Cameron', '1984-10-26');

INSERT INTO movie
VALUES ('Jingle All the Way', 'Levant', '1996-11-22');

INSERT INTO movie
VALUES ('Kindergarten Cop', 'Reitman', '1990-12-21');

INSERT INTO movie
VALUES ('Once Upon a Time in Hollywood', 'Tarantino', '2019-07-26');


-- Create a table for actors
CREATE TABLE actor (
    actor_id INT,
    first_name VARCHAR(30) NOT NULL,
    last_name VARCHAR(30) NOT NULL,
    PRIMARY KEY (actor_id),
    UNIQUE (actor_id)
);

-- Actors from Jaws
INSERT INTO actor
VALUES (1, 'Roy', 'Scheider');

INSERT INTO actor
VALUES (2, 'Robert', 'Shaw');

INSERT INTO actor
VALUES (3, 'Richard', 'Dreyfuss');

INSERT INTO actor
VALUES (4, 'Susan', 'Backlinie');

INSERT INTO actor
VALUES (5, 'Bruce', 'The Shark');


-- Actors from Jurassic Park
INSERT INTO actor
VALUES (6, 'Sam', 'Neill');

INSERT INTO actor
VALUES (7, 'Laura', 'Dern');

INSERT INTO actor
VALUES (8, 'Jeff', 'Goldblum');

INSERT INTO actor
VALUES (9, 'Roberta', 'The T-Rex');


-- Actors from 2001: A Space Odyssey
INSERT INTO actor
VALUES (10, 'Keir', 'Dullea');

INSERT INTO actor
VALUES (11, 'Gary', 'Lockwood');

INSERT INTO actor
VALUES (12, 'Daniel', 'Richter');


-- Actors from The Shining
INSERT INTO actor
VALUES (13, 'Jack', 'Nicholson');

INSERT INTO actor
VALUES (14, 'Shelley', 'Duvall');

INSERT INTO actor
VALUES (15, 'Danny', 'Lloyd');

INSERT INTO actor
VALUES (16, 'Scatman', 'Crothers');


-- Actors from various self added movies
INSERT INTO actor
VALUES (17, 'Jamie', 'Foxx');

INSERT INTO actor
VALUES (18, 'Christoph', 'Waltz');

INSERT INTO actor
VALUES (19, 'Leonardo', 'DiCaprio');

INSERT INTO actor
VALUES (20, 'Arnold', 'Schwarzenegger');

INSERT INTO actor
VALUES (21, 'Brad', 'Pitt');

INSERT INTO actor
VALUES (22, 'Margot', 'Robbie');


-- Create a table for linking actors and movies
CREATE TABLE acts_in (
    actor_id INT,
    title VARCHAR (30),
    character_name VARCHAR (30),
    PRIMARY KEY (actor_id, title),
    FOREIGN KEY (actor_id) REFERENCES actor(actor_id),
    FOREIGN KEY (title) REFERENCES movie(title)
);

INSERT INTO acts_in
VALUES (1, 'Jaws', 'Roy Scheider');

INSERT INTO acts_in
VALUES (2, 'Jaws', 'Quint');

INSERT INTO acts_in
VALUES (3, 'Jaws', 'Hooper');

INSERT INTO acts_in
VALUES (4, 'Jaws', 'Chrissie');

INSERT INTO acts_in
VALUES (5, 'Jaws', 'Great White Shark');


INSERT INTO acts_in
VALUES (6, 'Jurassic Park', 'Grant');

INSERT INTO acts_in
VALUES (7, 'Jurassic Park', 'Ellie');

INSERT INTO acts_in
VALUES (8, 'Jurassic Park', 'Malcom');

INSERT INTO acts_in
VALUES (9, 'Jurassic Park', 'Tyrannosaurus Rex');


INSERT INTO acts_in
VALUES (10, '2001: A Space Odyssey', 'Dr. David Bowman');

INSERT INTO acts_in
VALUES (11, '2001: A Space Odyssey', 'Dr. Frank Poole');

INSERT INTO acts_in
VALUES (12, '2001: A Space Odyssey', 'Chief Man-Ape');


INSERT INTO acts_in
VALUES (13, 'The Shining', 'Jack Torrance');

INSERT INTO acts_in
VALUES (14, 'The Shining', 'Wendy Torrance');

INSERT INTO acts_in
VALUES (15, 'The Shining', 'Danny Torrance');

INSERT INTO acts_in
VALUES (16, 'The Shining', 'Dick Hallorann');


INSERT INTO acts_in
VALUES (17, 'Django unchained', 'Django Freeman');

INSERT INTO acts_in
VALUES (18, 'Django unchained', 'Dr. King Schultz');

INSERT INTO acts_in
VALUES (19, 'Django unchained', 'Calvin J. Candie');


INSERT INTO acts_in
VALUES (21, 'Inglourious Basterds', 'Aldo "The Apache" Raine');

INSERT INTO acts_in
VALUES (18, 'Inglourious Basterds', 'Standartenführer Hans Landa');


INSERT INTO acts_in
VALUES (20, 'Terminator', 'T-800');


INSERT INTO acts_in
VALUES (20, 'Jingle All the Way', 'Howard Langston');


INSERT INTO acts_in
VALUES (20, 'Kindergarten Cop', 'Detective John Kimble');


INSERT INTO acts_in
VALUES (19, 'Once Upon a Time in Hollywood', 'Rick Dalton');

INSERT INTO acts_in
VALUES (21, 'Once Upon a Time in Hollywood', 'Cliff Booth');

INSERT INTO acts_in
VALUES (22, 'Once Upon a Time in Hollywood', 'Sharon Tate');
