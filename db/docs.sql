# -----------------------------------------------------------------------------------------------------
# таблицы для справочника должностей


CREATE TABLE "group_position" (
    "id"	INTEGER PRIMARY KEY AUTOINCREMENT,
    "name" TEXT NOT NULL,
    "level"  INT NOT NULL
);
CREATE UNIQUE INDEX "group_position_name_IDX" ON "group_position" ("name");
CREATE UNIQUE INDEX "group_position_level_IDX" ON "group_position" ("level");

CREATE TABLE "position" (
    "id"	INTEGER PRIMARY KEY AUTOINCREMENT,
    "name" TEXT NOT NULL,
    "group_id"  INT,
    CONSTRAINT position_group_id_FK FOREIGN KEY (group_id) REFERENCES group_position(id)
);
CREATE UNIQUE INDEX "position_name_IDX" ON "position" ("name");

CREATE TABLE "tmp_pos" (
    "name" TEXT PRIMARY KEY
);

# -----------------------------------------------------------------------------------------------

# таблицы хранение органиизационной структуры

CREATE TABLE "org" (
    "id"	INTEGER PRIMARY KEY AUTOINCREMENT,
    "code" TEXT NOT NULL,
    "name"  TEXT NOT NULL,
    "parent_id" INT,
    "created_at" TEXT NOT NULL DEFAULT (datetime('now','localtime')),
    "closed_at" TEXT
);
CREATE UNIQUE INDEX "org_name_IDX" ON "org" ("name", "created_at");

CREATE TABLE tree_path (
	"parent_id" INTEGER NOT NULL,
	"child_id" INTEGER NOT NULL,
	PRIMARY KEY (parent_id, child_id),
	CONSTRAINT tree_path_parent_id_FK FOREIGN KEY (parent_id) REFERENCES org(id)
	CONSTRAINT tree_path_child_id_FK FOREIGN KEY (child_id) REFERENCES org(id)
);
# ------------------------------------------------------------------------------------------------------------------

# таблицы для хранения персональных данных
# центральное лицо

CREATE TABLE "face" (
    "id"	INTEGER PRIMARY KEY AUTOINCREMENT,
    "snils" TEXT NOT NULL,
    "birthday"  TEXT NOT NULL
);
CREATE UNIQUE INDEX "face_snils_IDX" ON "face" ("snils");

CREATE TABLE "tmp_face" (
    "snils" TEXT PRIMARY KEY,
    "birthday"  TEXT NOT NULL,
    "tn"	INTEGER NOT NULL,
    "firstname"	TEXT NOT NULL,
	"name"	TEXT NOT NULL,
	"fathername" TEXT,
	"org_name" TEXT NOT NULL,
	"position" TEXT NOT NULL
);

# ------------------------------------------------------------------------------------------------------------------

CREATE TABLE "pd" (
	"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"face_id" INT NOT NULL,
	"firstname"	TEXT NOT NULL,
	"name"	TEXT NOT NULL,
	"fathername" TEXT,
	"created_at" TEXT NOT NULL DEFAULT (datetime('now','localtime')),
	"closed_at" TEXT,
	CONSTRAINT pd_face_id_FK FOREIGN KEY (face_id) REFERENCES face(id)
);
# -----------------------------------------------------------------------------------------------------------------
CREATE TABLE "shtat" (
	"id"	INTEGER PRIMARY KEY AUTOINCREMENT,
	"org_id" INT NOT NULL,
	"pos_id" INT NOT NULL,
	"tn" INT NOT NULL,
	"pd_id" INT NOT NULL,
	"created_at" TEXT NOT NULL DEFAULT (datetime('now','localtime')),
	"closed_at" TEXT,
	CONSTRAINT shtat_org_id_FK FOREIGN KEY (org_id) REFERENCES org(id),
	CONSTRAINT shtat_pos_id_FK FOREIGN KEY (pos_id) REFERENCES "position(id)",
	CONSTRAINT shtat_pd_id_FK FOREIGN KEY (pd_id) REFERENCES pg(id)
);
CREATE UNIQUE INDEX "pd_data_IDX" ON shtat (org_id, pos_id, tn, pd_id) ;

# -----------------------------------------------------------------------------------------------------------------


CREATE VIEW org_view AS
    SELECT o.id, o.name, "Chief name", o.parent_id
    FROM org o
    WHERE o.closed_at is NULL;