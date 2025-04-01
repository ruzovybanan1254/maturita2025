<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "dat_3b";
session_start();
// Vytvoření připojení
$conn = new mysqli($servername, $username, $password, $dbname) or die("Error pripojeni");

// Tabulka pro produkty
$sql = "CREATE TABLE IF NOT EXISTS produkty (
    id_produktu INT PRIMARY KEY AUTO_INCREMENT,
    nazev_produktu VARCHAR(255) NOT NULL,
    kategorie ENUM('motor', 'elektro', 'podvozek', 'ostatni') NOT NULL,
    cena DECIMAL(10, 2) NOT NULL,
    popis TEXT,
    cesta_k_obrazku VARCHAR(255),
    pocet_na_sklade INT NOT NULL
);";
$result = mysqli_query($conn,$sql);

// Tabulka pro uživatele
$sql = "CREATE TABLE IF NOT EXISTS uzivatele (
    id INT PRIMARY KEY AUTO_INCREMENT,
    email VARCHAR(255) NOT NULL,
    jmeno VARCHAR(255) NOT NULL,
    prijmeni VARCHAR(255) NOT NULL,
    ulice VARCHAR(255) NOT NULL,
    cislo_popisne VARCHAR(255) NOT NULL,
    mesto VARCHAR(255) NOT NULL,
    telefonni_cislo VARCHAR(255) NOT NULL,
    heslo VARCHAR(255) NOT NULL
);";
$result = mysqli_query($conn,$sql);

// Tabulka pro košík
$sql = "CREATE TABLE IF NOT EXISTS kosik (
    id INT PRIMARY KEY AUTO_INCREMENT,
    id_produktu INT NOT NULL,
    id_zakaznika INT NOT NULL,
    pocet INT NOT NULL,
    FOREIGN KEY (id_produktu) REFERENCES produkty(id_produktu),
    FOREIGN KEY (id_zakaznika) REFERENCES uzivatele(id)
);";
$result = mysqli_query($conn,$sql);
/*
// Tabulka pro dokončené objednávky
$sql = "CREATE TABLE IF NOT EXISTS objednavky (
    id_objednavky INT PRIMARY KEY AUTO_INCREMENT,
    id_zakaznika INT NOT NULL,
    datum_objednavky DATE NOT NULL,
    FOREIGN KEY (id_zakaznika) REFERENCES uzivatele(id)
);";
$result = mysqli_query($conn,$sql);
*/
?>
