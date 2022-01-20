CREATE TABLE IF NOT EXISTS auditLog (
	id	INTEGER,
	tableName	TEXT NOT NULL,
	rowId	INTEGER NOT NULL,
	type	INTEGER NOT NULL,
	timestamp	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	data	TEXT NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
);
CREATE TABLE IF NOT EXISTS users (
	id	INTEGER,
	username	TEXT NOT NULL UNIQUE,
	password	TEXT NOT NULL,
	isActive	INTEGER DEFAULT 1,
	firstName	TEXT,
	secondName	TEXT,
	lastName	TEXT,
	timestamp	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
);
INSERT OR IGNORE INTO users VALUES(NULL, 'admin', 'metro', 1, 'Admin', NULL, 'StarlingLab', CURRENT_TIMESTAMP, 1);
CREATE TRIGGER IF NOT EXISTS usersInsert AFTER INSERT ON users
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'users', new.id, 1, CURRENT_TIMESTAMP, new.userId);
	END;
CREATE TRIGGER IF NOT EXISTS usersUpdate AFTER UPDATE ON users
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'users', old.id, 0, CURRENT_TIMESTAMP,
			iif(new.id<>lod.id,new.id,'')||'|'||
			iif(new.username<>old.username,new.username,'')||'|'||
			iif(new.password<>old.password,new.password,'')||'|'||
			iif(new.isActive<>old.isActive,new.isActive,'')||'|'||
			iif(new.firstName<>old.firstName,new.firstName,'')||'|'||
			iif(new.secondName<>old.secondName,new.secondName,'')||'|'||
			iif(new.lastName<>old.lastName,new.lastName,'')||'|'||
			iif(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iif(new.userId<>old.userId,new.userId,''));
	END;
CREATE TRIGGER IF NOT EXISTS usersDelete AFTER DELETE ON users
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'users', old.id, -1, CURRENT_TIMESTAMP,old.userId);
	END;
CREATE TABLE IF NOT EXISTS settingGeneral (
	id	INTEGER,
	blankTime	INTEGER DEFAULT 60,
	sourceTime	INTEGER DEFAULT 300,
	repeated	INTEGER DEFAULT 10,
	delayedStart	INTEGER DEFAULT 5,
	voltageMax	INTEGER DEFAULT 2300,
	amperMax	INTEGER DEFAULT 3000,
	timestamp	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY("id" AUTOINCREMENT)
);
INSERT OR IGNORE INTO settingGeneral(id) VALUES (1);
CREATE TRIGGER IF NOT EXISTS settingGeneralUpdate AFTER UPDATE ON settingGeneral
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'settingGeneral', old.id, 0, CURRENT_TIMESTAMP,
			iif(new.id<>lod.id,new.id,'')||'|'||
			iif(new.blankTime<>old.blankTime,new.blankTime,'')||'|'||
			iif(new.sourceTime<>old.sourceTime,new.sourceTime,'')||'|'||
			iif(new.repeated<>old.repeated,new.repeated,'')||'|'||
			iif(new.delayedStart<>old.delayedStart,new.delayedStart,'')||'|'||
			iif(new.voltageMax<>old.voltageMax,new.voltageMax,'')||'|'||
			iif(new.amperMax<>old.amperMax,new.amperMax,'')||'|'||
			iif(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iif(new.userId<>old.userId,new.userId,''));
	END;
CREATE TABLE IF NOT EXISTS settingConnection (
	id	INTEGER,
	port	TEXT DEFAULT 'COM1',
	baudRate	TEXT DEFAULT 9600,
	lBusAddress	INTEGER DEFAULT 0,
	deviceName	TEXT DEFAULT 'CmodS6',
	isExtClk	INTEGER DEFAULT 0,
	timestamp	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(id AUTOINCREMENT)
);
INSERT OR IGNORE INTO settingConnection(id) VALUES (1);
CREATE TRIGGER IF NOT EXISTS settingConnectionUpdate AFTER UPDATE ON settingConnection
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'settingConnection', old.id, 0, CURRENT_TIMESTAMP,
			iif(new.id<>old.id,new.id,'')||'|'||
			iif(new.port<>old.port,new.port,'')||'|'||
			iif(new.baudRate<>old.baudRate,new.baudRate,'')||'|'||
			iif(new.lBusAddress<>old.lBusAddress,new.lBusAddress,'')||'|'||
			iif(new.deviceName<>old.deviceName,new.deviceName,'')||'|'||
			iif(new.isExtClk<>old.isExtClk,new.isExtClk,'')||'|'||
			iif(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iif(new.userId<>old.userId,new.userId,''));
	END;
CREATE TABLE IF NOT EXISTS tdkLog (
	id	INTEGER,
	creationDateTime	TEXT DEFAULT CURRENT_TIMESTAMP,
	nuclide	TEXT,
	solution	TEXT,
	noSources	INTEGER,
	sourceId	TEXT,
	sourcePreparationDate	TEXT,
	description	TEXT,
	linked	TEXT,
	madeByUserId	INTEGER NOT NULL,
	status	INTEGER NOT NULL,
	category	INTEGER NOT NULL,
	protocolId	INTEGER,
	timestamp	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
);
CREATE TRIGGER IF NOT EXISTS tdkLogInsert AFTER INSERT ON tdkLog
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'tdkLog', new.id, 1, CURRENT_TIMESTAMP, new.userId);
	END;
