--
-- Create database
--

DROP DATABASE lockrecv;
CREATE DATABASE lockrecv;
USE lockrecv;

--
-- Create the table children
--

CREATE TABLE children (
    childno INTEGER AUTO_INCREMENT NOT NULL PRIMARY KEY,
    fname varchar(30),
    age INTEGER
);

--
-- Populate the table 'children'
--

INSERT INTO children(fname, age) VALUES ('Jenny', 21);
INSERT INTO children(fname, age) VALUES ('Andrew', 17);
INSERT INTO children(fname, age) VALUES ('Gavin', 8);
INSERT INTO children(fname, age) VALUES ('Duncan', 6);
INSERT INTO children(fname, age) VALUES ('Emma', 4);
INSERT INTO children(fname, age) VALUES ('Alex', 15);
INSERT INTO children(fname, age) VALUES ('Adrian', 19);
