<?php
include_once 'connect.php';
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
    <h1>Přihlášení</h1>

</header>
<div class="content">
    <h2>Přihlášení</h2>
    <form action="overeni.php" method="post">
        <table>
            <tr>
                <td><label for="email">Email:</label></td>
                <td><input type="email" id="email" name="email" placeholder="your@email.com"></td>
            </tr>
            <tr>
                <td><label for="heslo">Heslo:</label></td>
                <td><input type="password" id="heslo" name="heslo" placeholder="YourPaSSword"></td>
            </tr>
        </table>
        <input type="submit" value="login" name="login" class="button">
        <a href="registrace.php" class="button">Registrace</a>
    </form>

<?php
mysqli_close($conn);
include_once 'footer.php';
?>

