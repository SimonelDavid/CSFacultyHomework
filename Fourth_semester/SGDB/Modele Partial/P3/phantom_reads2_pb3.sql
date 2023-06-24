USE Problema3
go

CREATE PROCEDURE Phantom_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL REPEATABLE READ
	BEGIN TRAN
	BEGIN TRY
	SELECT * FROM Tari
		WAITFOR DELAY '00:00:15'
		SELECT * FROM Tari
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END
------------------------------------------------------------------------------------------------------------------------------
EXECUTE Phantom_Reads_T2
SELECT * FROM Tari
------------------------------------------------------------------------------------------------------------------------------
CREATE PROCEDURE Phantom_Reads_T2_sol AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL SERIALIZABLE
	BEGIN TRAN
	BEGIN TRY
	SELECT * FROM Tari
		WAITFOR DELAY '00:00:15'
		SELECT * FROM Tari
		COMMIT TRAN
		SELECT 'Transaction committed' AS [Message]
	END TRY
	BEGIN CATCH
		ROLLBACK TRAN
		SELECT 'Transaction rollbacked' AS [Message]
	END CATCH
END
------------------------------------------------------------------------------------------------------------------------------
DELETE FROM Tari WHERE nume_t like 'TARA_NOUA'
EXECUTE Phantom_Reads_T2_sol
SELECT * FROM Tari
