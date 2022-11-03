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
('THALES', 'Franta');

INSERT INTO Statie(nume) VALUES('ISS'),
('Tiangong-1'),
('Tiangong-2'),
('Mir'),
('Skylab'),
('Salyut 7');