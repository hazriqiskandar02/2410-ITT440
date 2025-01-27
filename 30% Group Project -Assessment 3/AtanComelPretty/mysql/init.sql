CREATE DATABASE IF NOT EXISTS testdb;
USE testdb;

CREATE TABLE user_points (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) NOT NULL,
    points INT NOT NULL DEFAULT 0,
    datetime_stamp DATETIME NOT NULL DEFAULT CURRENT_TIMESTAMP
);

INSERT INTO user_points (username, points) VALUES
    ('Atan_Comel', 30),
    ('Atan_Pretty', 40),
    ('Atan_Comel2', 50),
    ('Atan_Pretty2', 60),
    ('Atan_Comel3', 70),
    ('Atan_Pretty3', 80);
