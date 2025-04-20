CREATE TABLE "pd" (
    "id"	INTEGER PRIMARY KEY AUTOINCREMENT,
    "name"  TEXT NOT NULL
);
CREATE UNIQUE INDEX "name_IDX" ON "pd" ("name"); 

INSERT INTO pd(name) values('Фамилия, Имя, Отчество'); 
INSERT INTO pd(name) values('Дата рождения'); 
INSERT INTO pd(name) values('Место рождения'); 
INSERT INTO pd(name) values('Гражданство'); 
