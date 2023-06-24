USE S32023
GO

CREATE PROCEDURE Non_Repeatable_Reads_T1 AS
BEGIN
	BEGIN TRAN
	BEGIN TRY
		WAITFOR DELAY '00:00:10'
		UPDATE Tari SET nume_tara = 'RO' WHERE descriere like 'descriere tara1'
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END
--------------------------------------------------------------------------------------------------------------------------
EXECUTE Non_Repeatable_Reads_T1
UPDATE Tari SET nume_tara = 'tara1' WHERE descriere like 'descriere tara1'
--------------------------------------------------------------------------------------------------------------------------
