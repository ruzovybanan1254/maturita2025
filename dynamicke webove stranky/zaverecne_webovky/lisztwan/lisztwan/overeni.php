<?php
require_once "connect.php";
?>
<!DOCTYPE html>
<meta charset="UTF-8">
<html>
<head>
    <title>Login page</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Ověření</h1>

</header>
<div class="content">
    <h2>Ověření</h2>
    <?php 
    if(isset($_POST['login'])){
    $email = $_POST['email'];
    $heslo = $_POST['heslo'];
    $sql = "SELECT email, heslo FROM uzivatele WHERE email = '$email' AND heslo = '$heslo'";
    $result = mysqli_query($conn, $sql);
    if (mysqli_num_rows($result) > 0) {
        $row = mysqli_fetch_assoc($result);
        session_start();
        $_SESSION['email'] = $row['email'];
        $_SESSION['heslo'] = $row['heslo'];
        session_start();
        header("Location: shop.php");
    }else{
        echo "Wrong email or password<br><br><a href='prihlaseni.php' class='button'>Zpět</a>";
        
    }
}
    
mysqli_close($conn);
include_once 'footer.php';
?>
