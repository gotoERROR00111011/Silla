
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
  
		 <td align="center"><font size="5">작업블록</font></td>
		 
		  <td align="center"><font size="5">목표 작업량</font></td>
         <td align="center"><font size="5">목표 본선</font></td>
         <td align="center"><font size="5">현재 작업량</font></td>
         <td align="center"><font size="5">현재 본선</font></td>
         
      </tr>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   
   
   String terminal_code, terminal_name, terminal_domi, terminal_tel,working_yard  , goals_working
   , goals_ship 
   , present_working 
   , present_ship 
   , port_state;
   
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
    	   goals_working = rs.getString("goals_working");
    	   present_ship =rs.getString("present_ship");
    	   present_working =rs.getString("present_working");
    	   present_ship =rs.getString("present_ship");
    	 
    	   

       %> 
       <tr>
		  
         
          <td align="center"><%=working_yard %></td>
          <td align="center"><%=goals_working %></td>
          <td align="center"><%=present_ship %></td>
          <td align="center"><%=present_working %></td>
          <td align="center"><%=present_ship %></td>
         
          
        
        
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