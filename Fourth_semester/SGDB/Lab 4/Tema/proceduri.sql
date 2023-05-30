use [Bolt_Food]

go
create or alter procedure P1
as
begin
	begin transaction
	update Tip_Vehicul set Denumire = 'Transaction 2'
	where Tonaj = 2;
	waitfor delay '00:00:10';
	update Meniu set Url_site = 'Transaction 2'
	where Id_Meniu = 13;
	commit transaction
end


go
create or alter procedure P2
as
begin
	begin transaction
	update Meniu set Url_site = 'Transaction 2'
	where Id_Meniu = 13;
	waitfor delay '00:00:10';
	update Tip_Vehicul set Denumire = 'Transaction 2'
	where Tonaj = 2;
	commit transaction;
end

select * from Tip_Vehicul
select * from Meniu

update Meniu set Url_site = 'Transaction 2'
	where Id_Meniu = 13;
update Tip_Vehicul set Denumire = 'Transaction 2'
	where Tonaj = 2;