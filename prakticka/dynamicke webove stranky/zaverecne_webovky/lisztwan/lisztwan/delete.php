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
    <title>Delete</title>
    <link rel="stylesheet" type="text/css" href="styles.css">
    <link rel="icon" type="image/x-icon" href="/images/favicon.ico">

</head>
<body>
<header>
    <h1>Delete</h1>
<?php
include_once 'header.php';

?>
</header>
<div class="content">
    <h2>Odtraneni zaznamu</h2>
    <?php
    include_once 'header.php';

    if ($_SERVER["REQUEST_METHOD"] == "POST"){
        if (isset($_POST['odstranit'])) {
            $id_produktu = $_POST['id_produktu'];
            $vysledek = mysqli_query($conn, "SELECT * FROM produkty WHERE id_produktu = '$id_produktu'");
            $row = mysqli_fetch_assoc($vysledek);
            unlink($row['cesta_k_obrazku']);
            $sql = "DELETE FROM produkty WHERE id_produktu =$id_produktu";
            $res=mysqli_query($conn,$sql);
            if ($res) {
                echo "Produkt '".$row['nazev_produktu']."' byl úspěšně odstraněn.";
            }else{
                echo "Error";
            }
            if ($_POST['last'] == "seznam"){
                header("Location: seznam.php");
            }else{
                header("Location: find.php");
            }
        }
    }
    ?>

<?php
mysqli_close($conn);
include_once 'footer.php';
?>

