
# mysql -uroot -p criteria < dm_mysql.sql

DROP TABLE IF EXISTS `dm_id_instances`;
CREATE TABLE `dm_id_instances` (
  `Id_instance` varchar(50) NOT NULL default '',
  `counter` int(6) unsigned NOT NULL default '0',
  `year` int(4) unsigned NOT NULL default '0',
  PRIMARY KEY (`Id_instance`)
) ENGINE=MyISAM;

DROP TABLE IF EXISTS `dm_idinstances_to_recycle`;
CREATE TABLE `dm_idinstances_to_recycle` (
  `id_instance` varchar(50) NOT NULL default '',
  `id_num` int(11) NOT NULL default '1',
  `recycled` enum('true','false') default 'false',
  PRIMARY KEY  (`id_instance`,`id_num`)
) ENGINE=MyISAM;

DROP TABLE IF EXISTS `dm_documents`;
CREATE TABLE `dm_documents` (
  `Id` varchar(50) NOT NULL default '',
  `Type` varchar(20) default NULL,
  `Name` varchar(50) default NULL,
  `Creation_policy` varchar(20) default NULL,
  `Manage_version` varchar(20) default NULL,
  `IdMaster` varchar(50) default NULL,
  `Version_Master` varchar(20) default NULL,
  `LastDocument` varchar(45) default NULL,
  `Migrates` text,
  `Grants` text,
  PRIMARY KEY  (`Id`)
) ENGINE=MyISAM;

DROP TABLE IF EXISTS `dm_document_versions`;
CREATE TABLE `dm_document_versions` (
  `Id_doc` varchar(50) NOT NULL default '',
  `Description` varchar(50) NOT NULL default '',
  `CreationDate` varchar(50) NOT NULL default '',
  `Attaches` text,
  `Grants` text,
  `Version` int(11) NOT NULL default '1',
  `Logs` text,
  `Reports` text,
  PRIMARY KEY  (`Id_doc`,`Version`)
) ENGINE=MyISAM;

DROP TABLE IF EXISTS `dm_document_childs`;
CREATE TABLE `dm_document_childs` (
  `id_doc` varchar(50) NOT NULL default '',
  `Version` int(11) default '1',
  `id_child` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`id_doc`,`id_child`)
) ENGINE=MyISAM;

DROP TABLE IF EXISTS `dm_document_files`;
CREATE TABLE `dm_document_files` (
  `id` varchar(50) NOT NULL default '',
  `name` varchar(50) default NULL,
  `description` varchar(100) default NULL,
  `status` varchar(20) default NULL,
  `type` varchar(20) default NULL,
  `migration_policy` varchar(45) default NULL,
  `download` varchar(20) default NULL,
  `id_doc` varchar(50) NOT NULL default '',
  PRIMARY KEY  (`id`,`id_doc`)
) ENGINE=MyISAM;


DROP TABLE IF EXISTS `dm_attributes`;
CREATE TABLE  `dm_attributes` (
  `DocId` varchar(50) NOT NULL default '',
  `Version` int(11) NOT NULL default '0',
  `Name` varchar(100) NOT NULL default '',
  `Direction` varchar(50) default 'None',
  `Type` varchar(50) default NULL,
  `Value` mediumtext,
  PRIMARY KEY  (`DocId`,`Version`,`Name`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
