
<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
     <%@page import="seaitc.*" %> 
   <%@ page import="java.sql.*" %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>

<body>
   <h1>항구터미널</h1>
   <table border="1" style="width: 100%;">
      <tr>
  
        <td align="center"><font size="5">작업 블록</font></td>
        <td align="center"><font size="5">작업 상태</font></td>
      </tr>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   
   
   String working_yard,port_state;
   
%>

 <%
    
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		
		conn = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String SQL = "select * from port_terminal,container,port_yard";
       pstmt = conn.prepareStatement(SQL);
       
       rs = pstmt.executeQuery();
       
       while(rs.next())
       {

    	   working_yard = rs.getString("working_yard");
    	   port_state =rs.getString("port_state");
    	   

       %> 
       <tr>
		  
           <td align="center"><%=working_yard %></td>
           <td align="center"><%=port_state %></td>
        
        
       </tr>
       <%
          }
       }catch(Exception e)
      {
         
       }finally{
          try{
             if(rs!=null)rs.close();
             if(pstmt!=null)pstmt.close();
             if(conn!=null)conn.close();
          }
          catch(Exception e){
             System.out.println("안되 돌아가");
          }
       }
       %>
    
 
   </table>

</body>
</html>