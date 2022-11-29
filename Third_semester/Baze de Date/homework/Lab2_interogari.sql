USE Gestiunea_Obiectelor_din_Orbita_Pamantului;

-- id-ul, titlul si numarul de misiuni intr-o orbita care au mai mult de o misiune ordonate descrescator
SELECT ORB.id_orb, ORB.nume, COUNT(M.id_mis) AS [nr misiuni] FROM Orbita ORB INNER JOIN Mis_in_Orb MO ON ORB.id_orb=MO.id_orb INNER JOIN Misiune M 
ON M.id_mis=MO.id_mis GROUP BY ORB.id_orb, ORB.nume HAVING COUNT(MO.id_mis)>1 ORDER BY [nr misiuni] DESC;

-- numele obiectului, id-ul obiectului si numele organizatiei care lanseaza obiectul si incepe cu C
SELECT S.nume,OB.id_ob,ORG.nume FROM Satelit S INNER JOIN Obiecte OB ON S.id_sat=OB.id_sat INNER JOIN Organizatii ORG ON ORG.id_org=OB.id_lan WHERE ORG.nume LIKE'E%';

-- id-ul, numele tipurilor de sateliti si numarul de sateliti pentru acel tip daca sunt mai mult de 3 sateliti la un tip
SELECT TS.id_tip_sat, TS.nume, COUNT(S.id_tip_sat) AS [nr tipuri sat] FROM Satelit S INNER JOIN TipSatelit TS ON TS.id_tip_sat=S.id_tip_sat 
GROUP BY TS.id_tip_sat, TS.nume HAVING COUNT(S.id_tip_sat)>3 ORDER BY [nr tipuri sat] DESC;

SELECT S.id_sat, S.nume, TS.nume FROM Satelit S INNER JOIN TipSatelit TS ON S.id_tip_sat=TS.id_tip_sat INNER JOIN Autori A ON CA.cod_autor=A.cod_autor WHERE A.nume_autor<>'Eminescu';