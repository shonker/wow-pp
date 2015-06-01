/*
SQLyog Community v12.02 (64 bit)
MySQL - 5.5.27 : Database - wowpp_realm
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
/*Table structure for table `character` */

DROP TABLE IF EXISTS `character`;

CREATE TABLE `character` (
  `id` int(11) unsigned NOT NULL AUTO_INCREMENT COMMENT 'Character identifier',
  `account` int(11) unsigned NOT NULL COMMENT 'Account identifier',
  `name` varchar(32) COLLATE latin1_german1_ci NOT NULL COMMENT 'Character name',
  `race` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'Character race',
  `class` smallint(5) unsigned NOT NULL DEFAULT '0' COMMENT 'Character class',
  `gender` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Character gender',
  `level` int(10) unsigned NOT NULL DEFAULT '1' COMMENT 'Character level',
  `xp` bigint(20) unsigned NOT NULL DEFAULT '0' COMMENT 'Gained experience points so far',
  `gold` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Character gold',
  `online` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Determines whether the character is online',
  `cinematic` tinyint(3) unsigned NOT NULL DEFAULT '0' COMMENT 'Determines whether the cinematic was played',
  `map` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Character map location',
  `zone` int(10) unsigned NOT NULL DEFAULT '0' COMMENT 'Character zone id',
  `position_x` double NOT NULL DEFAULT '-9458.05' COMMENT 'Character location (x)',
  `position_y` double NOT NULL DEFAULT '47.8475' COMMENT 'Character location (y)',
  `position_z` double NOT NULL DEFAULT '56.6068' COMMENT 'Character location (z)',
  `orientation` double NOT NULL DEFAULT '0' COMMENT 'Character orientation (radians)',
  `bytes` int(10) unsigned NOT NULL DEFAULT '0',
  `bytes2` int(10) unsigned NOT NULL DEFAULT '0',
  `flags` int(10) unsigned NOT NULL DEFAULT '0',
  `at_login` int(11) unsigned NOT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=latin1 COLLATE=latin1_german1_ci;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
