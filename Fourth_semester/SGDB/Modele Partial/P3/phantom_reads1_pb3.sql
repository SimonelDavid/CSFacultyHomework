USE Problema3
go


CREATE PROCEDURE Phantom_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		WAITFOR DELAY '00:00:10'
		INSERT INTO Tari(nume_t) VALUES ('TARA_NOUA')
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END

--------------------------------------------------------------------------------------------------------------------------
EXECUTE Phantom_Reads_T1