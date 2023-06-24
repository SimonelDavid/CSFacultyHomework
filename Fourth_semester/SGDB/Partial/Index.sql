use S5
go

CREATE INDEX index_denumire
on Facultati(Denumire);

Select * from Facultati
order by Denumire;
