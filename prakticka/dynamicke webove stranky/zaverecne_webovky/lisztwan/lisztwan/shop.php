<?php
require_once 'connect.php';
if(empty($_SESSION['email']) || empty($_SESSION['heslo'])){
    header('Location: prihlaseni.php');
    exit();
}
?>


<!DOCTYPE html>
<meta charset="UTF-8">
<html>
<head>
    <title>Eshop-jawa</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Eshop dílu jawa</h1>

    <?php
    include_once 'headershop.php';
    ?>
</header>
<div class="content">

    <h2>Vyhledejte produkt podle názvu</h2>
    <form action="" method="post" enctype="multipart/form-data">
        <label for="order">Seřadit podle:</label>
        <select name="serazeni">
            <option selected value="cena">nejlevnější</option>
            <option value="cena DESC">nejdražší</option>
            <option value="nazev_produktu">názvu</option>
            <option value="pocet_na_sklade">počtu na skladě</option>
        </select><br>
        <input type="text" name="hledany_produkt" placeholder="Zadejte název produktu">
        <select name="kat" id="kategorie">
            <option selected value="all">Všechny kategorie</option>
            <option value="motor">Motor</option>
            <option value="elektro">Elektro</option>
            <option value="podvozek">Podvozek</option>
            <option value="ostatni">Ostatní</option>
        </select>
        <input type="submit" name="hledat" value="Hledat" class="button">
    </form>
    <table class="seznam">
        <?php
        $sql = "SELECT * FROM produkty";
        if ($_POST) {
            $hledany_produkt = isset($_POST["hledany_produkt"]) ? $_POST["hledany_produkt"] : null;
            $kateg=$_POST["kat"];
            if (isset($_POST["hledat"])) {
                if ($hledany_produkt) {
                    $sql = "SELECT * FROM produkty WHERE nazev_produktu LIKE '%" . mysqli_real_escape_string($conn, $hledany_produkt) . "%'";
                    if($kateg!="all"){
                        $sql.=" AND kategorie='$kateg'";
                    }
                }else{
                    $sql = "SELECT * FROM produkty";
                    if($kateg!="all"){
                            $sql.=" WHERE kategorie='$kateg'";
                        }


                    }

                }
                if(isset($_POST["serazeni"])){
                    $sql.=" ORDER BY ".$_POST["serazeni"];
                }


        }
        $result = mysqli_query($conn, $sql);
        if (mysqli_num_rows($result) > 0) {
            echo "<tr><th>název</th><th>Kategorie</th><th>Cena</th><th>Obrazek</th><th>Pocet na skladě</th><th>Počet</th><th>Do košíku</th></tr>";
            while($row = mysqli_fetch_assoc($result)) {
                echo "<tr>
                        <td><form enctype='multipart/form-data' action='detail.php' method='post' >
                        <input type='hidden' name='id' value='". $row["id_produktu"]. "'>
                        <input type='submit' name='detail' value='".$row["nazev_produktu"]."' class='detail_button'>
                        </form></td>
                        
                        <td>". $row["kategorie"]. "</td>
                        <td>". $row["cena"]. "</td>
                        <td><img src=".$row["cesta_k_obrazku"]." alt='Obrazek' class='seznam_img'></td>
                        <td>". $row["pocet_na_sklade"]. "</td>
                        <form action='' method='post' enctype='multipart/form-data'><td>
                        <input type='hidden' name='id' value='". $row["id_produktu"]. "'>
                        <input type='number' name='pocet' min='1' max='".$row['pocet_na_sklade']."' value='1' step='any'></td>
                        <td><input type='submit' name='dokosiku' value='Do košíku' class='button'>
                        </td></form>
                        </tr>";
            }
        } else {
            echo "0 výsledků";
        }
        ?>
    </table>


<?php

if (isset($_POST["dokosiku"])) {
    $pocet = $_POST['pocet'];
    $id = $_POST['id'];
    $sql = "SELECT * FROM produkty WHERE id_produktu=$id";
    $result = mysqli_query($conn, $sql);
    $row = mysqli_fetch_assoc($result);
    $pocet_na_sklade=$row['pocet_na_sklade'];
    if(empty($pocet)){
        echo "Zadejte počet";
        exit();
    }
    if ($pocet_na_sklade<$pocet){
        echo "Zvolili jste zvolili větší počet než je na skladě";
        exit();
    }

    if (mysqli_query($conn, $sql)) {
        $sql= "SELECT * FROM uzivatele WHERE email='".$_SESSION['email']."'";
        $result = mysqli_query($conn, $sql);
        $row = mysqli_fetch_assoc($result);
        $id_zakaznika=$row['id'];
        $sql= "SELECT * FROM kosik WHERE id_zakaznika='$id_zakaznika' AND id_produktu='$id'";
        $result = mysqli_query($conn, $sql);
        if(mysqli_num_rows($result)>0){
            $sql="UPDATE kosik SET pocet=pocet+$pocet WHERE id_zakaznika='$id_zakaznika' AND id_produktu='$id'";
        }else{
            $sql="INSERT INTO kosik VALUES (default,'$id', '$id_zakaznika', '$pocet')";
        }
        if (mysqli_query($conn, $sql)) {
            header('Location: shop.php');
            echo "Produkt byl přidán do košíku";


        } else {
            echo "Error: ". $sql. "<br>". mysqli_error($conn);
        }


    } else {
        echo "Error: ". $sql. "<br>". mysqli_error($conn);
    }
}

mysqli_close($conn);

require_once 'footer.php';
?>
