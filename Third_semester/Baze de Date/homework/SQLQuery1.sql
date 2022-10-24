USE Gestiunea_Obiectelor_din_Orbita_Pamantului;

CREATE TABLE Satelit
(
	id_sat INT PRIMARY KEY IDENTITY,
	nume CHAR,
)

CREATE TABLE Domeniu
(
	id_dom INT PRIMARY KEY IDENTITY,
	nume CHAR,
)

CREATE TABLE Misiune
(
	id_mis INT PRIMARY KEY IDENTITY,
	tip CHAR,
	denumire CHAR,
	buget INT,
	id_dom INT,
	CONSTRAINT FK_domeniu FOREIGN KEY (id_dom) REFERENCES Domeniu(id_dom),
)

CREATE TABLE Organizatii
(
	id_org INT PRIMARY KEY IDENTITY,
	nume CHAR,
	tara_orig CHAR,
)

CREATE TABLE Orbita
(
	id_orb INT PRIMARY KEY IDENTITY,
	nume CHAR,
	altitudine INT, 
)

CREATE TABLE Mis_in_Orb(
	id_mis_orb INT PRIMARY KEY IDENTITY,
	id_mis INT,
	id_orb INT,
	CONSTRAINT FK_mis_orb FOREIGN KEY (id_mis) REFERENCES Misiune(id_mis),
	CONSTRAINT FK_orb_mis FOREIGN KEY (id_orb) REFERENCES Orbita(id_orb),
)

CREATE TABLE Statie
(
	id_st INT PRIMARY KEY IDENTITY,
	nume CHAR,
)

CREATE TABLE Sonda
(
	id_sd INT PRIMARY KEY IDENTITY,
	nume CHAR,
)

CREATE TABLE Telescop
(
	id_tel INT PRIMARY KEY IDENTITY,
	nume CHAR,
)

CREATE TABLE Deseu
(
	id_des INT PRIMARY KEY IDENTITY,
	nume CHAR,
)

CREATE TABLE Obiecte
(
	id_ob INT PRIMARY KEY IDENTITY,
	id_sat INT,
	id_mis INT,
	id_con INT,
	id_lan INT,
	id_int INT,
	id_orb INT,
	id_st INT,
	id_sd INT,
	id_tel INT,
	id_des INT,
	activ BIT,
	CONSTRAINT FK_satelit FOREIGN KEY (id_sat) REFERENCES Satelit(id_sat),
	CONSTRAINT FK_misiune FOREIGN KEY (id_mis) REFERENCES Misiune(id_mis),
	CONSTRAINT FK_constructor FOREIGN KEY (id_con) REFERENCES Organizatii(id_org),
	CONSTRAINT FK_lansator FOREIGN KEY (id_lan) REFERENCES Organizatii(id_org),
	CONSTRAINT FK_intretinator FOREIGN KEY (id_int) REFERENCES Organizatii(id_org),
	CONSTRAINT FK_orbita FOREIGN KEY (id_orb) REFERENCES Orbita(id_orb),
	CONSTRAINT FK_statie FOREIGN KEY (id_st) REFERENCES Statie(id_st),
	CONSTRAINT FK_sonda FOREIGN KEY (id_sd) REFERENCES Sonda(id_sd),
	CONSTRAINT FK_telescop FOREIGN KEY (id_tel) REFERENCES Telescop(id_tel),
	CONSTRAINT FK_deseu FOREIGN KEY (id_des) REFERENCES Deseu(id_des),
)