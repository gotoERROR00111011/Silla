<%@ page language="java" contentType="text/html; charset=UTF-8"
    pageEncoding="UTF-8"%>
     <%@page import="seaitc.*" %> 
   <%@ page import="java.sql.*" %>
   <%
	String c_code = request.getParameter("c_code");
   %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
<title>Insert title here</title>
<style type="text/css">
    h2{
      font-weight: bolder;
    }
    table{
      margin-top: 10px;
      border: 1px solid grey;
      text-align: center;
      width: 90%;
    }
    tr td{
      border: 1px solid grey;
      height: 40px;
    }
    th{
      text-align: center;
      border: 1px solid grey;
      background-color: #EAEAEA;
    }
    .navbar{
      background-color: #033f77;
      color: white;
    }
    .sub_title{
      font-weight: bolder;
    }
  </style>
</head>

</head>
<body>
<header>
    <nav class="navbar">
      <div class="col-xs-2">
        <ul class="nav navbar-nav navbar-left">
          <li><a href="#">Back</a></li>
        </ul>
      </div>
      <div class="col-xs-8">
        <h1 class="navbar-text" style="font-style: italic;">SMART PORT</h1>
      </div>
      <div class="col-xs-2">
        <ul class="nav navbar-nav navbar-right">
          <li><a href="#">Login</a></li>
        </ul>
      </div>
    </nav>
  </header>
<%
   request.setCharacterEncoding("UTF-8");
   Connection conn = null;
   PreparedStatement pstmt = null;
   ResultSet rs = null;
   
   
   String   cnt_code 
   ,terminal_code
   ,working_yard 
   ,yard_bay 
   ,yard_row 
   ,yard_tir 
   ,cnt_state 
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
		
       String SQL = "select * from container where cnt_code='"+c_code+"'";
       pstmt = conn.prepareStatement(SQL);
       
       rs = pstmt.executeQuery();
       
       while(rs.next())
       {  
    	 
    	   cnt_code = rs.getString("cnt_code");
    	   terminal_code = rs.getString("terminal_code");
    	   working_yard = rs.getString("working_yard");
    	   yard_bay =rs.getString("yard_bay");
    	   yard_row = rs.getString("yard_row");
    	   yard_tir = rs.getString("yard_tir");
    	   cnt_state = rs.getString("cnt_state");
    	   consignee  = rs.getString("consignee");
    	   send  =rs.getString("send");
    	   BL_code  =rs.getString("BL_code");
    	   

       %> 
  <div class="container">
    <div class="row">
      <img src="img/container_detail.png" style="width: 100%; margin-bottom: 10px;">
    </div>
    <div class="row">
      <table align="center">
        <tr>
          <th>컨테이너 코드</th>
          <td><%=cnt_code %></td>
        </tr>
        <tr>
          <th>터미널</th>
          <td><%=terminal_code %></td>
        </tr>
        <tr>
          <th>BL코드</th>
          <td><%=BL_code %></td>
        </tr>
        <tr>
          <th>상태정보</th>
          <td><%=cnt_state %></td>
        </tr>
        <tr>
          <th>위치정보</th>
          <td><%=working_yard %><%= yard_bay%><%= yard_row%><%= yard_tir%></td>
        </tr>
        <tr>
          <th>수화인</th>
          <td><%=consignee %></td>
        </tr>
        <tr>
          <th>송화인</th>
          <td><%=send %></td>
        </tr>
      </table>
    </div>
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