USE S32023
GO

CREATE PROCEDURE Non_Repeatable_Reads_T2 AS
BEGIN
	SET TRANSACTION ISOLATION LEVEL READ COMMITTED
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
EXECUTE Non_Repeatable_Reads_T2
SELECT * FROM Tari
------------------------------------------------------------------------------------------------------------------------------
CREATE PROCEDURE Non_Repeatable_Reads_T2_sol AS
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
EXECUTE Non_Repeatable_Reads_T2_sol
SELECT * FROM Tari