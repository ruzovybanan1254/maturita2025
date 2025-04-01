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


    <div class="detail">
        <?php
            if($_POST){
                if(isset($_POST['detail'])){
                    $id = $_POST['id'];
                    $sql = "SELECT * FROM produkty WHERE id_produktu=$id";
                    $result = mysqli_query($conn, $sql);
                    $row = mysqli_fetch_assoc($result);
                    $nazev = $row['nazev_produktu'];
                    $cena = $row['cena'];
                    $pocet_na_sklade = $row['pocet_na_sklade'];
                    $cesta_k_obrazku = $row['cesta_k_obrazku'];
                    $popis = $row['popis'];
                    echo "<h2>$nazev</h2>
                    <img src='$cesta_k_obrazku' alt='Obrazek' class='detail_img'>
                    <p>Cena: $cena Kč</p>
                    <p>Počet na skladě: $pocet_na_sklade</p>
                    <p>Popis: $popis</p>
                    <form action='' method='post' enctype='multipart/form-data'>
                        <input type='hidden' name='id' value='". $row["id_produktu"]. "'>
                        <input type='number' name='pocet' min='1' max='".$row['pocet_na_sklade']."' value='1' step='any'>
                        <input type='submit' name='dokosiku' value='Do košíku' class='button'>
                    </form>
                    ";

                }
            }
        ?>
    </div>
    <a href="shop.php" class="button">Zpět</a>

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
