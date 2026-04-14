CREATE DATABASE logistics_db;
USE logistics_db;

CREATE TABLE items (
    item_id INT PRIMARY KEY AUTO_INCREMENT,
    item_type VARCHAR(30) NOT NULL,
    weight DOUBLE NOT NULL,
    is_fragile BOOLEAN NOT NULL,
    status VARCHAR(30) NOT NULL,
    sorting_line VARCHAR(30) NOT NULL,
    saved_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
);

DROP TABLE items;

-- 라인별 개수 조회
SELECT sorting_line, COUNT(sorting_line)
  FROM items
 GROUP BY sorting_line;

-- 타입별 개수 조회
SELECT item_type, COUNT(item_type)
  FROM items
 GROUP BY item_type;

-- 라인별 평균 무게 조회
SELECT sorting_line, AVG(weight)
  FROM items
 GROUP BY sorting_line;

-- 특정 라인에 배정된 물품만 조회
SELECT item_type, weight, is_fragile
	 , status, sorting_line
	 , CONVERT_TZ(saved_at, '+00:00', '+09:00')
  FROM items
 WHERE sorting_line = 'LargeLine'
 ORDER BY saved_at DESC;

-- Top N 조회
SELECT item_type, weight, sorting_line
	 , CONVERT_TZ(saved_at, '+00:00', '+09:00')
  FROM items
 ORDER BY weight DESC
 LIMIT 5;

-- 최근 저장된 물품 조회
SELECT item_type, weight, sorting_line, status
	 , CONVERT_TZ(saved_at, '+00:00', '+09:00')
  FROM items
 ORDER BY saved_at DESC
 LIMIT 3;