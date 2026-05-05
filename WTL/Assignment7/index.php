<?php
// DATABASE CONNECTION
$host = "10.10.8.119";
$user = "te31474";
$password = "te31474";
$database = "te31474_db";

$conn = mysqli_connect($host, $user, $password, $database);

if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}

// ADD
if (isset($_POST['add'])) {
    $name = $_POST['name'];
    $email = $_POST['email'];
    $course = $_POST['course'];

    mysqli_query($conn, "INSERT INTO students (name,email,course)
                         VALUES ('$name','$email','$course')");
}

// DELETE
if (isset($_GET['delete'])) {
    $id = $_GET['delete'];
    mysqli_query($conn, "DELETE FROM students WHERE id=$id");
}

// UPDATE
if (isset($_POST['update'])) {
    $id = $_POST['id'];
    $name = $_POST['name'];
    $email = $_POST['email'];
    $course = $_POST['course'];

    mysqli_query($conn, "UPDATE students 
        SET name='$name', email='$email', course='$course'
        WHERE id=$id");
}

// EDIT FETCH
$editData = null;
if (isset($_GET['edit'])) {
    $id = $_GET['edit'];
    $result = mysqli_query($conn, "SELECT * FROM students WHERE id=$id");
    $editData = mysqli_fetch_assoc($result);
}
?>

<!DOCTYPE html>
<html>
<head>
    <title>Student</title>
</head>
<style>
body {
    font-family: Arial, sans-serif;
    background: #f4f6f9;
    margin: 0;
    padding: 20px;
}

h2 {
    color: #333;
}

form {
    background: #fff;
    padding: 20px;
    margin-bottom: 30px;
    border-radius: 8px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    max-width: 400px;
}

input[type="text"] {
    width: 100%;
    padding: 10px;
    margin: 8px 0;
    border: 1px solid #ccc;
    border-radius: 5px;
}

input[type="submit"] {
    padding: 10px 15px;
    border: none;
    background: #007bff;
    color: white;
    border-radius: 5px;
    cursor: pointer;
}

input[type="submit"]:hover {
    background: #0056b3;
}

a {
    text-decoration: none;
    margin-left: 10px;
}

a.edit {
    color: #28a745;
    font-weight: bold;
}

a.delete {
    color: #dc3545;
    font-weight: bold;
}

table {
    width: 100%;
    border-collapse: collapse;
    background: #fff;
    border-radius: 8px;
    overflow: hidden;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
}

th, td {
    padding: 12px;
    text-align: left;
}

th {
    background: #007bff;
    color: white;
}

tr:nth-child(even) {
    background: #f2f2f2;
}

tr:hover {
    background: #e9ecef;
}
</style>
<body>

<h2><?php echo $editData ? "Update Student" : "Add Student"; ?></h2>

<form method="POST">
    <input type="hidden" name="id" value="<?php echo $editData['id'] ?? ''; ?>">

    <input type="text" name="name" placeholder="Name"
        value="<?php echo $editData['name'] ?? ''; ?>" required>

    <input type="text" name="email" placeholder="Email"
        value="<?php echo $editData['email'] ?? ''; ?>" required>

    <input type="text" name="course" placeholder="Course"
        value="<?php echo $editData['course'] ?? ''; ?>" required>

    <?php if ($editData): ?>
        <input type="submit" name="update" value="Update">
        <a href="index.php">Cancel</a>
    <?php else:?>
        <input type="submit" name="add" value="Add">
    <?php endif; ?>
</form>

<h2>Student List</h2>

<table>
<tr>
    <th>ID</th>
    <th>Name</th>
    <th>Email</th>
    <th>Course</th>
    <th>Action</th>
</tr>

<?php
$result = mysqli_query($conn, "SELECT * FROM students");

while ($row = mysqli_fetch_assoc($result)) {
    echo "<tr>
        <td>{$row['id']}</td>
        <td>{$row['name']}</td>
        <td>{$row['email']}</td>
        <td>{$row['course']}</td>
        <td>
            <a class='edit' href='?edit={$row['id']}'>Edit</a>
            <a class='delete' href='?delete={$row['id']}'>Delete</a>
        </td>
    </tr>";
}
?>

</table>

</body>
</html>