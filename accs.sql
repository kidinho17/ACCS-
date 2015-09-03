-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: 03-Set-2015 às 23:44
-- Versão do servidor: 5.6.20
-- PHP Version: 5.5.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `accs`
--

-- --------------------------------------------------------

--
-- Estrutura da tabela `parameters`
--

CREATE TABLE IF NOT EXISTS `parameters` (
  `desiredTemp` varchar(11) NOT NULL,
  `time_set` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `parameters`
--

INSERT INTO `parameters` (`desiredTemp`, `time_set`) VALUES
('22', '2015-09-03 23:19:43');

-- --------------------------------------------------------

--
-- Estrutura da tabela `readings`
--

CREATE TABLE IF NOT EXISTS `readings` (
  `temp` varchar(11) DEFAULT '0',
  `humidity` varchar(11) DEFAULT '0',
  `luminosity` varchar(11) DEFAULT '0',
  `fan_speed` varchar(11) DEFAULT NULL,
  `time_server` datetime DEFAULT CURRENT_TIMESTAMP,
  `time_workstation` datetime NOT NULL DEFAULT CURRENT_TIMESTAMP
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Extraindo dados da tabela `readings`
--

INSERT INTO `readings` (`temp`, `humidity`, `luminosity`, `fan_speed`, `time_server`, `time_workstation`) VALUES
('22', '30', '17', '20', '2015-09-03 22:36:36', '2015-09-03 22:36:01'),
('22', '30', '18', '20', '2015-09-03 22:38:42', '2015-09-03 22:38:09'),
('30', '30', '18', '20', '2015-09-03 22:48:26', '2015-09-03 22:38:09'),
('25', '30', '18', '20', '2015-09-03 23:09:10', '2015-09-03 22:38:09'),
('27', '30', '18', '20', '2015-09-03 23:09:33', '2015-09-03 22:38:09'),
('18', '30', '18', '20', '2015-09-03 23:10:00', '2015-09-03 22:38:09');

-- --------------------------------------------------------

--
-- Estrutura da tabela `user`
--

CREATE TABLE IF NOT EXISTS `user` (
  `id` int(11) NOT NULL,
  `name` varchar(255) NOT NULL,
  `password` varchar(255) NOT NULL,
  `level` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
