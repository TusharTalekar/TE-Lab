import javax.servlet.http.HttpServlet;
import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.WebServlet;
import java.sql.*;

@WebServlet("/")
public class HelloWorld extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        try {

            // Load JDBC Driver
            Class.forName("com.mysql.cj.jdbc.Driver");

            // Database Connection (your IP)
            Connection con = DriverManager.getConnection(
            		"jdbc:mysql://10.10.8.119:3306/te31474_db",
            	    "te31474",
                    "te31474"
            );

            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM ebookshop");

            out.println("<html>");
            
            out.println("<head>");
            out.println("<style>");
            out.println("body { font-family: Arial; background-color:#f4f6f8; text-align:center; }");
            out.println("h2 { color:#333; margin-top:30px; }");
            out.println("table { border-collapse: collapse; margin:auto; width:70%; background:white; }");
            out.println("th { background:grey; color:white; padding:10px; }");
            out.println("td { padding:8px; text-align:center; }");
            out.println("tr:nth-child(even) { background:#f2f2f2; }");
            out.println("tr:hover { background:#ddd; }");
            out.println("</style>");
            out.println("</head>");
            
            out.println("<body>");
            out.println("<h2>Ebookshop Table</h2>");

            out.println("<table border='1'>");
            out.println("<tr>");
            out.println("<th>ID</th>");
            out.println("<th>Title</th>");
            out.println("<th>Author</th>");
            out.println("<th>Price</th>");
            out.println("<th>Quantity</th>");
            out.println("</tr>");

            while(rs.next())
            {
                out.println("<tr>");
                out.println("<td>" + rs.getInt("book_id") + "</td>");
                out.println("<td>" + rs.getString("book_title") + "</td>");
                out.println("<td>" + rs.getString("book_author") + "</td>");
                out.println("<td>" + rs.getDouble("book_price") + "</td>");
                out.println("<td>" + rs.getInt("quantity") + "</td>");
                out.println("</tr>");
            }

            out.println("</table>");
            out.println("</body></html>");

            con.close();

        } catch (Exception e) {
            out.println("Error: " + e.getMessage());
        }
    }
}