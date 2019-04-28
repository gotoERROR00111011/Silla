<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
     <%@page import="seaitc.*" %> 
   <%@ page import="java.sql.*" %>
   <%
	String y_code = request.getParameter("y_code");
   	String y_state = request.getParameter("y_state");

	
 %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
</head>

<body>
  <!--  <h1>1C 작업중 같은거 써줘야함</h1> -->
  <H1></H1>
   
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   String   cnt_code 
   ,working_yard 
   , ship_name 
   ,cnt_operation 
   ,cnt_state 
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
		
    	String dbURL ="jdbc:mysql://localhost:3306/ado";
		String dbID = "root";
		String dbPassword = "1111";
		
		conn = DriverManager.getConnection(dbURL,dbID,dbPassword);
		
       String SQL = "select * from container where working_yard='"+y_code+"'and cnt_state='"+y_state+"'";
       pstmt = conn.prepareStatement(SQL);
       rs = pstmt.executeQuery();
       System.out.print("야드 detail");
       if(rs.next())
       {  
    	 
    	   cnt_code = rs.getString("cnt_code");
    	   working_yard = rs.getString("working_yard");
    	   ship_name =rs.getString("ship_name");
    	   cnt_operation = rs.getString("cnt_operation");
    	   cnt_state = rs.getString("cnt_state");
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
      
       <div class="row">
	      <h1 style="color: green; font-weight: bold; text-align: center;"><%= y_code%><%=y_state %></h1>
	   </div>
       <div class="row">
       <table>

         <tr> 
         <td align="center" bgcolor="red"><font size="5" color="white">컨테이너 선사정보</font></td>
          <td align="center"><%=cnt_operation %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">상태 정보</font></td>
          <td align="center"><%=cnt_state %></td>
          </tr>
		  <tr>       
		  <td align="center" bgcolor="red"><font size="5" color="white">yard_bay</font></td>
          <td align="center"><%=yard_bay %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">yard_row</font></td>
          <td align="center"><%=yard_row %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">yard_tir</font></td>
          <td align="center"><%=yard_tir %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">모선</font></td>
          <td align="center"><%=vehicle_ship %></td>
          </tr>
          <tr>
           <td align="center" bgcolor="red"><font size="5" color="white">수출입구분 코드</font></td>
          <td align="center"><%=inOut_separation %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">적공구분 코드</font></td>
           <td align="center"><%=cnt_load_state %></td>
           </tr>
           <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">실제차량 번호</font></td>
          <td align="center"><%=car_num %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">수화인</font></td>
          <td align="center"><%=consignee %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">송화인</font></td>
          <td align="center"><%=send %></td>
          </tr>
          <tr>
          <td align="center" bgcolor="red"><font size="5" color="white">BL코드</font></td>
          <td align="center"><%=BL_code %></td>
          </tr>        
          </table>
       </div>
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
    
 
   

</body>
</html>