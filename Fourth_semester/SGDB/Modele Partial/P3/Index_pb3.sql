--Creati un index si scrieti o interogare a carei executie sa utilizeze indexul. Aratati ca indexul este folosit afisand si explicand planul de executie pentru interogare

USE Problema3
GO

CREATE INDEX IX_nume_site ON Producatori(nume_p,website)

SELECT nume_p,website FROM Producatori WHERE nume_p like 'Belvita'
SELECT cod_p FROM Producatori 

drop index IX_nume_site ON Producatori