<?php
include 'db.php';

$id = $_GET['id'];
$result = mysqli_query($conn, "SELECT * FROM students WHERE id=$id");
$row = mysqli_fetch_assoc($result);

if(isset($_POST['update'])){
    $name = $_POST['name'];
    $email = $_POST['email'];
    $course = $_POST['course'];

    $sql = "UPDATE students 
            SET name='$name', email='$email', course='$course' 
            WHERE id=$id";

    if(mysqli_query($conn, $sql)){
        echo "Updated successfully!";
        header("Location: index.php");
    }
}
?>

<form method="POST">
    Name: <input type="text" name="name" value="<?php echo $row['name']; ?>"><br>
    Email: <input type="text" name="email" value="<?php echo $row['email']; ?>"><br>
    Course: <input type="text" name="course" value="<?php echo $row['course']; ?>"><br>
    <input type="submit" name="update" value="Update">
</form>