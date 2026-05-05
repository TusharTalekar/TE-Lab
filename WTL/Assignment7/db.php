<?php
$host = "10.10.8.119";
$user = "te31474";
$password = "te31474";
$database = "te31474_db";

$conn = mysqli_connect($host, $user, $password, $database);

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
?>