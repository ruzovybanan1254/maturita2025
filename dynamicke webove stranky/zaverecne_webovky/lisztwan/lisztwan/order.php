<?php
require_once 'connect.php';
if(empty($_SESSION['email']) || empty($_SESSION['heslo'])){
    header('Location: prihlaseni.php');
    exit();
}
?>


<!DOCTYPE html>
<meta charset="UTF-8">
<html lang="cs">
<head>
    <title>Objednávka</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">
</head>
<body>
<header>
    <h1>Objednávka</h1>

    <?php
    include_once 'headershop.php';
    ?>
</header>
<div class="content">
    <h2>Objednávka</h2>
    <?php
    if(isset($_POST['odeslat'])){
        $id_zakaznika=$_POST['uzivatel'];
        $sql = "SELECT * FROM uzivatele WHERE id='$id_zakaznika'";
        $result = mysqli_query($conn, $sql);
        $row = mysqli_fetch_assoc($result);
        $jmeno=$row['jmeno'];
        $prijmeni=$row['prijmeni'];
        $ulice=$row['ulice'];
        $cislo_popisne=$row['cislo_popisne'];
        $mesto=$row['mesto'];
        $telefonni_cislo=$row['telefonni_cislo'];
        $email=$row['email'];
        echo "<p>Adresa: ".$mesto." ".$ulice." ".$cislo_popisne."</p>";
        echo "<p>Na osobu: ".$jmeno." ".$prijmeni."</p>";
        echo "<p>Na telefon: ".$telefonni_cislo."</p>";
        echo "Odesíláme českou poštou, cena za dopravu je 100Kč</p>";
        echo "<p>Cena celkem: ".($_POST['cena']+100)."Kč</>";
        echo "<form action='' method='post' enctype='multipart/form-data'>";
            echo "<input type='submit' name='objednat' value='Potvrzuji objednavku' class='button'>";
        echo "</form>";


    }
    if ($_POST){
        if (isset($_POST['objednat'])){
            echo "<p>Objednávka byla odeslána</p>";
            $sql = "SELECT * FROM uzivatele WHERE email='".$_SESSION['email']."'";
            $result = mysqli_query($conn, $sql);
            $row = mysqli_fetch_assoc($result);
            $id_zakaznika=$row['id'];
            $sql = "SELECT * FROM kosik WHERE id_zakaznika='$id_zakaznika'";
            $result = mysqli_query($conn, $sql);
            while($row = mysqli_fetch_assoc($result)) {
                $pocet=$row['pocet'];
                $id_produktu=$row['id_produktu'];
                $sql = "UPDATE produkty SET pocet_na_sklade=pocet_na_sklade-$pocet WHERE id_produktu='$id_produktu'";
                mysqli_query($conn, $sql);
            }
            $sql = "DELETE FROM kosik WHERE id_zakaznika='$id_zakaznika'";
            mysqli_query($conn, $sql);
        }
    }

    ?>
<a href='kosik.php' class='button'>Zpět</a>


<?php
mysqli_close($conn);
require_once 'footer.php';
?>
