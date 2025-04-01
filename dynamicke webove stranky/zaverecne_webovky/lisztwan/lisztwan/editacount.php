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
    <title></title>
    <link rel="stylesheet" href="styles.css">

</head>
<body>
<header>
    <h1>Úprava údajů o účtu</h1>
    <?php
    include_once 'headershop.php';
    ?>
</header>
<div class="content">
    <h2>Úprava účtu</h2>

    <form action="" enctype="multipart/form-data" method="post">

        <?php
        $email = $_SESSION['email'];
        $sql = "SELECT * FROM uzivatele WHERE email='$email'";
        $res = mysqli_query($conn, $sql);
        if (mysqli_num_rows($res) > 0) {
            $row = mysqli_fetch_assoc($res);
            $id = $row['id'];
            $email = $row['email'];
            $jmeno = $row['jmeno'];
            $prijmeni = $row['prijmeni'];
            $ulice = $row['ulice'];
            $cislo_popisne = $row['cislo_popisne'];
            $mesto = $row['mesto'];
            $telefonni_cislo = $row['telefonni_cislo'];
            $heslo = $row['heslo'];
            echo "<table class='form'>";
            echo "<tr><td>Email</td><td><input type='text' name='email' value='$email'></td></tr>";
            echo "<tr><td>Jméno</td><td><input type='text' name='jmeno' value='$jmeno'></td></tr>";
            echo "<tr><td>Příjmení</td><td><input type='text' name='prijmeni' value='$prijmeni'></td></tr>";
            echo "<tr><td>Ulice</td><td><input type='text' name='ulice' value='$ulice'>";
            echo "<tr><td>Číslo popisné</td><td><input type='text' name='cislo_popisne' value='$cislo_popisne'></td></tr>";
            echo "<tr><td>Město</td><td><input type='text' name='mesto' value='$mesto'></td></tr>";
            echo "<tr><td>Telefonní číslo</td><td><input type='text' name='telefonni_cislo' value='$telefonni_cislo'></td></tr>";
            echo "<tr><td>Heslo</td><td><input type='text' name='heslo' value='$heslo'></td></tr></table>";
            echo "<input type='submit' name='submit' value='Upravit' class='button'>";
        } else {
            echo "Chyba: ". $sql. "<br>". $conn->error;
        }
        ?>


    </form>

<?php
if ($_POST){
    if (isset($_POST['submit'])){
        $email = $_POST['email'];
        $jmeno = $_POST['jmeno'];
        $prijmeni = $_POST['prijmeni'];
        $ulice = $_POST['ulice'];
        $cislo_popisne = $_POST['cislo_popisne'];
        $mesto = $_POST['mesto'];
        $telefonni_cislo = $_POST['telefonni_cislo'];
        $heslo = $_POST['heslo'];
        if(empty($jmeno) || empty($prijmeni) || empty($ulice) || empty($cislo_popisne) || empty($mesto) || empty($telefonni_cislo) || empty($heslo)|| empty($email)){
            echo "Vyplňte všechna pole";
            return;
        }elseif ($jmeno == $prijmeni){
            echo "Jméno a příjmení nesmí být stejné";
            return;
        }elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
            echo "Neplatný email";
            return;
        }elseif (strlen($telefonni_cislo) < 9){
            echo "Telefonní číslo musí mít alespoň 9 znaků";
            return;
        }elseif (strlen($telefonni_cislo) > 13){
            echo "Telefonní číslo musí mít maximálně 13 znaků";
            return;
        }elseif (strlen($cislo_popisne) > 10){
            echo "Číslo popisné musí mít maximálně 10 znaků";
            return;
        }elseif (strlen($mesto) > 20){
            echo "Město musí mít maximálně 20 znaků";
            return;
        }elseif (strlen($heslo) < 4){
            echo "Heslo musí mít alespoň 4 znaky";
            return;
        }
        
        $sql = "UPDATE uzivatele SET email='$email', jmeno='$jmeno', prijmeni='$prijmeni', ulice='$ulice', cislo_popisne='$cislo_popisne', mesto='$mesto', telefonni_cislo='$telefonni_cislo', heslo='$heslo' WHERE id='$id'";
        $result = mysqli_query($conn, $sql);
        if ($result){
            header("Location: shop.php");
        }else{
            echo "Chyba: ". $sql. "<br>". $conn->error;
        }
    }
}
mysqli_close($conn);
require_once 'footer.php';
?>
