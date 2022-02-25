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
)^_
INSERT OR IGNORE INTO user VALUES(1, 'admin', 'metro', 'metrologia@polatom.pl', NULL, 'Crystal', 'StarlingLab', 'Admin', NULL, 1, NULL, CURRENT_TIMESTAMP, 1)^_
CREATE TABLE IF NOT EXISTS crystalSettings (
	id	INTEGER,
	blank	INTEGER NOT NULL DEFAULT 60,
	source	INTEGER NOT NULL DEFAULT 300,
	repeat	INTEGER NOT NULL DEFAULT 10,
	deviceName	TEXT NOT NULL DEFAULT 'CmodS6',
	lastModification	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
INSERT OR IGNORE INTO crystalSettings(id) VALUES (1)^_
CREATE TABLE IF NOT EXISTS crystalProtocol (
	id	INTEGER,
	systemLabel	TEXT NOT NULL UNIQUE,
	anodeVoltage	TEXT NOT NULL DEFAULT 1000,
	thresholdVolatge	TEXT NOT NULL DEFAULT 2,
	extendableDeadTime	REAL NOT NULL DEFAULT 3,
	notes	TEXT,
	lastModification	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
INSERT OR IGNORE INTO crystalProtocol VALUES(1, 'A', 1000, 2, 3, NULL, CURRENT_TIMESTAMP, 1)^_
INSERT OR IGNORE INTO crystalProtocol VALUES(2, 'B', 1000, 2, 3, NULL, CURRENT_TIMESTAMP, 1)^_
INSERT OR IGNORE INTO crystalProtocol VALUES(3, 'C', 1000, 2, 3, NULL, CURRENT_TIMESTAMP, 1)^_
INSERT OR IGNORE INTO crystalProtocol VALUES(4, 'D', 1000, 2, 3, NULL, CURRENT_TIMESTAMP, 1)^_
CREATE TABLE IF NOT EXISTS crystalMeasurementProtocol (
	id	INTEGER,
	measurementId TEXT NOT NULL,
	anodeVoltage	TEXT NOT NULL DEFAULT 1000,
	thresholdVolatge	TEXT NOT NULL DEFAULT 2,
	extendableDeadTime	REAL NOT NULL DEFAULT 3,
	notes	TEXT,
	lastModification	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
CREATE TABLE IF NOT EXISTS crystalMeasurementRegister (
	id INTEGER,
	systemLabel TEXT NOT NULL,
	measurementId TEXT NOT NULL,
	measurementDate TEXT NOT NULL,
	nuclide TEXT NOT NULL,
	sourceId TEXT NOT NULL,
	sourceNo INTEGER NOT NULL,
	geometry TEXT NOT NULL,
	blankTime INTEGER NOT NULL,
	sourceTime INTEGER NOT NULL,
	repeat INTEGER NOT NULL,
	protocolId INTEGER NOT NULL,
	linked TEXT,
	category TEXT NOT NULL,
	comments TEXT,
	authorId INTEGER NOT NULL,
    acceptedId INTEGER DEFAULT 0,
    acceptedDateTime TEXT DEFAULT NULL,
	lastModification TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
CREATE TABLE IF NOT EXISTS crystalMeasurementRegisterCounter (
	year INTEGER,
	systemNumber TEXT,
	number INTEGER,
	PRIMARY KEY(systemNumber)
)^_
CREATE TABLE IF NOT EXISTS crystalMeasuringSystem (
	id INTEGER,
    numberA TEXT NOT NULL,
	numberB TEXT NOT NULL,
	numberC TEXT NOT NULL,
	numberD TEXT NOT NULL,
	name TEXT NOT NULL,
	fullName TEXT NOT NULL,
	measuremntProcedureName TEXT,
	location TEXT,
	notes TEXT,
	lastModification TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
INSERT OR IGNORE INTO crystalMeasuringSystem VALUES(1, '14.A', '14.B', '14.C', '14.D', 'Domki NaI', 'Układ z detektorem scyntylacyjnym NaI(Tl)', 'BW-PP-14: Pomiar aktywności promieniotwórczej w układach z detektorami scyntylacyjnymi NaI(Tl). Wyd. 7 z dn. 02.10.2019', 'Piwnica', NULL, CURRENT_TIMESTAMP, 1)^_
CREATE TABLE IF NOT EXISTS crystalMeasurementRAW (
	id INTEGER,
	measurementId INTEGER NOT NULL,
	startMeasurementDateTime TEXT NOT NULL,
	sourceNo INTEGER NOT NULL,
	pointTag TEXT NOT NULL,
	repeat INTEGER NOT NULL,
	counts INTEGER NOT NULL,
	liveTime INTEGER NOT NULL,
	realTime INTEGER NOT NULL,
	lastModification TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
CREATE TABLE IF NOT EXISTS labInfo (
	id INTEGER,
	institute TEXT,
	deparment TEXT,
	lab TEXT,
	addressLine1 TEXT,
	addressLine2 TEXT,
	zip TEXT,
	city TEXT,
	country TEXT,
	phone TEXT,
	email TEXT,
	lastModification TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
INSERT OR IGNORE INTO labInfo VALUES(1, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, CURRENT_TIMESTAMP, 1)^_
CREATE TABLE IF NOT EXISTS crystalLogbook (
	id INTEGER,
	type TEXT,
	description TEXT,
	root TEXT,
	element TEXT,
	lastModification TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
CREATE TRIGGER IF NOT EXISTS userInsert AFTER INSERT ON user
BEGIN
	INSERT INTO crystalLogbook VALUES(NULL, 'Add', 'Create new user', 'User', new.username, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS userUpdate AFTER UPDATE ON user
BEGIN
	INSERT INTO crystalLogbook VALUES(NULL, 'Modify', 'The following changes have been made:'||char(10)||
		iif(new.password<>old.password,' - Password was changed.','')||
		iif(new.degree<>old.degree,' - Degree from '||old.degree||' to '||new.degree||'.'||char(10),'')||
		iif(new.firstName<>old.firstName,' - First name from '||old.firstName||' to '||new.firstName||'.'||char(10),'')||
		iif(new.secondName<>old.secondName,' - Second name from '||old.secondName||' to '||new.secondName||'.'||char(10),'')||
		iif(new.lastName<>old.lastName,' - Second name from '||old.lastName||' to '||new.lastName||'.'||char(10),''),
		'User',new.username, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS measurementRegisterInsert AFTER INSERT ON crystalMeasurementRegister
BEGIN
	INSERT INTO crystalLogbook VALUES(NULL, 'Add', 'A new measurement has been added with the ID '||new.measurementId, 'Measurement', new.measurementId, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS measurementRegisterUpdate AFTER UPDATE ON crystalMeasurementRegister
BEGIN
	INSERT INTO crystalRegLogbook VALUES(NULL, 'Modify', 'The following changes have been made:'||char(10)||
		iif(new.nuclide<>old.nuclide,' - Nuclide from '||old.nuclide||' to '||new.nuclide||'.'||char(10),'')||
		iif(new.geometry<>old.geometry,' - Geometry from '||old.geometry||' to '||new.geometry||'.'||char(10),'')||
		iif(new.sourceId<>old.sourceId,' - Source ID from '||old.sourceId||' to '||new.sourceId||'.'||char(10),'')||
		iif(new.linked<>old.linked,' - Linked from '||old.linked||' to '||new.linked||'.'||char(10),'')||
		iif(new.category<>old.category,' - Category from '||old.category||' to '||new.category||'.'||char(10),'')||
		iif(new.comments<>old.comments,' - Comments from '||old.comments||' to '||new.comments||'.'||char(10),'')||
		iif(new.acceptedId=0,' - Acceptance of the measurement has been revoked.'||char(10),' - The measurement was accepted on '||new.acceptedDateTime),
		'Measurement',new.measurementId, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS protocolUpdate AFTER UPDATE ON crystalProtocol
BEGIN
	INSERT INTO crystalLogbook VALUES(NULL, 'Modify', 'The following changes have been made:'||char(10)||
		iif(new.anodeVoltage<>old.anodeVoltage,' - Anode voltage from '||old.anodeVoltage||' to '||new.anodeVoltage||'.'||char(10),'')||
		iif(new.thresholdVolatge<>old.thresholdVolatge,' - Threshold voltage from '||old.thresholdVolatge||' to '||new.thresholdVolatge||'.'||char(10),'')||
		iif(new.extendableDeadTime<>old.extendableDeadTime,' - Dead-time from '||old.extendableDeadTime||' to '||new.extendableDeadTime||'.'||char(10),'')||
		iif(new.notes<>old.notes,' - Notes from '||old.notes||' to '||new.notes||'.'||char(10),''),
		'Protocol',new.systemLabel, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS measurementProtocolUpdate AFTER UPDATE ON crystalMeasurementProtocol
BEGIN
	INSERT INTO crystalLogbook VALUES(NULL, 'Modify',
		iif(new.notes<>old.notes,'Modified protocol notes in the measurement '||old.measurementId||' from '||old.notes||' to '||new.notes||'.'||char(10),''),
		'Measurement',old.measurementId, CURRENT_TIMESTAMP, new.userId);
END^_