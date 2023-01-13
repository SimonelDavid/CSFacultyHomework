--Procedura1
--modifica buget misiune
CREATE PROCEDURE version1
AS
BEGIN
      ALTER TABLE Misiune
	  ALTER COLUMN buget VARCHAR(30);

	  PRINT 'S-a modificat coloana buget in varchar'
END;

GO
--DROP PROCEDURE versiune1

--UNDO Procedura1
GO
CREATE PROCEDURE reverse_version1
AS
BEGIN
      ALTER TABLE Misiune
	  ALTER COLUMN buget INT;

	  PRINT 'UNDO S-a modificat coloana buget in INT'
END;


GO
--DROP PROCEDURE reverse_versiune1


--Procedura2
--Valoare Default pentru tara de origine a organizatiei
GO
CREATE PROCEDURE version2
AS
BEGIN
      ALTER TABLE Organizatii
	  ADD CONSTRAINT df_tara_orig DEFAULT 'SUA' FOR tara_orig;

	  PRINT 'S-a facut default la tara_orig a organizatiei'
END;

GO
--DROP PROCEDURE versiune2

--UNDO Procedura2
GO
CREATE PROCEDURE reverse_version2
AS
BEGIN
       ALTER TABLE Organizatii
	   DROP CONSTRAINT df_tara_orig

	   PRINT 'UNDO S-a facut undo la default tara_orig a organizatiei'
END;

GO
--DROP PROCEDURE reverse_versiune2

--Procedura3
--creeaza tabela publicatii
GO
CREATE PROCEDURE version3
AS
BEGIN
        CREATE TABLE Publicatii (
		id_publicatie INT PRIMARY KEY IDENTITY,
		id_obiect INT NOT NULL,
		data_publicatir DATETIME NOT NULL,
		text_publicatie NVARCHAR(200) NOT NULL
		);

		PRINT 'S-a creat tabela Publicatii'
END;

GO
--DROP PROCEDURE versiune3


--UNDO Procedura3
GO
CREATE PROCEDURE reverse_version3
AS
BEGIN
        DROP TABLE Publicatii;

		PRINT 'UNDO S-a sters tabela Publicatii'
END;


GO
--DROP PROCEDURE reverse_versiune3

--Procedura4
--Adauga camp nr aprecieri la tabela publicatii
GO
CREATE PROCEDURE version4
AS
BEGIN
        ALTER TABLE Publicatii
		ADD nr_aprecieri INT;

		PRINT 'S-a adaugat nr_aprecieri la tabela Publicatii'
END;

GO
--DROP PROCEDURE versiune4


--UNDO Procedura4
GO
CREATE PROCEDURE reverse_version4
AS
BEGIN
        ALTER TABLE Publicatii
		DROP COLUMN nr_aprecieri;

		PRINT 'UNDO S-a sters nr_aprecieri de la tabela Publicatii'
END;


GO
--DROP PROCEDURE UndoAdaugaCampNou


--Procedura5
GO
CREATE PROCEDURE version5
AS
BEGIN
        ALTER TABLE Publicatii
		ADD CONSTRAINT fk_obiect FOREIGN KEY(id_obiect) REFERENCES Obiecte(id_ob);

		PRINT 'S-a creat constrangere FK la tabela Publicatii-Obiect'
END;


GO
--DROP PROCEDURE versiune5


--UNDO Procedura5
GO
CREATE PROCEDURE reverse_version5
AS
BEGIN
       ALTER TABLE Publicatii
	   DROP CONSTRAINT fk_obiect

	   PRINT 'UNDO S-a sters constrangerea FK de la tabela Publicatii-Obiecte'
END;


GO
--DROP PROCEDURE versiune5




--Functia mare care apeleaza procedurile
--Am un tabel de versiuni
CREATE TABLE Versiune(
	id_versiune INT PRIMARY KEY IDENTITY,
	nr_versiune INT NOT NULL
);

INSERT INTO Versiune(nr_versiune) values(0);

SELECT * FROM Versiune

--Functia care apeleza versiunile
GO
--aduce baza de date intr o anumita versiune
CREATE PROCEDURE modifyDB @nr_procedura INT
AS
BEGIN
	DECLARE @curent INT --versiunea curenta in care e bd
	SET @curent = (SELECT nr_versiune FROM Versiune);

	IF @nr_procedura < 0 OR @nr_procedura > 5
	BEGIN
		PRINT 'Versiune inexistenta!'
		RETURN
	END
	ELSE

	IF @curent = @nr_procedura
		PRINT 'Tabela este deja in versiunea ceruta!'
	ELSE

	IF @curent < @nr_procedura
		WHILE @curent < @nr_procedura
		BEGIN
			IF @curent = 4 EXEC sp_executesql version5
			IF @curent = 3 EXEC sp_executesql version4
			IF @curent = 2 EXEC sp_executesql version3
			IF @curent = 1 EXEC sp_executesql version2
			IF @curent = 0 EXEC sp_executesql version1 
			SET @curent = @curent + 1
		END
	ELSE
		WHILE @curent > @nr_procedura
		BEGIN
			IF @curent = 1 EXEC sp_executesql reverse_version1
			IF @curent = 2 EXEC sp_executesql reverse_version2
			IF @curent = 3 EXEC sp_executesql reverse_version3 
			IF @curent = 4 EXEC sp_executesql reverse_version4
			IF @curent = 5 EXEC sp_executesql reverse_version5
			SET @curent = @curent - 1
		END
	UPDATE Versiune SET nr_versiune = @nr_procedura

END

EXEC modifyDB 0