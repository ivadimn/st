CREATE TABLE users(id SERIAL PRIMARY KEY, name TEXT NOT NULL, email TEXT NOT NULL, balance INTEGER NOT NULL);

DROP TABLE users;

CREATE EXTENSION IF NOT EXISTS "uuid-ossp";

CREATE TABLE users(pid SERIAL PRIMARY KEY, name TEXT NOT NULL, user_id UUID NOT NULL DEFAULT uuid_generate_v4(),
email TEXT NOT NULL, balance INTEGER NOT NULL, registration TIMESTAMP NOT NULL DEFAULT now());

SELECT uuid_generate_v4(); 

INSERT INTO users(name, email, balance) VALUES('Jerry Kinn', 'jkinn@gmail.com', 1000);
INSERT INTO users(name, email, balance) VALUES('Adam Smith', 'asmith@gmail.com', 1000);
INSERT INTO users(name, email, balance) VALUES('Billy Jonnes', 'bjonnes@gmail.com', 1000);

ALTER TABLE users ALTER COLUMN balance SET DEFAULT 0;

INSERT INTO users(name, email) VALUES('Marina Longdale', 'mlongdale@gmail.com');

ALTER TABLE users ADD CHECK(balance >= 0);
ALTER TABLE users ADD CHECK(length(name) <=100);
ALTER TABLE users ADD CHECK(length(email) <=100);

ALTER TABLE users ADD COLUMN enabled BOOLEAN NOT NULL DEFAULT true;

ALTER TABLE users DROP COLUMN enabled;

UPDATE users SET balance = balance + 100 WHERE pid = 2;

UPDATE users SET balance = balance + 100 WHERE user_id = '2e3277f0-501b-4698-a64a-89ae5f4afc53';

UPDATE users SET balance = balance + 10;
UPDATE users SET balance = balance - 100;

UPDATE users SET balance = balance + 100 WHERE balance < 100;