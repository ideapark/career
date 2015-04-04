--
-- create database
--

DROP DATABASE lockrecv;
CREATE DATABASE lockrecv;
USE lockrecv;

--
-- create table
--

CREATE TABLE cd (
    id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY,
    title VARCHAR(70) NOT NULL,
    artist_id INTEGER NOT NULL,
    catalogue VARCHAR(30) NOT NULL,
    notes VARCHAR(100)
);

CREATE TABLE artist (
    id INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

CREATE TABLE track (
    cd_id INTEGER NOT NULL,
    track_id INTEGER NOT NULL,
    title VARCHAR(70),
    PRIMARY KEY(cd_id, track_Id)
);

--
-- preparing test data
--

-- populate the cd
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(1, 'Dark Side of the Moon', 1, 'B000024D4P');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(2, 'Wish You Were Here', 1, 'B000024D4S');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(3, 'A Trick of the Tail', 2, 'B000024EXM');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(4, 'Selling England By the Pound', 2, 'B000024E9M');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(5, 'I Giorni', 3, 'B000071WEV');
INSERT INTO cd(id, title, artist_id, catalogue) VALUES(6, 'Northern Star', 4, 'B00004YMST');

-- populate artist
INSERT INTO artist(id, name) VALUES(1, 'Pink Floyd');
INSERT INTO artist(id, name) VALUES(2, 'Genesis');
INSERT INTO artist(id, name) VALUES(3, 'Einaudi');
INSERT INTO artist(id, name) VALUES(4, 'Melanie C');

-- populate track
INSERT INTO track(cd_id, track_id, title) VALUES(1, 1, 'Speak to me');
INSERT INTO track(cd_id, track_id, title) VALUES(1, 2, 'Breathe');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 1, 'Shine on you crazy diamond');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 2, 'Welcome to the machine');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 3, 'Have a cigar');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 4, 'Wish you were here');
INSERT INTO track(cd_id, track_id, title) VALUES(2, 5, 'Shine on you crazy diamond pt.2');
INSERT INTO track(cd_id, track_id, title) VALUES(5, 1, 'Melodia Africana (part 1)');
INSERT INTO track(cd_id, track_id, title) VALUES(5, 2, 'I due fiumi');
INSERT INTO track(cd_id, track_id, title) VALUES(5, 3, 'In um\'altra vita');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 11, 'Closer');
INSERT INTO track(cd_id, track_id, title) VALUES(6, 12, 'Feel The Sun');
