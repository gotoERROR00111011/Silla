
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
   <h1>선박</h1>
   <table border="1" style="width: 100%;">
      <tr>
         <td align="center"><font size="5">선박명</font></td>
         <td align="center"><font size="5">터미널 코드</font></td>
         <td align="center"><font size="5">입항일시</font></td>
         <td align="center"><font size="5">출항일시</font></td>
		<td align="center"><font size="5">총 작업량</font></td>
		<td align="center"><font size="5">현재작업량</font></td>
		<td align="center"><font size="5">잔여작업량</font></td>

      </tr>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   
   
   String ship_name , terminal_code , in_date , out_date ,max_work,now_work ,rest_work ;
   
%>

 <%
    
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/sea itc";
		String dbID = "root";
		String dbPassword = "apmsetup";
		
		conn = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String SQL = "select * from ship";
       pstmt = conn.prepareStatement(SQL);
       
       rs = pstmt.executeQuery();
       
       while(rs.next())
       {
    	   ship_name = rs.getString("ship_name");
    	   terminal_code = rs.getString("terminal_code");
    	   in_date = rs.getString("in_date");
    	   out_date =rs.getString("out_date");
    	   max_work =rs.getString("max_work");
    	   now_work =rs.getString("now_work");
    	   rest_work =rs.getString("rest_work");
    	   

       %> 
       <tr>
          <td align="center"><%=ship_name %></td>
          <td align="center"><%=terminal_code %></td>
          <td align="center"><%=in_date %></td>
          <td align="center"><%=out_date %></td>
          <td align="center"><%=max_work %></td>
          <td align="center"><%=now_work %></td>
          <td align="center"><%=rest_work %></td>
          
          
        
        
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