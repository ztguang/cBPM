DROP TABLE IF EXISTS `SF_Users`;
CREATE TABLE `SF_Users` (`UserKey` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Name` TEXT(50) NOT NULL,
          `Description` TEXT(50),
          `UserPassword` TEXT(50) NOT NULL,
          `DisplayName` TEXT(50),
          `Email` TEXT(50));

DROP TABLE IF EXISTS `SF_Roles`;
CREATE TABLE `SF_Roles` (`RoleKey` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Name` TEXT(50) NOT NULL,
          `Description` TEXT(50),
          `Users` BLOB);

DROP TABLE IF EXISTS `SF_DataTypes`;
CREATE TABLE `SF_DataTypes` (`DataTypeKey` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Type` TEXT(50) NOT NULL,
          `Description` TEXT(50),
          `Values` BLOB);

DROP TABLE IF EXISTS `SF_Services`;
CREATE TABLE `SF_Services` (`Name` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Workflow` TEXT(50),
          `Description` TEXT(50),
          `Users` BLOB,
          `Roles` BLOB,
          `ExtendedAttributes` BLOB);

DROP TABLE IF EXISTS "SF_WorkflowProcesses";
CREATE TABLE "SF_WorkflowProcesses" (
	"PROCESS_ID"  TEXT(50) NOT NULL,
	"Name"  TEXT(50) NOT NULL,
	"Status"  TEXT(50),
	"Description"  TEXT(50),
	"ParentProcess"  TEXT(50) DEFAULT '',
	"ActivityParentProcess"  TEXT(50),
	"Completed"  TEXT(50),
	"Created"  TEXT(50),
	"Exit2Manage"  TEXT(50),
	"Transitions"  BLOB,
	"MessageFlows"  BLOB,
	PRIMARY KEY ("PROCESS_ID")
);


DROP TABLE IF EXISTS `SF_Activities`;
CREATE TABLE `SF_Activities` (
          `PROCESS_ID` TEXT(50) NOT NULL,
          `ACTIVITY_ID` TEXT(50) NOT NULL,
          `Type` TEXT(50) NOT NULL,
          `Description` TEXT(50),
          `ReferenceActivity` TEXT(50),
          `Name` TEXT(50) NOT NULL,
          `Status` TEXT(50),
          `Owner` TEXT(50),
          `CatchType` TEXT(50),
          `NR_EXECUTED` INTEGER NOT NULL default '0',
          `GRANTS` BLOB,
          `BEHAVIOUR` BLOB,
          `LOG` BLOB,
          `LOGS` BLOB,
          `REPORTS` BLOB);

DROP TABLE IF EXISTS `SF_Attributes`;
CREATE TABLE `SF_Attributes` (
          `PROCESS_ID` TEXT(50) NOT NULL,
          `ACTIVITY_ID` TEXT(50) NOT NULL default '0',
          `NAME` TEXT(50) NOT NULL,
          `DIRECTION` TEXT(50),
          `TYPE` TEXT(50),
          `VALUE` BLOB);

DROP TABLE IF EXISTS `SF_REPORTS`;
CREATE TABLE `SF_REPORTS` (
          `PROCESS_ID` TEXT(50) NOT NULL,
          `DATE` TEXT(20),
          `DESCRIPTION` BLOB);


DROP TABLE IF EXISTS `SF_MESSAGEFLOWS`;
CREATE TABLE `SF_MESSAGEFLOWS` (
          `PROCESS_ID` TEXT(50) NOT NULL,
          `ID` TEXT(20),
          `ObjectFROM` TEXT(20),
          `ObjectTO` TEXT(20),
          `ATTRIBUTES` BLOB);

DROP VIEW IF EXISTS `BAM_Activity`;
CREATE VIEW `BAM_Activity` AS
  SELECT
  a.PROCESS_ID as ProcessId,
  a.ACTIVITY_ID,
  a.Type,
  a.Description,
  a.ReferenceActivity,
  a.Name,
  a.Status,
  a.Owner,
  a.CatchType,
  a.NR_EXECUTED,
  a.GRANTS,
  a.BEHAVIOUR,
  a.LOG,
  a.LOGS,
  a.REPORTS,
  w.Name as ProcessName
  FROM  sf_activities a,
        sf_workflowprocesses w
where a.process_id=w.process_id;