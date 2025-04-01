<?php
include_once 'connect.php';
?>
<!DOCTYPE html>
<meta charset="UTF-8">
<html>
<head>
    <title>Domovská stránka</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Domovská stránka</h1>
<?php
include_once 'headershop.php';
?>
</header>
<div class="content">
    <h2>Evidence produktu JAWA Kývačka</h2>
    <p>Toto je závěrečná práce z předmětu Databáze, tyto stránky byly vytvořeny pro studijní účely na SPŠE Havířov</p>
    <p>Děkuji za propůjčení obrázků pro demo ukázku funkčnosti databáze z eshopu <a href="https://www.motojelinek.cz/.htm" target="blank">motojelinek</a></p>
    <p><br>V této závěrečné práci je obsažen jednoduchý základ eshopu a správa produktů na eshop se prokliknete v menu, ke správě uživatelů použijte tlačítko níže. Musíte být ale příhlášení účtem admin@admi.admin a heslem "heslo"</p>
    <a href="seznam.php" class="button">Správa</a>
    <a href="prihlaseni.php" class="button">Přihlášení</a>
    
<?php
mysqli_close($conn);
include_once 'footer.php';
?>