CREATE TRIGGER IF NOT EXISTS tdkLogUpdate AFTER UPDATE ON tdkLog
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'tdkLog', old.id, 0, CURRENT_TIMESTAMP,
			iif(new.id<>old.id,new.id,'')||'|'||
			iif(new.creationDateTime<>old.creationDateTime,new.creationDateTime,'')||'|'||
			iif(new.nuclide<>old.nuclide,new.nuclide,'')||'|'||
			iif(new.solution<>old.solution,new.solution,'')||'|'||
			iif(new.noSources<>old.noSources,new.noSources,'')||'|'||
			iif(new.sourceId<>old.sourceId,new.sourceId,'')||'|'||
			iif(new.sourcePreparationDate<>old.sourcePreparationDate,new.sourcePreparationDate,'')||'|'||
			iif(new.description<>old.description,new.description,'')||'|'||
			iif(new.linked<>old.linked,new.linked,'')||'|'||
			iif(new.madeByUserId<>old.madeByUserId,new.madeByUserId,'')||'|'||
			iif(new.status<>old.status,new.status,'')||'|'||
			iif(new.category<>old.category,new.category,'')||'|'||
			iif(new.protocolId<>old.protocolId,new.protocolId,'')||'|'||
			iif(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iif(new.userId<>old.userId,new.userId,''));
	END;
CREATE TRIGGER IF NOT EXISTS tdkLogDelete AFTER DELETE ON tdkLog
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'tdkLog', old.id, -1, CURRENT_TIMESTAMP,old.userId);
	END;
CREATE TABLE IF NOT EXISTS protocol (
	id	INTEGER,
	name	TEXT NOT NULL UNIQUE,
	anodaVoltage	TEXT NOT NULL,
	shiftA	INTEGER NOT NULL,
	shiftB	INTEGER NOT NULL,
	shiftC	INTEGER NOT NULL,
	focusingVoltage	TEXT NOT NULL,
	resolvingTime	INTEGER NOT NULL,
	deadTime	INTEGER NOT NULL,
	thrA	REAL NOT NULL,
	thrB	REAL NOT NULL,
	thrC	REAL NOT NULL,
	description	TEXT,
	timestamp	TEXT NOT NULL DEFAULT CURRENT_TIMESTAMP,
	userId	INTEGER NOT NULL,
	PRIMARY KEY(id AUTOINCREMENT)
);
CREATE TRIGGER IF NOT EXISTS protocolInsert AFTER INSERT ON protocol
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'protocol', new.id, 1, CURRENT_TIMESTAMP, new.userId);
	END;
CREATE TRIGGER IF NOT EXISTS protocolUpdate AFTER UPDATE ON protocol
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'protocol', old.id, 0, CURRENT_TIMESTAMP,
			iif(new.id<>old.id,new.id,'')||'|'||
			iif(new.name<>old.name,new.name,'')||'|'||
			iif(new.anodaVoltage<>old.anodaVoltage,new.anodaVoltage,'')||'|'||
			iif(new.shiftA<>old.shiftA,new.shiftA,'')||'|'||
			iif(new.shiftB<>old.shiftB,new.shiftB,'')||'|'||
			iif(new.shiftC<>old.shiftC,new.shiftC,'')||'|'||
			iif(new.focusingVoltage<>old.focusingVoltage,new.focusingVoltage,'')||'|'||
			iif(new.resolvingTime<>old.resolvingTime,new.resolvingTime,'')||'|'||
			iif(new.deadTime<>old.deadTime,new.deadTime,'')||'|'||
			iif(new.thrA<>old.thrA,new.thrA,'')||'|'||
			iif(new.thrB<>old.thrB,new.thrB,'')||'|'||
			iif(new.thrC<>old.thrC,new.thrC,'')||'|'||
			iif(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iif(new.userId<>old.userId,new.userId,''));
	END;
CREATE TRIGGER IF NOT EXISTS protocolDelete AFTER DELETE ON protocol
	BEGIN
		INSERT INTO auditLog VALUES(NULL, 'protocol', old.id, -1, CURRENT_TIMESTAMP,old.userId);
	END;
CREATE TABLE IF NOT EXISTS measurementRAW (
	id	INTEGER,
	tdkLogId	INTEGER,
	startMeasurementDateTime	TEXT,
	sampleNumber	INTEGER,
	tag	TEXT,
	repeatNumber	INTEGER,
	A	INTEGER,
	B	INTEGER,
	C	INTEGER,
	S	INTEGER,
	AB	INTEGER,
	BC	INTEGER,
	AC	INTEGER,
	T	INTEGER,
	D	INTEGER,
	LT	INTEGER,
	CLK_IN	INTEGER,
	ch0	REAL,
	ch1	REAL,
	ch2	REAL,
	ch3	REAL,
	timestamp	TEXT,
	userId	INTEGER,
	PRIMARY KEY(id AUTOINCREMENT)
)