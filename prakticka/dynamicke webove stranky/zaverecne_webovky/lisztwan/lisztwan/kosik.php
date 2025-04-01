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
    <title>Kosik</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">
</head>
<body>
<header>
    <h1>Tvůj košík</h1>

    <?php
    include_once 'headershop.php';
    ?>
</header>
<div class="content">

    <h2>
        <?php
        echo "Košík uživatele ".$_SESSION['email'];
        ?>
    </h2>

    <table class="seznam">
        <?php
            $sql = "SELECT * FROM uzivatele WHERE email='".$_SESSION['email']."'";
            $cena = 0;
            $result = mysqli_query($conn, $sql);
            $row = mysqli_fetch_assoc($result);
            $id_zakaznika=$row['id'];
            $sql = "SELECT * FROM kosik WHERE id_zakaznika='$id_zakaznika'";
            $result = mysqli_query($conn, $sql);
            if (mysqli_num_rows($result) > 0) {
                echo "<tr><th>Obrázek</th><th>Název</th><th>Kategorie</th><th>Počet kusů</th><th>Cena/ks</th><th>Cena celkem</th><th>Odstranit</th></tr>";
                while($row = mysqli_fetch_assoc($result)) {
                    $id_produktu=$row['id_produktu'];
                    $sql = "SELECT * FROM produkty WHERE id_produktu='$id_produktu'";
                    $result2 = mysqli_query($conn, $sql);
                    $row2 = mysqli_fetch_assoc($result2);
                    $cena+=$row2['cena']*$row["pocet"];
                    echo "<tr>
                            <td><img src='". $row2["cesta_k_obrazku"]. "' alt='". $row2["nazev_produktu"]. "'></td>
                            <td>". $row2["nazev_produktu"]. "</td>
                            <td>". $row2["kategorie"]. "</td>
                            <td>". $row["pocet"]. "</td>
                            <td><b>". $row2["cena"]. "Kč</b></td>
                            <td><b>". $row2["cena"]*$row["pocet"]. "Kč</b></td>
                           
                            <td><form action='deletefromcart.php' enctype='multipart/form-data' method='post'>
                                <input type='hidden' name='id_produktu' value='".$row2["id_produktu"]."'>
                                <input type='hidden' name='uzivatel' value='".$id_zakaznika."'>
                                <input type='submit' name='odstranit' value='Odstranit' class='button'>
                            </form></td>";
                }
            }
        ?>
    </table>
    <h3>Celková cena: <b><?php echo $cena;?>Kč</b></h3>
    <form action='order.php' method='post' enctype="multipart/form-data">
        <input type='hidden' name='cena' value='<?php echo $cena;?>'>
        <input type='hidden' name='uzivatel' value='<?php echo $id_zakaznika;?>'>
        <input type='submit' name='odeslat' value='Odeslat objednávku' class='button'>
    </form>
<?php
mysqli_close($conn);
require_once 'footer.php';
?>
