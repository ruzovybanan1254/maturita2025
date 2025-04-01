<?php
require_once 'connect.php';
if(empty($_SESSION['email']) || empty($_SESSION['heslo'])){
    header('Location: prihlaseni.php');
    exit();
}
?>

<?php
if ($_POST){
    if(isset($_POST['odstranit'])){
        $id_produktu=$_POST['id_produktu'];
        $sql = "DELETE FROM kosik WHERE id_produktu='$id_produktu' AND id_zakaznika='".$_POST['uzivatel']."'";
        $result = mysqli_query($conn, $sql);
        if ($result) {
            echo "Produkt byl úspěšně odstraněn z košíku.";
            header("Location: kosik.php");
        }else{
            echo "Error";
        }
    }
}
mysqli_close($conn);
require_once 'footer.php';
?>