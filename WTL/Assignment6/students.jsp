<%@ page import="java.sql.*" %>

<html>
<head>
<title>Students Info</title>

<style>
body{
font-family: Arial;
background:#f4f4f4;
text-align:center;
}

table{
border-collapse: collapse;
margin:auto;
background:white;
}

th{
background:grey;
color:white;
padding:10px;
}

td{
padding:8px;
}

tr:nth-child(even){
background:#f2f2f2;
}
</style>

</head>

<body>

<h2>Students Information</h2>

<%

try{

Class.forName("com.mysql.cj.jdbc.Driver");

Connection con = DriverManager.getConnection(
"jdbc:mysql://10.10.8.119:3306/te31474_db",
"te31474",
"te31474"
);

Statement stmt = con.createStatement();

ResultSet rs = stmt.executeQuery("SELECT * FROM students_info");

%>

<table border="1">

<tr>
<th>ID</th>
<th>Name</th>
<th>Class</th>
<th>Division</th>
<th>City</th>
</tr>

<%

while(rs.next()){
%>

<tr>
<td><%= rs.getInt("stud_id") %></td>
<td><%= rs.getString("stud_name") %></td>
<td><%= rs.getString("class") %></td>
<td><%= rs.getString("division") %></td>
<td><%= rs.getString("city") %></td>
</tr>

<%
}

con.close();

}catch(Exception e){
out.println(e);
}

%>

</table>

</body>
</html>