CREATE DATABASE logistics_db;
USE logistics_db;

CREATE TABLE items (
    item_id INT PRIMARY KEY AUTO_INCREMENT,
    item_type VARCHAR(30) NOT NULL,
    weight DOUBLE NOT NULL,
    is_fragile BOOLEAN NOT NULL,
    status VARCHAR(30) NOT NULL,
    sorting_line VARCHAR(30) NOT NULL,
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE items;