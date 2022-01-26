CREATE TABLE IF NOT EXISTS user (
	id	INTEGER NOT NULL,
	username	TEXT NOT NULL UNIQUE,
	password	TEXT NOT NULL,
	email	TEXT NOT NULL,
	degree	TEXT,
	firstName	TEXT NOT NULL,
	secondName	TEXT,
	lastName	TEXT NOT NULL,
	position	TEXT,
	isActive	INTEGER NOT NULL DEFAULT 1,
	signature	BLOB,
	lastModification	TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
);
INSERT OR IGNORE INTO user VALUES(NULL, 'admin', 'metro', 'metrologia@polatom.pl', NULL, 'Admin', NULL, 'StarlingLab', NULL, 1, NULL, CURRENT_TIMESTAMP, 1);
CREATE TABLE IF NOT EXISTS tripleRegSettings (
	id	INTEGER,
	blank	INTEGER NOT NULL DEFAULT 60,
	source	INTEGER NOT NULL DEFAULT 300,
	repeat	INTEGER NOT NULL DEFAULT 10,
	startDelay	INTEGER NOT NULL DEFAULT 5,
	maxVoltage	INTEGER NOT NULL DEFAULT 2200,
	port	TEXT NOT NULL DEFAULT 'COM1',
	usbBaudRate	TEXT NOT NULL DEFAULT '9600',
	lBusAddress	INTEGER NOT NULL DEFAULT 0,
	deviceName	TEXT NOT NULL DEFAULT 'CmodS6',
	isExtClkIn	INTEGER NOT NULL DEFAULT 0,
	lastModification	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
);
INSERT OR IGNORE INTO tripleRegSettings(id) VALUES (1);