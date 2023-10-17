--Creati un index si scrieti o interogare a carei executie sa utilizeze indexul. Aratati ca indexul este folosit afisand si explicand planul de executie pentru interogare

USE S32023
GO

CREATE INDEX index2 ON Sejururi (data_inceput);
SELECT data_inceput FROM Sejururi ORDER BY data_inceput;

drop index index2 ON Sejururi