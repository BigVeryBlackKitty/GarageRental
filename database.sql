-- database.sql
-- Удаляем старые таблицы
DROP TABLE IF EXISTS Payment;
DROP TABLE IF EXISTS Lease_Agreement;
DROP TABLE IF EXISTS Garage;
DROP TABLE IF EXISTS Tenant;

-- Арендатор
CREATE TABLE IF NOT EXISTS "Tenant" (
	"id" INTEGER PRIMARY KEY AUTOINCREMENT,
	"surname" VARCHAR NOT NULL,
	"name" VARCHAR NOT NULL,
	"patronymic" VARCHAR,
	"phone_num" VARCHAR NOT NULL,
	"email" VARCHAR,
	"isOverdue" INTEGER DEFAULT 0,
	"created_at" DATE DEFAULT CURRENT_DATE
);

-- Гараж
CREATE TABLE IF NOT EXISTS "Garage" (
	"id" INTEGER PRIMARY KEY AUTOINCREMENT,
	"personal_numbers" VARCHAR UNIQUE NOT NULL,
	"location" VARCHAR,
	"width_garage" REAL,
	"height_garage" REAL,
	"status_garage" INTEGER DEFAULT 1,
	"created_at" DATE DEFAULT CURRENT_DATE
);

-- Договор аренды
CREATE TABLE IF NOT EXISTS "Lease_Agreement" (
	"id" INTEGER PRIMARY KEY AUTOINCREMENT,
	"personal_numbers" VARCHAR UNIQUE NOT NULL,
	"tenant_id" INTEGER NOT NULL,
	"garage_id" INTEGER NOT NULL,
	"start_date" DATE NOT NULL,
	"end_date" DATE NOT NULL,
	"monthly_price" REAL NOT NULL,
	"total_amount" REAL NOT NULL,
	"status" INTEGER DEFAULT 1,
	"created_at" DATE DEFAULT CURRENT_DATE,
	FOREIGN KEY ("tenant_id") REFERENCES "Tenant"("id"),
	FOREIGN KEY ("garage_id") REFERENCES "Garage"("id")
);

-- Платеж
CREATE TABLE IF NOT EXISTS "Payment" (
	"id" INTEGER PRIMARY KEY AUTOINCREMENT,
	"receipt_number" VARCHAR,
	"payer_id" INTEGER,
	"agreement_id" INTEGER,
	"payment_amount" REAL,
	"payment_date" DATE DEFAULT CURRENT_DATE,
	"payment_type" INTEGER DEFAULT 1,
	"status_payment" INTEGER DEFAULT 1,
	FOREIGN KEY ("payer_id") REFERENCES "Tenant"("id"),
	FOREIGN KEY ("agreement_id") REFERENCES "Lease_Agreement"("id")
);

-- Индексы
CREATE INDEX idx_agreement_tenant ON Lease_Agreement(tenant_id);
CREATE INDEX idx_agreement_garage ON Lease_Agreement(garage_id);
CREATE INDEX idx_payment_agreement ON Payment(agreement_id);
CREATE INDEX idx_payment_payer ON Payment(payer_id);

-- Тестовые данные
INSERT INTO Tenant (surname, name, patronymic, phone_num, email) VALUES
('Иванов', 'Иван', 'Иванович', '+7-999-123-45-67', 'ivan@mail.ru'),
('Петров', 'Петр', 'Петрович', '+7-999-234-56-78', 'petr@mail.ru'),
('Сидоров', 'Сидор', 'Сидорович', '+7-999-345-67-89', 'sidor@mail.ru');

INSERT INTO Garage (personal_numbers, location, width_garage, height_garage, status_garage) VALUES
('A-01', 'Секция А, место 1', 3.5, 2.5, 1),
('A-02', 'Секция А, место 2', 3.5, 2.5, 1),
('B-01', 'Секция Б, место 1', 4.0, 3.0, 1),
('B-02', 'Секция Б, место 2', 4.0, 3.0, 1),
('C-01', 'Секция С, место 1', 5.0, 4.0, 1);