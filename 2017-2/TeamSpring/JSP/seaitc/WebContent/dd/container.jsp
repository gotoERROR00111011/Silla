
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
         <td align="center"><font size="5">터미널 코드</font></td>
         <td align="center"><font size="5">작업블록</font></td>
         <td align="center"><font size="5">선박명</font></td>
         <td align="center"><font size="5">컨테이너 선사정보</font></td>
         <td align="center"><font size="5">상태 정보</font></td>
         <td align="center"><font size="5">작업일시</font></td>
         <td align="center"><font size="5">yard_bay</font></td>
         <td align="center"><font size="5">yard_low</font></td>
         <td align="center"><font size="5">yard_tir</font></td>
         <td align="center"><font size="5">모선</font></td>
         <td align="center"><font size="5">수출입구분 코드</font></td>
         <td align="center"><font size="5">적공구분 코드</font></td>
         <td align="center"><font size="5">실제차량 번호</font></td>
         <td align="center"><font size="5">수화인</font></td>
         <td align="center"><font size="5">송화인</font></td>
         <td align="center"><font size="5">BL코드</font></td>

      </tr>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   
   
   String  cnt_code 
   ,terminal_code
   ,working_yard 
   , ship_name 
   ,cnt_operation 
   ,cnt_state 
   ,w_time
   ,yard_bay 
   ,yard_row 
   ,yard_tir 
   ,vehicle_ship 
   ,inOut_separation 
   ,cnt_load_state 
   ,car_num 
   ,consignee 
   ,send
   ,BL_code;
   
%>

 <%
    
    try{
    	Class.forName("com.mysql.jdbc.Driver");
		
		String dbURL ="jdbc:mysql://localhost:3306/sea itc";
		String dbID = "root";
		String dbPassword = "apmsetup";
		
		conn = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String SQL = "select * from container";
       pstmt = conn.prepareStatement(SQL);
       
       rs = pstmt.executeQuery();
       
       while(rs.next())
       {  
    	 
    	   cnt_code = rs.getString("cnt_code");
    	   terminal_code = rs.getString("terminal_code");
    	   working_yard = rs.getString("working_yard");
    	   ship_name =rs.getString("ship_name");
    	   cnt_operation = rs.getString("cnt_operation");
    	   cnt_state = rs.getString("cnt_state");
    	   w_time = rs.getString("w_time");
    	   yard_bay =rs.getString("yard_bay");
    	   yard_row = rs.getString("yard_row");
    	   yard_tir = rs.getString("yard_tir");
    	   vehicle_ship  = rs.getString("vehicle_ship");
    	   inOut_separation  =rs.getString("inOut_separation");
    	   cnt_load_state  = rs.getString("cnt_load_state");
    	   car_num  = rs.getString("car_num");
    	   consignee  = rs.getString("consignee");
    	   send  =rs.getString("send");
    	   BL_code  =rs.getString("BL_code");
    	   

       %> 
       <tr>
          <td align="center"><%=cnt_code %></td>
          <td align="center"><%=terminal_code %></td>
          <td align="center"><%=working_yard %></td>
          <td align="center"><%=ship_name %></td>
          <td align="center"><%=cnt_operation %></td>
          <td align="center"><%=cnt_state %></td>
          <td align="center"><%=w_time %></td>
          <td align="center"><%=yard_bay %></td>
          <td align="center"><%=yard_row %></td>
          <td align="center"><%=yard_tir %></td>
          <td align="center"><%=vehicle_ship %></td>
          <td align="center"><%=inOut_separation %></td>
           <td align="center"><%=cnt_load_state %></td>
          <td align="center"><%=car_num %></td>
          <td align="center"><%=consignee %></td>
          <td align="center"><%=send %></td>
          <td align="center"><%=BL_code %></td>        
          
        
        
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