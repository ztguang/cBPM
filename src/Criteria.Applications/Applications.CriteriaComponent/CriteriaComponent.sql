USE `scenario`;

# Table structure for table 'ProcessMasterSlave'
#
DROP TABLE IF EXISTS `ProcessMasterSlave`;
CREATE TABLE `ProcessMasterSlave` (`IdMaster` VARCHAR(50) NOT NULL,
					`IdSlave` INT default '0',
					`IsBusy` INT default '0');
														