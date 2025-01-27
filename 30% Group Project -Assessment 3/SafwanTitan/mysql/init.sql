-- Create users table
CREATE TABLE IF NOT EXISTS users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(50) NOT NULL,
    role ENUM('student', 'teacher', 'admin') NOT NULL,
    points INT DEFAULT 0
);

-- Insert initial data
INSERT INTO users (username, role, points) VALUES ('student1', 'student', 0);
INSERT INTO users (username, role, points) VALUES ('teacher1', 'teacher', 0);
INSERT INTO users (username, role, points) VALUES ('admin1', 'admin', 0);