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
			iff(new.username<>old.username,new.username,'')||'|'||
			iff(new.password<>old.password,new.password,'')||'|'||
			iff(new.isActive<>old.isActive,new.isActive,'')||'|'||
			iff(new.firstName<>old.firstName,new.firstName,'')||'|'||
			iff(new.secondName<>old.secondName,new.secondName,'')||'|'||
			iff(new.lastName<>old.lastName,new.lastName,'')||'|'||
			iff(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iff(new.userId<>old.userId,new.userId,''));
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
			iff(new.blankTime<>old.blankTime,new.blankTime,'')||'|'||
			iff(new.sourceTime<>old.sourceTime,new.sourceTime,'')||'|'||
			iff(new.repeated<>old.repeated,new.repeated,'')||'|'||
			iff(new.delayedStart<>old.delayedStart,new.delayedStart,'')||'|'||
			iff(new.voltageMax<>old.voltageMax,new.voltageMax,'')||'|'||
			iff(new.amperMax<>old.amperMax,new.amperMax,'')||'|'||
			iff(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iff(new.userId<>old.userId,new.userId,''));
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
			iif(new.id<>lod.id,new.id,'')||'|'||
			iff(new.port<>old.port,new.port,'')||'|'||
			iff(new.baudRate<>old.baudRate,new.baudRate,'')||'|'||
			iff(new.lBusAddress<>old.lBusAddress,new.lBusAddress,'')||'|'||
			iff(new.deviceName<>old.deviceName,new.deviceName,'')||'|'||
			iff(new.isExtClk<>old.isExtClk,new.isExtClk,'')||'|'||
			iff(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iff(new.userId<>old.userId,new.userId,''));
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
			iif(new.id<>lod.id,new.id,'')||'|'||
			iff(new.creationDateTime<>old.creationDateTime,new.creationDateTime,'')||'|'||
			iff(new.nuclide<>old.nuclide,new.nuclide,'')||'|'||
			iff(new.solution<>old.solution,new.solution,'')||'|'||
			iff(new.noSources<>old.noSources,new.noSources,'')||'|'||
			iff(new.sourceId<>old.sourceId,new.sourceId,'')||'|'||
			iff(new.sourcePreparationDate<>old.sourcePreparationDate,new.sourcePreparationDate,'')||'|'||
			iff(new.description<>old.description,new.description,'')||'|'||
			iff(new.linked<>old.linked,new.linked,'')||'|'||
			iff(new.madeByUserId<>old.madeByUserId,new.madeByUserId,'')||'|'||
			iff(new.status<>old.status,new.status,'')||'|'||
			iff(new.category<>old.category,new.category,'')||'|'||
			iff(new.protocolId<>old.protocolId,new.protocolId,'')||'|'||
			iff(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iff(new.userId<>old.userId,new.userId,''));
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
			iif(new.id<>lod.id,new.id,'')||'|'||
			iff(new.name<>old.name,new.name,'')||'|'||
			iff(new.anodaVoltage<>old.anodaVoltage,new.anodaVoltage,'')||'|'||
			iff(new.shiftA<>old.shiftA,new.shiftA,'')||'|'||
			iff(new.shiftB<>old.shiftB,new.shiftB,'')||'|'||
			iff(new.shiftC<>old.shiftC,new.shiftC,'')||'|'||
			iff(new.focusingVoltage<>old.focusingVoltage,new.focusingVoltage,'')||'|'||
			iff(new.resolvingTime<>old.resolvingTime,new.resolvingTime,'')||'|'||
			iff(new.deadTime<>old.deadTime,new.deadTime,'')||'|'||
			iff(new.thrA<>old.thrA,new.thrA,'')||'|'||
			iff(new.thrB<>old.thrB,new.thrB,'')||'|'||
			iff(new.thrC<>old.thrC,new.thrC,'')||'|'||
			iff(new.timestamp<>old.timestamp,new.timestamp,'')||'|'||
			iff(new.userId<>old.userId,new.userId,''));
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