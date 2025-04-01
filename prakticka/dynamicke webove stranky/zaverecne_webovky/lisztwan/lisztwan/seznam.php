<?php
require_once 'connect.php';
if(($_SESSION['email']!="admin@admin.admin") || ($_SESSION['heslo']!="heslo")){
    header('Location: index.php');
    exit();
}
?>
<!DOCTYPE html>
<meta charset="UTF-8">
<html>
<head>
    <title>Seznam dílů</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Seznam dílů Jawa Kývačka</h1>
    <?php
    include_once 'header.php';
    ?>
</header>
    <div class="content">
        <h2>Seznam dílů</h2>

        <form enctype="multipart/form-data" action="" method="post">
            <label for="order">Seřadit podle:</label>
            <select name="serazeni" value="id">
                <option value="id_produktu">id</option>
                <option value="cena">nejlevnější</option>
                <option value="maxCena">nejdražší</option>
                <option value="nazev_produktu">názvu</option>
                <option value="pocet_na_sklade">počtu na skladě</option>
            </select>
            <input type="submit" name="order" value="Seřadit" class="button">
        </form>
        <table class="seznam">
    <?php
    $sql = "SELECT * FROM produkty";
    if ($_POST){
        if (isset($_POST["order"])){
            $sql = "SELECT * FROM produkty ORDER BY ".$_POST["serazeni"];
            if ($_POST["serazeni"] == "maxCena")$sql = "SELECT * FROM produkty ORDER BY cena DESC";

        }
    }
    $result = mysqli_query($conn, $sql);
    if (mysqli_num_rows($result) > 0) {
        echo "<tr><th>id</th><th>název</th><th>Kategorie</th><th>Cena</th><th>Popis</th><th>Obrazek</th><th>Pocet na skladě</th><th>Odstranit</th><th>Edit</th></tr>";
        while($row = mysqli_fetch_assoc($result)) {
            echo "<tr>
    <td>". $row["id_produktu"]. "</td>
    <td>". $row["nazev_produktu"]. "</td>
    <td>". $row["kategorie"]. "</td>
    <td>". $row["cena"]. "</td>
    <td>". $row["popis"]. "</td>
    <td><img src=".$row["cesta_k_obrazku"]." alt='Obrazek' class='seznam_img'></td>
    <td>". $row["pocet_na_sklade"]. "</td>
    <td><form action='delete.php' method='post' enctype='multipart/form-data'>
    <input type='hidden' name='id_produktu' value='".$row["id_produktu"]."'>
    <input type='hidden' name='last' value='seznam'>
    <input type='submit' name='odstranit' value='Odstranit' class='button'>
    </form></td>
    <td><form action='edit.php' method='post' enctype='multipart/form-data'>
    <input type='hidden' name='id_produktu' value='".$row["id_produktu"]."'>
    <input type='submit' name='Edit' value='Edit' class='button'>
    </form></td>
    </tr>";
        }
    } else {
        echo "0 výsledků";
    }

    ?>
        </table>
<?php


mysqli_close($conn);
    require_once 'footer.php';
?>
