USE Gestiunea_Obiectelor_din_Orbita_Pamantului;

INSERT INTO Organizatii(nume, tara_orig) VALUES('CNSA', 'Chima');

INSERT INTO Obiecte(id_mis, id_sat, id_st, id_tel, id_des, id_con, id_lan, id_int, activ) VALUES(1,1,null,null,null,1,1,1,1),
(2, 2, null, null, null, 1, 1, 1, 1),
(3, null, null, 2, null, 1, 1, 2, 1),
(4, null, null, 1, null, 1, 2, 1, 1),
(5, null, 1, null, null, 1, 3, 2, 1),
(6, null, 2, null, null, 7, 7, 7, 1),
(6, null, 3, null, null, 7, 7, 7, 0),
(7, 20, null, null, null, 2, 2, 2, 1),
(7, 21, null, null, null, 2, 2, 2, 1);