<?php
include_once 'connect.php';
if(($_SESSION['email']!="admin@admin.admin") || ($_SESSION['heslo']!="heslo")){
    header('Location: index.php');
    exit();
}
?>
<!DOCTYPE html>
<meta charset="UTF-8">
<html>
<head>
    <title>Přidání produktu</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Přidání produktu</h1>
    <?php
    include_once 'header.php';
    ?>
</header>
<div class="content">
    <h2>Přidání produktu do databáze</h2>
    <form action="" enctype="multipart/form-data" method="post">
    <table class="form">
        <tr>
            <td><label for="nazev">Název produktu</label></td>
            <td><input type="text" name="nazevP" id="nazev"></td>
        </tr>
        <tr>
            <td><label for="kategorie">Vyberte kategorii</label></td>
            <td>
                <select id="kategorie" name="kategorie">
                    <option selected value="motor">Motor</option>
                    <option value="elektro">Elektro</option>
                    <option value="podvozek">Podvozek</option>
                    <option value="ostatni">Ostatní</option>
                </select>
            </td>
        </tr>
        <tr>
            <td><label for="cena">Cena</label></td>
            <td><input type="number" step="0.01" name="cenaP" id="cena" min="1" max="100000"></td>
        </tr>
        <tr>
            <td><label for="popis">Popis produktu</label></td>
            <td><textarea id='popis' name='popisP'></textarea></td>
        </tr>
        <tr>
            <td><label for="obr">Vyberte obrazek</label></td>
            <td><input type="file" name="file"></td>
        </tr>
        <tr>
            <td><label for="pocet">Pocet na sklade</label></td>
            <td><input type="number" step="any" name="pocetP" id="pocet" min="0" max="10000"></td>
        </tr>

    </table>
        <input type="submit" name="odeslat" id="odeslat" class="button">
    </form>

<?php
if($_SERVER["REQUEST_METHOD"] == "POST"){
    if (isset($_POST["odeslat"])){
        if(empty($_POST["nazevP"]) || empty($_POST["cenaP"]) || empty($_POST["popisP"]) || empty($_POST["pocetP"]) || empty($_POST["kategorie"])){
            echo "Vyplňte všechna pole";
            return;
        }
        $file = $_FILES["file"];
        $fileName = $_FILES["file"]["name"];
        $fileTmpName = $_FILES["file"]["tmp_name"];
        $fileSize = $_FILES["file"]["size"];
        $fileError = $_FILES["file"]["error"];
        $fileType = $_FILES["file"]["type"];
        $fileExt = explode('.', $fileName);
        $fileActualExt = strtolower(end($fileExt));
        $allowed = array('jpg', 'jpeg', 'png');
        if(in_array($fileActualExt, $allowed)){
            if ($fileError === 0){
                $fileNameNew = uniqid('', true).".".$fileActualExt;
                $fileDestination = 'imgs/'.$fileNameNew;
                $cesta = './'.$fileDestination;
                move_uploaded_file($fileTmpName, $fileDestination);
                echo "Obrázek byl úspěšně nahrán<br>";
            }else{
                echo "Chyba při nahrávání obrázku";
                return;
            }
        }else{
            echo "Nesprávný formát obrázku";
            return;
        }

        $nazev = $_POST["nazevP"];
        $cena = $_POST["cenaP"];
        $popis = $_POST["popisP"];
        $kategorie = $_POST["kategorie"];
        $pocet = $_POST["pocetP"];

        $sql = "INSERT INTO produkty VALUES (default,'$nazev','$kategorie', '$cena', '$popis', '$cesta', '$pocet')";
        if (mysqli_query($conn, $sql)) {
            echo "Produkt byl úspěšně přidán do databáze.";
        } else {
            echo "Error";
        }
    }
}
mysqli_close($conn);
include_once 'footer.php';
?>
