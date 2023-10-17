--Creati un index si scrieti o interogare a carei executie sa utilizeze indexul. Aratati ca indexul este folosit afisand si explicand planul de executie pentru interogare

USE Problema2
GO

CREATE INDEX index2 ON Melodii (an_lansare);
SELECT an_lansare FROM Melodii ORDER BY an_lansare;
