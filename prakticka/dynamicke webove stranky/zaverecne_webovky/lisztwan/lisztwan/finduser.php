<?php
require_once 'connect.php';
?>
<!DOCTYPE html>
<html lang="cs">
<head>
    <meta charset="UTF-8">
    <title>Hledání zákazníka</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
</head>
<body>
<header>
    <h1>Hladání zákazníka</h1>
    <?php include_once 'header.php'; ?>
</header>
<div class="content">
    <h2>Hledej zákazníka</h2>
    <form action="" method="post" enctype="multipart/form-data">
        <input type="email" name="email" placeholder="email">
        <input type="number" name="hledane_id" step="any" placeholder="id">
        <input type="text" name="jmeno" placeholder="jmeno">
        <input type="submit" name="hledat" value="Hledat" class="button">
    </form>
    <table class="seznam">
        <?php
        $sql = "SELECT * FROM uzivatele";
        if ($_POST) {
            $hledane_id = isset($_POST["hledane_id"])? intval($_POST["hledane_id"]) : null;
            $email = isset($_POST["email"])? $_POST["email"] : null;
            $jmeno = isset($_POST["jmeno"])? $_POST["jmeno"] : null;
            if (isset($_POST["hledat"])) {

                if ($hledane_id && $email && $jmeno) {
                    $sql = "SELECT * FROM uzivatele WHERE id='$hledane_id' AND email like mysql_real_escape_string($conn, $email) AND jmeno like mysql_real_escape_string($conn, $jmeno)";
                } elseif ($hledane_id && $email) {
                    $sql = "SELECT * FROM uzivatele WHERE id='$hledane_id' AND email like mysql_real_escape_string($conn, $email)";
                } elseif ($email && $jmeno) {
                    $sql = "SELECT * FROM uzivatele WHERE email like mysql_real_escape_string($conn, $email) AND jmeno like mysql_real_escape_string($conn, $jmeno)";
                } elseif ($hledane_id && $jmeno) {
                    $sql = "SELECT * FROM uzivatele WHERE id='$hledane_id' AND jmeno like mysql_real_escape_string($conn, $jmeno)";
                } elseif ($hledane_id) {
                    $sql = "SELECT * FROM uzivatele WHERE id='$hledane_id'";
                } elseif ($email) {
                    $sql = "SELECT * FROM uzivatele WHERE email like mysql_real_escape_string($conn, $email)";
                } elseif ($jmeno) {
                    $sql = "SELECT * FROM uzivatele WHERE jmeno like mysql_real_escape_string($conn, $jmeno)";
                } else{
                    $sql = "SELECT * FROM uzivatele";
                }
            }
        }
        $result = mysqli_query($conn, $sql);
        if (mysqli_num_rows($result) > 0) {
            echo"<tr><th>id</th><th>email</th><th>Jmeno</><th>Prijmeni</th><th>Ulice</th><th>Cislo popisne</th><th>Mesto</th><th>Telefonni cislo</th><th>Odstranění</th></tr>";
            while ($row = mysqli_fetch_assoc($result)) {
                echo "<tr>
                            <td>". $row["id"]. "</td>
                            <td>". $row["email"]. "</td>
                            <td>". $row["jmeno"]. "</td>
                            <td>". $row["prijmeni"]. "</td>
                            <td>". $row["ulice"]. "</td>
                            <td>". $row["cislo_popisne"]. "</td>
                            <td>". $row["mesto"]. "</td>
                            <td>". $row["telefonni_cislo"]. "</td>
                            <td><form action='deleteuser.php' enctype='multipart/form-data' method='post'>
                                <input type='hidden' name='id' value='". $row["id"]. "'>
                                <input type='submit' name='odstranit' value='Odstranit' class='button'>
                            </form></td>
                        </tr>";
            }
        } else {
            echo "Nebyl nalezen žádný zákazník";
        }
        ?>
    </table>
<?php

mysqli_close($conn);
require_once 'footer.php';
