<?php
include_once 'connect.php';
if(($_SESSION['email']!="admin@admin.admin") || ($_SESSION['heslo']!="heslo")){
    header('Location: index.php');
    exit();
}
?>
<!DOCTYPE html>
<meta charset="UTF-8">
<html lang="cs">
<head>
    <title>Delete</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
</head>
<body>
<header>
    <h1>Delete User</h1>
    <?php
    include_once 'header.php';

    ?>
</header>
<div class="content">
    <h2>Odstranění uživatele</h2>
    <?php
    include_once 'header.php';

    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if (isset($_POST['odstranit'])) {
            $id = $_POST['id'];
            $sql = "DELETE FROM uzivatele WHERE id='$id'";
            $res=mysqli_query($conn,$sql);
            if ($res) {
                echo "Uživatel byl úspěšně odstraněn.";
                header("Location: finduser.php");
            }else{
                echo "Error";
            }
        }
    }
    ?>

<?php
mysqli_close($conn);
include_once 'footer.php';
?>

