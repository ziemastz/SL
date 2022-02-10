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
INSERT OR IGNORE INTO user VALUES(1, 'admin', 'metro', 'metrologia@polatom.pl', NULL, 'Admin', NULL, 'StarlingLab', NULL, 1, NULL, CURRENT_TIMESTAMP, 1)^_
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
)^_
INSERT OR IGNORE INTO tripleRegSettings(id) VALUES (1)^_
CREATE TABLE IF NOT EXISTS tripleRegProtocol (
	id	INTEGER,
	name	TEXT NOT NULL UNIQUE DEFAULT 'Default',
	anodeVoltage	TEXT NOT NULL DEFAULT 2000,
	voltageShiftA	INTEGER NOT NULL DEFAULT 0,
	voltageShiftB	INTEGER NOT NULL DEFAULT 0,
	voltageShiftC	INTEGER NOT NULL DEFAULT 0,
	focusingVoltage	TEXT NOT NULL DEFAULT 660,
	resolvingTime	INTEGER NOT NULL DEFAULT 40,
	deadTime	INTEGER NOT NULL DEFAULT 30,
	thrA	REAL NOT NULL DEFAULT 0.1,
	thrB	REAL NOT NULL DEFAULT 0.1,
	thrC	REAL NOT NULL DEFAULT 0.1,
	notes	TEXT,
	lastModification	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
INSERT OR IGNORE INTO tripleRegProtocol(id) VALUES (1)^_
CREATE TABLE IF NOT EXISTS tripleRegMeasurementProtocol (
	id	INTEGER,
	name	TEXT NOT NULL DEFAULT 'Default',
	anodeVoltage	TEXT NOT NULL DEFAULT 2000,
	voltageShiftA	INTEGER NOT NULL DEFAULT 0,
	voltageShiftB	INTEGER NOT NULL DEFAULT 0,
	voltageShiftC	INTEGER NOT NULL DEFAULT 0,
	focusingVoltage	TEXT NOT NULL DEFAULT 660,
	resolvingTime	INTEGER NOT NULL DEFAULT 40,
	deadTime	INTEGER NOT NULL DEFAULT 30,
	thrA	REAL NOT NULL DEFAULT 0.1,
	thrB	REAL NOT NULL DEFAULT 0.1,
	thrC	REAL NOT NULL DEFAULT 0.1,
	notes	TEXT,
	lastModification	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
CREATE TABLE IF NOT EXISTS tripleRegMeasurementRegister (
	id INTEGER,
	measurementId TEXT NOT NULL,
	measurementDate TEXT NOT NULL,
	nuclide TEXT NOT NULL,
	solutionId TEXT,
	sourceId TEXT NOT NULL,
	sourceNo INTEGER NOT NULL,
	isBlank INTEGER NOT NULL,
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
CREATE TABLE IF NOT EXISTS tripleRegMeasurementRegisterCounter (
	year INTEGER,
	number INTEGER,
	PRIMARY KEY(year)
)^_
CREATE TABLE IF NOT EXISTS tripleRegMeasuringSystem (
	id INTEGER,
	number INTEGER NOT NULL UNIQUE,
	name TEXT NOT NULL,
	fullName TEXT NOT NULL,
	measuremntProcedureName TEXT,
	location TEXT,
	isDefault INTEGER NOT NULL,
	notes TEXT,
	lastModification TEXT NOT NULL,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
)^_
INSERT OR IGNORE INTO tripleRegMeasuringSystem VALUES(1, 1, 'TDK', 'Układ potrójno–podwójnych koincydencji TDK', 'BW-PP-1: Pomiar aktywności promieniotwórczej radionuklidów metodą potrójno-podwójnych koincydencji TDK. Wyd. 7 z dn. 02.10.2019', '4C', 1, NULL, CURRENT_TIMESTAMP, 1)^_
CREATE TABLE IF NOT EXISTS tripleRegMeasurementRAW (
	id INTEGER,
	measurementId INTEGER NOT NULL,
	startMeasurementDateTime TEXT NOT NULL,
	sourceNo INTEGER NOT NULL,
	pointTag TEXT NOT NULL,
	repeat INTEGER NOT NULL,
	A INTEGER NOT NULL,
	B INTEGER NOT NULL,
	C INTEGER NOT NULL,
	S INTEGER NOT NULL,
	AB INTEGER NOT NULL,
	BC INTEGER NOT NULL,
	AC INTEGER NOT NULL,
	T INTEGER NOT NULL,
	D INTEGER NOT NULL,
	LT INTEGER NOT NULL,
	CLK_IN INTEGER NOT NULL,
	voltageCh0 REAL NOT NULL,
	voltageCh1 REAL NOT NULL,
	voltageCh2 REAL NOT NULL,
	voltageCh3 REAL NOT NULL,
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
CREATE TABLE IF NOT EXISTS tripleRegLogbook (
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
	INSERT INTO tripleRegLogbook VALUES(NULL, 'Add', 'Create new user', 'User', new.username, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS userUpdate AFTER UPDATE ON user
BEGIN
	INSERT INTO tripleRegLogbook VALUES(NULL, 'Modify', 'The following changes have been made:'||char(10)||
		iif(new.password<>old.password,' - Password was changed.','')||
		iif(new.degree<>old.degree,' - Degree from '||old.degree||' to '||new.degree||'.'||char(10),'')||
		iif(new.firstName<>old.firstName,' - First name from '||old.firstName||' to '||new.firstName||'.'||char(10),'')||
		iif(new.secondName<>old.secondName,' - Second name from '||old.secondName||' to '||new.secondName||'.'||char(10),'')||
		iif(new.lastName<>old.lastName,' - Second name from '||old.lastName||' to '||new.lastName||'.'||char(10),''),
		'User',new.username, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS measurementRegisterInsert AFTER INSERT ON tripleRegMeasurementRegister
BEGIN
	INSERT INTO tripleRegLogbook VALUES(NULL, 'Add', 'A new measurement has been added with the ID '||new.measurementId, 'Measurement', new.measurementId, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS measurementRegisterUpdate AFTER UPDATE ON tripleRegMeasurementRegister
BEGIN
	INSERT INTO tripleRegLogbook VALUES(NULL, 'Modify', 'The following changes have been made:'||char(10)||
		iif(new.nuclide<>old.nuclide,' - Nuclide from '||old.nuclide||' to '||new.nuclide||'.'||char(10),'')||
		iif(new.solutionId<>old.solutionId,' - Solution ID from '||old.solutionId||' to '||new.solutionId||'.'||char(10),'')||
		iif(new.sourceId<>old.sourceId,' - Source ID name from '||old.sourceId||' to '||new.sourceId||'.'||char(10),'')||
		iif(new.linked<>old.linked,' - Linked from '||old.linked||' to '||new.linked||'.'||char(10),'')||
		iif(new.category<>old.category,' - Category from '||old.category||' to '||new.category||'.'||char(10),''),
		'Measurement',new.measurementId, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS protocolInsert AFTER INSERT ON tripleRegProtocol
BEGIN
	INSERT INTO tripleRegLogbook VALUES(NULL, 'Add', 'A new measurement protocol was created with the name '||new.name, 'Protocol', new.name, CURRENT_TIMESTAMP, new.userId);
END^_
CREATE TRIGGER IF NOT EXISTS protocolUpdate AFTER UPDATE ON tripleRegProtocol
BEGIN
	INSERT INTO tripleRegLogbook VALUES(NULL, 'Modify', 'The following changes have been made:'||char(10)||
		iif(new.nuclide<>old.nuclide,' - Nuclide from '||old.nuclide||' to '||new.nuclide||'.'||char(10),'')||
		iif(new.solutionId<>old.solutionId,' - Solution ID from '||old.solutionId||' to '||new.solutionId||'.'||char(10),'')||
		iif(new.sourceId<>old.sourceId,' - Source ID name from '||old.sourceId||' to '||new.sourceId||'.'||char(10),'')||
		iif(new.linked<>old.linked,' - Linked from '||old.linked||' to '||new.linked||'.'||char(10),'')||
		iif(new.category<>old.category,' - Category from '||old.category||' to '||new.category||'.'||char(10),''),
		'Measurement',new.measurementId, CURRENT_TIMESTAMP, new.userId);
END^_