<?php
require_once 'connect.php';
if(($_SESSION['email']!="admin@admin.admin") || ($_SESSION['heslo']!="heslo")){
    header('Location: index.php');
    exit();
}
?>
<!DOCTYPE html>
<html lang="cs">
<head>
    <meta charset="UTF-8">
    <title>Rozšířené hledání produktů</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Rozšířené hledání produktu</h1>
    <?php include_once 'header.php'; ?>
</header>
<div class="content">
    <h2>Vyhledejte produkt podle ID nebo názvu</h2>
    <form action="" method="post" enctype="multipart/form-data">
        <input type="text" name="hledany_produkt" placeholder="Zadejte název produktu">
        <input type="number" name="hledane_id" step="any" placeholder="Zadejte ID produktu">
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
            $hledane_id = isset($_POST["hledane_id"]) ? intval($_POST["hledane_id"]) : null;
            $hledany_produkt = isset($_POST["hledany_produkt"]) ? $_POST["hledany_produkt"] : null;
            $kateg=$_POST["kat"];
            if (isset($_POST["hledat"])) {
                if ($hledane_id && $hledany_produkt) {
                    $sql = "SELECT * FROM produkty WHERE id_produktu = $hledane_id OR nazev_produktu LIKE '%" . mysqli_real_escape_string($conn, $hledany_produkt) . "%'";
                    if($kateg!="all"){
                        $sql.=" AND kategorie='$kateg'";
                    }
                } elseif ($hledane_id) {
                    $sql = "SELECT * FROM produkty WHERE id_produktu = $hledane_id";
                    if($kateg!="all"){
                        $sql.=" AND kategorie='$kateg'";
                    }
                } elseif ($hledany_produkt) {
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

                $result = mysqli_query($conn, $sql);
                if (mysqli_num_rows($result) > 0) {
                    echo "<tr><th>id</th><th>název</th><th>Kategorie</th><th>Cena</th><th>Popis</th><th>Obrazek</th><th>Pocet na skladě</th><th>Odstranit</th><th>Edit</th></tr>";
                    while ($row = mysqli_fetch_assoc($result)) {
                        echo "<tr>
                            <td>" . $row["id_produktu"] . "</td>
                            <td>" . $row["nazev_produktu"] . "</td>
                            <td>". $row["kategorie"]. "</td>
                            <td>" . $row["cena"] . "</td>
                            <td>" . $row["popis"] . "</td>
                            <td><img src='" . $row["cesta_k_obrazku"] . "' alt='Obrazek' class='seznam_img'></td>
                            <td>" . $row["pocet_na_sklade"] . "</td>
                            <td><form action='delete.php' method='post' enctype='multipart/form-data'>
                                <input type='hidden' name='id_produktu' value='" . $row["id_produktu"] . "'>
                                <input type='hidden' name='last' value='find'>
                                <input type='submit' name='odstranit' value='Odstranit' class='button'>
                            </form></td>
                            <td><form action='edit.php' method='post' enctype='multipart/form-data'>
                                <input type='hidden' name='id_produktu' value='" . $row["id_produktu"] . "'>
                                <input type='submit' name='Edit' value='Edit' class='button'>
                            </form></td>
                        </tr>";
                    }
                } else {
                    echo "0 výsledků";
                }
            }
        }
        ?>
    </table>
<?php

mysqli_close($conn);
require_once 'footer.php';