# iot-miniproject-logistics-sorting-2026
IoT 첫번째 미니프로젝트 2026

## 물류 자동 분류 시뮬레이터
C++ 기반의 객체지향 설계와 MySQL 연동을 활용하여
물류 자동 분류 시스템의 전체 흐름을 시뮬레이션한 프로젝트입니다.

물품 생성 → 큐 적재 → 분류 → 유효성 검사 → DB 저장 → 통계 조회까지
하나의 흐름으로 통합 구현하였습니다.

## 프로젝트 개요
이 프로젝트는 단순한 기능 구현이 아닌,
객체지향 설계 + 데이터 흐름 + DB 연동을 하나의 시스템으로 구성하는 것을 목표로 합니다.

특히 다음과 같은 흐름을 중심으로 설계되었습니다

Item 생성 → Queue 적재 → 처리 → 분류 → 저장 → 조회

## 주요 기능

### 1. 물품 생성 (Factory 기반 구조)
- ItemFactory를 통해 객체 생성 책임 분리
- 랜덤 타입 / 무게 / 속성 생성
- Food, Electronics, Fragile 다형성 활용

### 2. 컨베이어 시스템 (Queue 기반 처리)
- std::queue를 활용한 FIFO 구조
- 상태 변화 관리 (Queued → Processing)
- 안전한 포인터 관리 (shared_ptr)

### 3. 자동 분류 로직
- 속성 기반 분류 시스템 구현
- dynamic_pointer_cast 활용한 타입 판별
- 분류 기준
    - Fragile → FragileLine
    - Fragile 속성 → CautionLine
    - Weight < 5kg → SmallLine
    - 그 외 → LargeLine

### 4. 유효성 검사
- 공통 유효성: 타입, 무게 검증
- 타입별 유효성 확장 가능 구조
- 잘못된 데이터는 DB 저장 차단

### 5. MySQL 연동
- MySQL Connector/C++ 사용
- PreparedStatement 기반 안전한 INSERT
- UTC → KST 시간 변환 처리

### 6. 통계 및 조회 기능
- 통계 조회
    - 라인별 개수
    - 타입별 개수
    - 라인별 평균 무게

- 조건 기반 조회
    - 특정 라인 물품 조회
    - 무게 상위 N개 조회
    - 최근 저장된 데이터 조회

- 조회 결과는 구조체로 반환 후 출력 분리:
    - std::vector<LineStatistic>
    - std::vector<ItemRecord>

### 7. 출력 로직 분리 (설계 개선)
- DB 조회와 출력 로직 분리
- ReportPrinter에서 출력 담당

### 8. 자동 실행 + 사용자 인터랙션
- 자동 사이클: 물품 생성 → 처리 → 저장 반복
- 인터랙티브 모드
    - Enter → 다음 사이클 실행
    - m → 관리자 메뉴
    - q → 종료
- 콘솔 UI 개선 (\r 기반 출력 덮어쓰기)

### 9. 관리자 메뉴 시스템
- Admin Menu
    - Statistics
    - Query Results
- 입력 오류 처리 (cin fail 대응)
- 입력 버퍼 관리
- 화면 초기화 및 UX 개선

## 설계 특징

### 1. 객체지향 설계 (OOP)
- 상속: Item → Food / Electronics / Fragile
- 다형성: showInfo(), isValid()
- 캡슐화: 상태 관리 및 접근 제어

### 2. 역할 분리 (Separation of Concerns)

|역할|클래스|
|:--|:--|
|객체 생성|ItemFactory|
|데이터 흐름|ConveyorSystem|
|분류 로직|Sorter|
|DB 처리|DatabaseManager|
|출력|ReportPrinter|
|전체 흐름|LogisticsService|

### 3. Factory 패턴 (부분 적용)
- 객체 생성 로직 캡슐화
- 확장 가능 구조

### 4. Service 계층 구조
- main → LogisticsService → DatabaseManager

### 5. 안전한 입력 처리
- cin.fail() 처리
- 입력 버퍼 정리
- 잘못된 입력 방어 로직

## 실행 흐름

===== Auto Cycle #1 =====
[CREATE]
[ENQUEUE]
[PROCESS]
[SORT]
[VALID]
[SAVE]

Press Enter to continue, [m] for menu, [q] to quit:

## 기술 스택

- Language: C++
- Database: MySQL
- Library
    - MySQL Connector/C++
    - STL (queue, vector, smart pointer)
    - Environment: Visual Studio

## 프로젝트 구조

- Item / Food / Electronics / Fragile
- ItemFactory
- ConveyorSystem
- Sorter
- DatabaseManager
- ReportPrinter
- LogisticsService
- main.cpp

## 프로젝트 목적

- 객체지향 설계 실전 적용
- 데이터 흐름 기반 시스템 설계 경험
- C++ + DB 연동 경험 확보
- 단순 기능이 아닌 “하나의 시스템” 구현

## 향후 개선 방향

- 멀티스레드 기반 실시간 처리
- 로그 시스템 분리 (Logger 클래스)
- GUI 적용 (Qt 또는 WinAPI)
- REST API 서버 확장

## 한 줄 요약

C++ 객체지향 설계와 MySQL 연동을 통해 물류 처리 시스템의 전체 흐름을 구현한 콘솔 기반 시뮬레이션 프로젝트