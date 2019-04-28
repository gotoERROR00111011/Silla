
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
        
         <td align="center"><font size="5">입항일시</font></td>
         <td align="center"><font size="5">출항일시</font></td>
         
		<td align="center"><font size="5">총 작업량</font></td>
		
		<td align="center"><font size="5">구분 (양하,적하 들어가야함)</font></td>
      </tr>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   int count=1;
   
   String ship_name , in_date , out_date ,max_work,now_work ,rest_work ;
   
%>

 <%
    
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		System.out.print("DB 커넥터 진입 전");
		conn = DriverManager.getConnection(dbURL,dbID,dbPassword);
		System.out.print("DB 커넥터 접속");
       String SQL = "select * from ship";
       pstmt = conn.prepareStatement(SQL);
       System.out.print("DB Sql문 삽입");
       rs = pstmt.executeQuery();
       while(rs.next())
       {
    	   ship_name = rs.getString("ship_name");
    	   
    	   in_date = rs.getString("in_date");
    	   out_date =rs.getString("out_date");
    	   max_work =rs.getString("max_work");
    	   now_work =rs.getString("now_work");
    	   rest_work =rs.getString("rest_work");
    	   System.out.print("DB검색 중");
    	   count++;
			
       %> 
       <tr>
          <td align="center"><%=ship_name %></td>
         
          <td align="center"><%=in_date %></td>
          <td align="center"><%=out_date %></td>
          <td align="center"><%=max_work %>/<%=now_work %>/<%=rest_work %></td>
      
          
        
        
       </tr>
       <%
       		if(count==3){
       			break;
       		}
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