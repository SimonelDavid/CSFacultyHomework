USE Gestiunea_Obiectelor_din_Orbita_Pamantului;

INSERT INTO TipSatelit(nume) VALUES('comunicare');
INSERT INTO TipSatelit(nume) VALUES('geostationar');
INSERT INTO TipSatelit(nume) VALUES('militar');
INSERT INTO TipSatelit(nume) VALUES('geosincron');
INSERT INTO TipSatelit(nume) VALUES('observare');
INSERT INTO TipSatelit(nume) VALUES('navigare');
INSERT INTO TipSatelit(nume) VALUES('vreme');

INSERT INTO Satelit(nume, id_tip_sat) VALUES('Telstar 1', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Intelsat 1', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Telstar 603', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Telstar 1', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('AMOS 2', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('AMOS 3', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('AMOS 6A', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Telkom 2', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Telkom 3', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Telstar 1', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Courier 1B', 1);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('GOES 16', 2);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('GOES 17', 2);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('Mexsat-3', 2);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('GSAT-18', 2);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('USA 327', 3);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('TURKSAT 5B', 3);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('USA 310', 3);
INSERT INTO Satelit(nume, id_tip_sat) VALUES('OFEQ 16', 3);

INSERT INTO Telescop(nume) VALUES('James Webb Telescope'), 
('Hubble Space Telescope'),
('Herschel Space Observatory'),
('Spektr-RG');

INSERT INTO Deseu(nume) VALUES('piese de nave spatiale'),
('bucati de racheta'),
('sateliti inactivi');

INSERT INTO Organizatii(nume, tara_orig) VALUES('NASA', 'SUA'),
('ESA', 'Europa'),
('JAXA', 'Japnoia'),
('SpaceX', 'SUA'),
('GMV', 'Spania'),
('THALES', 'Franta'),
('CNSA', 'Chima');

INSERT INTO Statie(nume) VALUES('ISS'),
('Tiangong-1'),
('Tiangong-2'),
('Mir'),
('Skylab'),
('Salyut 7');

INSERT INTO Misiune(tip, denumire, buget) VALUES('comunicare','Telstar',500),
('comunicare','Intelsat',150),
('deep space','hubble',16000),
('deep space','james webb',10000),
('experimente','iss',150000),
('experiemnte','tiangong',60000),
('observsare','Copernicus',3500),
('geostationar','GOES',2500),
('militar','TURKSAT', 5000);

INSERT INTO Satelit(nume, id_tip_sat) VALUES('Copernicus Sentinel-1',5),
('Copernicus Sentinel-6',5);

INSERT INTO Orbita(nume, altitudine) VALUES('LEO',2000),
('MEO',17000),
('GEO',35800),
('SSO',700),
('GTO',37000);

USE Gestiunea_Obiectelor_din_Orbita_Pamantului;

INSERT INTO Satelit(nume, id_tip_sat) VALUES('GSAT0202', 6), ('GSAT0209', 6);

INSERT INTO Misiune(tip, denumire, buget) VALUES('localizare','Galileo',10000);

INSERT INTO Orbita(nume, altitudine) VALUES('Lagrange Orbit',1500000) 

INSERT INTO Mis_in_Orb(id_mis, id_orb) VALUES(1,2),
(2,3),
(3,4),
(4,6),
(5,1),
(6,1),
(7,1),
(8,2);

INSERT INTO Obiecte(id_mis, id_sat, id_st, id_tel, id_des, id_con, id_lan, id_int, activ) VALUES(1,1,null,null,null,1,1,1,1),
(1,1,null,null,null,1,1,1,1),
(2, 2, null, null, null, 1, 1, 1, 1),
(3, null, null, 2, null, 1, 1, 2, 1),
(4, null, null, 1, null, 1, 2, 1, 1),
(5, null, 1, null, null, 1, 3, 2, 1),
(6, null, 2, null, null, 7, 7, 7, 1),
(6, null, 3, null, null, 7, 7, 7, 0),
(7, 20, null, null, null, 2, 2, 2, 1),
(7, 21, null, null, null, 2, 2, 2, 1),
(8, 12, null, null, null, 1, 1, 1, 1),
(8, 13, null, null, null, 1, 1, 1, 1),
(9, 17, null, null, null, 2, 2, 2, 1);