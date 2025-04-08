
# Návod na SQL Skripty

Tento dokument obsahuje stručný návod pro práci se SQL skripty – vytváření databáze, tabulek, vkládání dat, jejich výběr a aktualizaci. Navíc ukazuje propojení dvou tabulek pomocí cizího klíče.

---

## Vytvoření databáze a přepnutí do ní

```sql
CREATE DATABASE MojeDatabaze;
USE MojeDatabaze;
```

---

## Vytvoření tabulek

### Tabulka `Uzivatele`

```sql
CREATE TABLE Uzivatele (
    ID INT PRIMARY KEY,
    Jmeno VARCHAR(50),
    Email VARCHAR(100)
);
```

### Tabulka `Objednavky` s cizím klíčem

```sql
CREATE TABLE Objednavky (
    ID INT PRIMARY KEY,
    UzivatelID INT,
    Produkt VARCHAR(100),
    Cena DECIMAL(10,2),
    FOREIGN KEY (UzivatelID) REFERENCES Uzivatele(ID)
);
```

---

## Vložení dat

```sql
INSERT INTO Uzivatele (ID, Jmeno, Email)
VALUES (1, 'Petr Novak', 'petr@example.com');

INSERT INTO Objednavky (ID, UzivatelID, Produkt, Cena)
VALUES (1, 1, 'Notebook', 24999.99);
```

---

## Výběr dat

### Všichni uživatelé

```sql
SELECT * FROM Uzivatele;
```

### Všechny objednávky

```sql
SELECT * FROM Objednavky;
```

### Uživatele s jejich objednávkami (JOIN)

```sql
SELECT U.Jmeno, O.Produkt, O.Cena
FROM Uzivatele U
JOIN Objednavky O ON U.ID = O.UzivatelID;
```

---

## Aktualizace dat

```sql
UPDATE Uzivatele
SET Email = 'novyemail@example.com'
WHERE ID = 1;
```

---

## Mazání dat

```sql
DELETE FROM Objednavky WHERE ID = 1;
DELETE FROM Uzivatele WHERE ID = 1;
```

---

## Komentáře v SQL

```sql
-- Jednořádkový komentář
/* Víceřádkový
   komentář */
```

---

> 📄 Tento návod je určen pro základní pochopení práce s SQL skripty v relačních databázích.
