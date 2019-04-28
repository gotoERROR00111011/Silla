
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
   <h1>컨테이너</h1>
   <table border="1" style="width: 100%;">
      <tr>
         <td align="center"><font size="5">컨테이너 코드</font></td>

         <td align="center"><font size="5">상태 정보</font></td>
		 <td align="center"><font size="5">작업일시</font></td>

         <td align="center"><font size="5">모선</font></td>


      </tr>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   
   
   String   cnt_code 
   ,cnt_state 
   ,w_time 
   ,vehicle_ship ;
   
%>

 <%
    
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		
		conn = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String SQL = "select * from container";
       pstmt = conn.prepareStatement(SQL);
       
       rs = pstmt.executeQuery();
       
       while(rs.next())
       {  
    	 
    	   cnt_code = rs.getString("cnt_code");

    	   cnt_state = rs.getString("cnt_state");
    	   w_time = rs.getString("w_time");

    	   vehicle_ship  = rs.getString("vehicle_ship");

    	   

       %> 
       <tr>
          <td align="center"><%=cnt_code %></td>

          <td align="center"><%=cnt_state %></td>
          <td align="center"><%=w_time %></td>
     
          <td align="center"><%=vehicle_ship %></td>
       
          
        
        
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