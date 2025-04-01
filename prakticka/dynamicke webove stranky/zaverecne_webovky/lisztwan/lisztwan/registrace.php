<?php
require_once 'connect.php';
?>
    <!DOCTYPE html>
    <meta charset="UTF-8">
    <html>
    <head>
        <title>Registrace</title>
        <link rel="stylesheet" type="text/css" href="styles.css">
        <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

    </head>
    <body>
    <header>
        <h1>Registrace</h1>
    </header>
    <div class="content">
        <h2>Registrace nového "Oslíčka otřes se"</h2>
        <form action="" method="post">
            <table>
                <tr>
                    <td><label for="email">Email:</label></td>
                    <td><input type="text" id="email" name="email" placeholder="oslicku.otres@se.dik"></td>
                </tr>
                <tr>
                    <td><label for="jmeno">Jméno:</label></td>
                    <td><input type="text" id="jmeno" name="jmeno" placeholder="Oslik"></td>
                </tr>
                <tr>
                    <td><label for="prijmeni">Příjmení:</label></td>
                    <td><input type="text" id="prijmeni" name="prijmeni" placeholder="Otres"></td>
                </tr>
                <tr>
                    <td><label for="ulice">Ulice:</label></td>
                    <td><input type="text" id="ulice" name="ulice" placeholder="Otřesná"></td>
                </tr>
                <tr>
                    <td><label for="cislo_popisne">Číslo popisné:</label></td>
                    <td><input type="text" id="cislo_popisne" name="cislo_popisne" placeholder="8"></td>
                </tr>
                <tr>
                    <td><label for="mesto">Město:</label></td>
                    <td><input type="text" id="mesto" name="mesto" placeholder="Oslíkov"></td>
                </tr>
                <tr>
                    <td><label for="telefonni_cislo">Telefonní číslo:</label></td>
                    <td><input type="text" id="telefonni_cislo" name="telefonni_cislo" placeholder="123 123 123"></td>
                </tr>
                <tr>
                    <td><label for="heslo">Heslo:</label></td>
                    <td><input type="password" id="heslo" name="heslo" placeholder="oslickuotresse"></td>
                </tr>
            </table>
            <input type="submit" value="Registrovat" class="button">
            <a href="prihlaseni.php" class="button">Storno</a>
        </form>


<?php
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $email = $_POST["email"];
    $jmeno = $_POST["jmeno"];
    $prijmeni = $_POST["prijmeni"];
    $ulice = $_POST["ulice"];
    $cislo_popisne = $_POST["cislo_popisne"];
    $mesto = $_POST["mesto"];
    $telefonni_cislo = $_POST["telefonni_cislo"];
    $heslo = $_POST["heslo"];

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
    $sql = "SELECT email FROM uzivatele WHERE email='$email'";
    $result = mysqli_query($conn, $sql);
    if (mysqli_num_rows($result) > 0) {
        echo "Uživatel s tímto emailem již existuje";
        return;
    }
    ?>

    <?php
    $sql = "INSERT INTO uzivatele (email,jmeno, prijmeni, ulice, cislo_popisne, mesto, telefonni_cislo, heslo)
            VALUES ('$email','$jmeno', '$prijmeni', '$ulice', '$cislo_popisne', '$mesto', '$telefonni_cislo', '$heslo')";

    if ($conn->query($sql) === TRUE) {
        header("Location: prihlaseni.php");
    } else {
        echo "Chyba: " . $sql . "<br>" . $conn->error;
    }
    $conn->close();
    include_once 'footer.php';
}
