USE `scenario`;

# Table structure for table 'Users'
#
DROP TABLE IF EXISTS `SF_Users`;
CREATE TABLE `SF_Users` (`UserKey` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Name` VARCHAR(50) NOT NULL,
          `Description` VARCHAR(50),
          `UserPassword` VARCHAR(50) NOT NULL,
          `DisplayName` VARCHAR(50),
          `Email` VARCHAR(50));

# Dumping data for table 'Users'
#
LOCK TABLES `SF_Users` WRITE;
INSERT INTO `SF_Users` VALUES('scenario', 'Scenario User', 'Scenario Super-User.', 'scenario', 'Scenario Super-User', 'scenario@proandpro.it');
UNLOCK TABLES;

#
# Table structure for table 'Roles'
#
DROP TABLE IF EXISTS `SF_Roles`;
CREATE TABLE `SF_Roles` (`RoleKey` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Name` VARCHAR(50) NOT NULL,
          `Description` VARCHAR(50),
          `Users` TEXT);
#
# Dumping data for table 'Roles'
#
LOCK TABLES `SF_Roles` WRITE;
INSERT INTO `SF_Roles` VALUES('Administrator', 'Scenario Administrator', 'Scenario Administrator.', '<Users><User Key="scenario"></User></Users>');
UNLOCK TABLES;

#
# Table structure for table 'DataTypes'
#
DROP TABLE IF EXISTS `SF_DataTypes`;
CREATE TABLE `SF_DataTypes` (`DataTypeKey` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Type` VARCHAR(50) NOT NULL,
          `Description` VARCHAR(50),
          `Values` TEXT);
#
# Dumping data for table 'DataTypes'
#
LOCK TABLES `SF_DataTypes` WRITE;
INSERT INTO `SF_DataTypes` VALUES('0', 'STRING', 'StringType', '<EnumerationValues><Value Key="0"></Value></EnumerationValues>');
UNLOCK TABLES;

#
# Table structure for table 'Services'
#
DROP TABLE IF EXISTS `SF_Services`;
CREATE TABLE `SF_Services` (`Name` VARCHAR(50) NOT NULL PRIMARY KEY,
          `Workflow` VARCHAR(50),
          `Description` VARCHAR(50),
          `Users` TEXT,
          `Roles` TEXT,
          `ExtendedAttributes` TEXT);

#
# Dumping data for table 'Services'
#
LOCK TABLES `SF_Services` WRITE;
INSERT INTO `SF_Services` VALUES('Service1', 'Workflow1', 'Description1', '<Users><User Key="ddematteo"></User></Users>', '<Roles><Role Key="rolescenario"></Role></Roles>', '');
INSERT INTO `SF_Services` VALUES('Service2', 'Workflow2', 'Description2', '<Users><User Key="scenario"></User></Users>', '<Roles><Role Key="ScenarioUser"></Role></Roles>', '');
UNLOCK TABLES;

DROP TABLE IF EXISTS `SF_WorkflowProcesses`;
CREATE TABLE `SF_WorkflowProcesses` (`PROCESS_ID` INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
          `Name` VARCHAR(50) NOT NULL,
          `Status` VARCHAR(50),
          `Description` VARCHAR(50),
          `ParentProcess` INT default '0',
          `ActivityParentProcess` VARCHAR(50),
          `Exit2Manage` VARCHAR(50),
          `Transitions` TEXT,
          `MessageFlows` TEXT
          );


DROP TABLE IF EXISTS `SF_Activities`;
CREATE TABLE `SF_Activities` (
          `PROCESS_ID` INT NOT NULL,
          `ACTIVITY_ID` VARCHAR(50) NOT NULL,
          `Type` VARCHAR(50) NOT NULL,
          `Description` VARCHAR(50),
          `ReferenceActivity` VARCHAR(50),
          `Name` VARCHAR(50) NOT NULL,
          `Status` VARCHAR(50),
          `Owner` VARCHAR(50),
          `CatchType` VARCHAR(50),
          `NR_EXECUTED` INT NOT NULL default '0',
          `GRANTS` TEXT,
          `BEHAVIOUR` TEXT,
          `LOG` TEXT,
          `LOGS` TEXT,
          `REPORTS` TEXT,
          PRIMARY KEY `PrimaryKey` (`PROCESS_ID`,`ACTIVITY_ID`));

DROP TABLE IF EXISTS `SF_Attributes`;
CREATE TABLE `SF_Attributes` (
          `PROCESS_ID` INT NOT NULL,
          `ACTIVITY_ID` VARCHAR(50) NOT NULL default '0',
          `NAME` VARCHAR(50) NOT NULL,
          `DIRECTION` VARCHAR(50),
          `TYPE` VARCHAR(50),
          `VALUE` TEXT,
          PRIMARY KEY `PrimaryKey` (`PROCESS_ID`,`ACTIVITY_ID`,`Name`));

DROP TABLE IF EXISTS `SF_REPORTS`;
CREATE TABLE `SF_REPORTS` (
          `PROCESS_ID` INT NOT NULL,
          `DATE` VARCHAR(20),
          `DESCRIPTION` TEXT);


DROP TABLE IF EXISTS `SF_MESSAGEFLOWS`;
CREATE TABLE `SF_MESSAGEFLOWS` (
          `PROCESS_ID` INT NOT NULL,
          `ID` VARCHAR(20),
          `ObjectFROM` VARCHAR(20),
          `ObjectTO` VARCHAR(20),
          `ATTRIBUTES` TEXT);