create database farmacii
use farmacii
go

create table Afectiuni(
id_a int primary key identity,
nume_a nvarchar(100),
descriere_a nvarchar(100)
)

create table Medicament(
id_m int primary key identity,
nume_m nvarchar(100),
descriere_m nvarchar(100),
producator_m nvarchar(100),
mod_administrare_m nvarchar(100),
)

create table afect_med(
id_afect_med int primary key identity,
id_a int,
id_m int,
constraint fk_aid foreign key (id_a) references Afectiuni(id_a),
constraint fk_pid foreign key (id_m) references Medicament(id_m),
)

create table Farmacie(
id_f int primary key identity,
nume_f nvarchar(100),
adresa_f nvarchar(100),
nr_telefon_f int,
oras_f nvarchar(100)
)

create table Pret(
id_f int,
id_m int,
pret_m int,
foreign key (id_f) references Farmacie(id_f),
foreign key (id_m) references Medicament(id_m),
primary key(id_f,id_m)
)

insert into Medicament values ('algocalmin','pentru dureri de cap','zentiva','prin inghitire'),
('paduden','pentru dureri generale','terapia s.a.','prin inghitire'),
('strepsils','pentru dureri de gat',' Reckitt Benckiser Healthcare International Ltd.','prin dizolvare inceta in gura'),
('imunix','pentru gripa','Bionika','prin inghitire'),
('voltaren','pentru dureri de spate','novartis','se aplica local pe piele');
select * from Medicament;

insert into Farmacie values('catena','strada crangasi, nr 70',734989231,'Bucuresti'),
('napocafarm','strada florilor, nr 14',734286201,'Cluj-Napoca');
select * from Farmacie;

insert into Afectiuni values('ameteala','nu gandeste limpede, il doare capul'),
('durere de gat','durere de gat, raguseala'),
('durere de spate', 'carcei, dureri in oase');
select * from Afectiuni;

insert into afect_med values(1,1),
(3,2),
(3,3);

select * from afect_med
go

create or alter procedure AdaugaMed 
@id_f int, 
@id_m int,
@pret float
as
begin
	if(exists(select * from Pret where id_f=@id_f and id_m=@id_m))
	begin
		update Pret set pret_m=@pret where id_f=@id_f and id_m=@id_m
	end
	else
	begin
		insert into Pret(id_f, id_m,pret_m) values(@id_f,@id_m,@pret)
	end
end

exec AdaugaMed 1, 2, 20
exec AdaugaMed 1 ,3, 20
select * from Pret;

go

create or alter view Dureri
as


select * from Dureri;